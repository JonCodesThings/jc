#ifndef JC_AST_HPP
#define JC_AST_HPP

#include <string>
#include <vector>

#include <llvm/ADT/APFloat.h>
#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <stdio.h>
#include <stdlib.h>

#include <include/IREmitter.hpp>

class ASTConstantInt;

class ASTNode
{
public:
    unsigned int line_number = 0;
    unsigned int start_char = 0;

    virtual ~ASTNode() {}
    virtual const Symbol *GetSymbol(IREmitter::EmitterState &state) { return NULL; };
    virtual const std::string *GetType(IREmitter::EmitterState &state) { return state.typeRegistry.GetLifetimeTypeString("void"); };
    virtual llvm::Value *EmitIR(IREmitter::EmitterState &state) = 0;
};

class ASTStatement : public ASTNode
{
public:
    virtual ~ASTStatement() {}
};

class ASTExpression : public ASTStatement
{
public:
    virtual ~ASTExpression() {}
};


class ASTIdentifier : public ASTExpression
{
public:
    std::string identifier;

    ASTIdentifier() {}
    const std::string *GetType(IREmitter::EmitterState &state)
    {
        Symbol *symbol = state.frontmost->GetSymbolByIdentifier(identifier);
        if (symbol)
            return &symbol->type;
        return state.typeRegistry.GetLifetimeTypeString(identifier);
    }
    const Symbol *GetSymbol(IREmitter::EmitterState &state)
    {
        return state.frontmost->GetSymbolByIdentifier(identifier);
    }
    ASTIdentifier(const std::string &identifier) : identifier(identifier) {}
    llvm::Value *EmitIR(IREmitter::EmitterState &state);
};

class ASTUnaryOperator : public ASTExpression
{
public:
    ASTNode &operatee;
    ASTIdentifier *cast;
    ASTConstantInt *index;

    enum OP
    {
        CAST,
        INCREMENT,
        DECREMENT,
        ADDRESS_OF,
        DEREFERENCE,
        ARRAY_INDEX
    } op;

    ASTUnaryOperator(ASTNode &operatee, OP op) : operatee(operatee), cast(NULL), index(NULL), op(op) {}
    ASTUnaryOperator(ASTNode &operatee, ASTIdentifier *identifier, OP op) : operatee(operatee), cast(identifier), index(NULL), op(op) {}
    ASTUnaryOperator(ASTNode &operatee, ASTConstantInt &index, OP op) : operatee(operatee), cast(NULL), index(&index), op(op) {}
    llvm::Value *EmitIR(IREmitter::EmitterState &state);
};

class ASTBinaryOperator : public ASTExpression
{
public:
    ASTNode &left;
    ASTNode &right;

    enum OP
    {
        ADD,
        SUBTRACT,
        MULTIPLE,
        DIVIDE
    } op;

    ASTBinaryOperator(ASTNode &left, ASTNode &right, OP op) : left(left), right(right), op(op) {}
    llvm::Value *EmitIR(IREmitter::EmitterState &state);
    const std::string *GetType(IREmitter::EmitterState &state)
    {
        return right.GetType(state);
    }
};

class ASTConstant : public ASTNode
{
public:
    ASTConstant() {}
};

class ASTConstantInt : public ASTConstant
{
public:
    int constant;

    ASTConstantInt(int constant) : constant(constant) {}

    llvm::Value *EmitIR(IREmitter::EmitterState &state) 
    { 
        return llvm::ConstantInt::get(llvm::Type::getInt32Ty(state.context), constant); 
    }
    const std::string *GetType(IREmitter::EmitterState &state)
    {
        return state.typeRegistry.GetLifetimeTypeString("i32");
    }
};

class ASTConstantFloat : public ASTConstant
{
public:
    float constant;

    ASTConstantFloat(float constant) : constant(constant) {}

    llvm::Value *EmitIR(IREmitter::EmitterState &state) 
    { 
        return llvm::ConstantFP::get(llvm::Type::getFloatTy(state.context), constant); 
    }
    const std::string *GetType(IREmitter::EmitterState &state)
    {
        return state.typeRegistry.GetLifetimeTypeString("f32");
    }
};

class ASTVariableDeclaration : public ASTStatement
{
public:
    ASTIdentifier &type;
    ASTIdentifier &id;

    ASTNode *node;
    ASTConstant *array_size;

    ASTVariableDeclaration(ASTIdentifier &type, ASTIdentifier &id) : type(type), id(id), node(NULL), array_size(NULL) {}
    ASTVariableDeclaration(ASTIdentifier &type, ASTIdentifier &id, ASTNode &node) : type(type), id(id), node(&node), array_size(NULL) {}
    ASTVariableDeclaration(ASTIdentifier &type, ASTIdentifier &id, ASTConstant &array_size) : type(type), id(id), node(NULL), array_size(&array_size) {}
    llvm::Value *EmitIR(IREmitter::EmitterState &state);
};

class ASTVariableAssignment : public ASTExpression
{
public:
    ASTIdentifier *id;
    ASTNode &node;
    ASTNode *array_index;

    ASTVariableAssignment(ASTIdentifier &id, ASTNode &node) : id(&id), node(node), array_index(NULL) {}
    ASTVariableAssignment(ASTNode &array_index, ASTNode &node) : id (NULL), array_index(&array_index), node(node) {}
    llvm::Value *EmitIR(IREmitter::EmitterState &state);
};

class ASTReturnStatement : public ASTStatement
{
public:
    ASTStatement *expr;

    enum ReturnType
    {
        CONSTANT,
        ID,
        STATEMENT
    } type;

    ASTReturnStatement(ASTStatement &expr) : expr(&expr) {}
    llvm::Value *EmitIR(IREmitter::EmitterState &state);
};

struct ASTFunctionArg
{
    ASTFunctionArg(ASTIdentifier &type, ASTIdentifier &name) : type(type), name(name) {}
    ASTIdentifier &type;
    ASTIdentifier &name;
};

class ASTFunctionArgs
{
public:
    std::vector<ASTFunctionArg> args;
};

class ASTBlock : public ASTStatement
{
public:
    std::vector<ASTStatement*> &block;

    ASTBlock() : block(*new std::vector<ASTStatement*>()) {}
    ASTBlock(std::vector<ASTStatement*> &block) : block(block) {}

    llvm::Value *EmitIR(IREmitter::EmitterState &state);
    llvm::Value *EmitIR(IREmitter::EmitterState &state, ASTFunctionArgs &args, llvm::Function &func);
};

class ASTFunctionCall : public ASTExpression
{
public:
    ASTIdentifier &identifier;
    std::vector<ASTStatement*> *args;
    ASTFunctionCall(ASTIdentifier &id) : identifier(id), args(NULL) {}
    ASTFunctionCall(ASTIdentifier &id, std::vector<ASTStatement*> &args) : identifier(id), args(&args) {}
    llvm::Value *EmitIR(IREmitter::EmitterState &state);
};

class ASTFunctionDeclaration : public ASTStatement
{
public:
    ASTIdentifier &identifier;
    ASTIdentifier &return_type;
    ASTFunctionArgs &arguments;

    ASTFunctionDeclaration() : identifier(*new ASTIdentifier("function id: TBD")), return_type(*new ASTIdentifier("return type: TBD")), arguments(*new ASTFunctionArgs()) {}
    ASTFunctionDeclaration(ASTIdentifier &ret_type, ASTIdentifier &id, ASTFunctionArgs &args) : identifier(id), return_type(ret_type), arguments(args) {}

    llvm::Value *EmitIR(IREmitter::EmitterState &state);
};

class ASTFunctionDefinition : public ASTStatement
{
public:
    ASTFunctionDeclaration &declaration;
    ASTBlock &block;

    ASTFunctionDefinition() : declaration(*new ASTFunctionDeclaration()), block(*new ASTBlock()) {}
    ASTFunctionDefinition(ASTIdentifier &id, ASTIdentifier &ret_type, ASTFunctionArgs &args, ASTBlock &block) : declaration(*new ASTFunctionDeclaration(id, ret_type, args)), block(block) {}

    llvm::Value *EmitIR(IREmitter::EmitterState &state);
    //ASTFunctionDefinition(ASTFunctionDeclaration &decl, ASTBlock &bl) :
    //declaration(decl), block(block) {}
};
#endif
