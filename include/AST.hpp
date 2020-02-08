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

class ASTNode
{
public:
    virtual ~ASTNode() {}
    virtual void *EmitIR(IREmitter::EmitterState &state) = 0;
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
    ASTIdentifier(const char *identifier) : identifier(identifier) {}
    void *EmitIR(IREmitter::EmitterState &state);
};

template <class T>
class ASTConstant : public ASTNode
{
public:
    T constant;

    ASTConstant() {}
    ASTConstant(T value) : constant(value) {}

    void *EmitIR(IREmitter::EmitterState &state) 
    { 
        return llvm::ConstantInt::get(llvm::IntegerType::get(state.context, 32), constant); 
    }
};

class ASTVariableDeclaration : public ASTStatement
{
public:
    ASTIdentifier &type;
    ASTIdentifier &id;

    ASTVariableDeclaration(ASTIdentifier &type, ASTIdentifier &id) : type(type), id(id) {}
    void *EmitIR(IREmitter::EmitterState &state);
};

class ASTVariableAssignment : public ASTExpression
{
public:
    ASTIdentifier &id;
    ASTConstant<int> &constant;

    ASTVariableAssignment(ASTIdentifier &id, ASTConstant<int> &constant) : id(id), constant(constant) {}
    void *EmitIR(IREmitter::EmitterState &state);
};

class ASTReturnStatement : public ASTStatement
{
public:
    ASTConstant<int> constant;
    ASTIdentifier id;

    enum ReturnType
    {
        CONSTANT,
        ID
    } type;

    ASTReturnStatement(ASTConstant<int> &val) : constant(val), type(CONSTANT) {}
    ASTReturnStatement(ASTIdentifier &id) : id(id), type(ID) {}
    void *EmitIR(IREmitter::EmitterState &state);
};

class ASTBlock : public ASTStatement
{
public:
    std::vector<ASTStatement*> &block;

    ASTBlock() : block(*new std::vector<ASTStatement*>()) {}
    ASTBlock(std::vector<ASTStatement*> &block) : block(block) {}

    void *EmitIR(IREmitter::EmitterState &state);
    void *EmitIR(IREmitter::EmitterState &state, llvm::Function &func);
};

class ASTFunctionCall : public ASTExpression
{
public:
    ASTIdentifier &identifier;
    std::vector<const char *> &arguments;
    ASTFunctionCall(ASTIdentifier &id, std::vector<const char *> &args) : identifier(id), arguments(args) {}
    void *EmitIR(IREmitter::EmitterState &state) { return NULL; }
};

class ASTFunctionDeclaration : public ASTStatement
{
public:
    ASTIdentifier &identifier;
    ASTIdentifier &return_type;
    std::vector<const char *> &arguments;

    ASTFunctionDeclaration() : identifier(*new ASTIdentifier("function id: TBD")), return_type(*new ASTIdentifier("return type: TBD")), arguments(*new std::vector<const char *>) {}
    ASTFunctionDeclaration(ASTIdentifier &ret_type, ASTIdentifier &id, std::vector<const char *>&args) : identifier(id), return_type(ret_type), arguments(args) {}

    void *EmitIR(IREmitter::EmitterState &state);
};

class ASTFunctionDefinition : public ASTStatement
{
public:
    ASTFunctionDeclaration &declaration;
    ASTBlock &block;

    ASTFunctionDefinition() : declaration(*new ASTFunctionDeclaration()), block(*new ASTBlock()) {}
    ASTFunctionDefinition(ASTIdentifier &id, ASTIdentifier &ret_type, std::vector<const char *> &args, ASTBlock &block) : declaration(*new ASTFunctionDeclaration(id, ret_type, args)), block(block) {}

    void *EmitIR(IREmitter::EmitterState &state);
    //ASTFunctionDefinition(ASTFunctionDeclaration &decl, ASTBlock &bl) :
    //declaration(decl), block(block) {}
};
#endif
