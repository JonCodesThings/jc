#ifndef JC_AST_HPP
#define JC_AST_HPP

#include <string>
#include <vector>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>

#include <stdio.h>
#include <stdlib.h>

class ASTNode
{
public:
virtual ~ASTNode() {}
virtual void *EmitIR(IRBuilder &builder, llvm::LLVMContext &context) = 0;
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

template <class T>
class ASTConstant : public ASTNode
{
public:
T constant;

ASTConstant(T value) { constant = value; }
void *EmitIR(IRBuilder &builder, llvm::LLVMContext &context) { return &constant; }
};

class ASTReturnStatement : public ASTStatement
{
public:
ASTConstant<int> constant;
ASTReturnStatement(ASTConstant<int> &val) : constant(val) {}
void *EmitIR(IRBuilder &builder, llvm::LLVMContext &context)
{
printf("returned %d\n", constant.constant);
return NULL;
}
};

class ASTIdentifier : public ASTExpression
{
public:
std::string identifier;
ASTIdentifier(const char *identifier) : identifier(identifier) {}
void *EmitIR(IRBuilder &builder, llvm::LLVMContext &context)
{
printf("%s\n", identifier.c_str());
return NULL;
}
};

class ASTBlock : public ASTStatement
{
public:
std::vector<ASTStatement*> &block;
ASTBlock() : block(*new std::vector<ASTStatement*>()) {}
ASTBlock(std::vector<ASTStatement*> &block) : block(block) {}
void *EmitIR(IRBuilder &builder, llvm::LLVMContext &context) 
{
printf("Block started\n");
for (ASTStatement *statement : block)
statement->EmitIR();
printf("Block ended\n");
return NULL;
}
};

class ASTFunctionCall : public ASTExpression
{
public:
ASTIdentifier &identifier;
std::vector<const char *> &arguments;
ASTFunctionCall(ASTIdentifier &id, std::vector<const char *> &args) : identifier(id), arguments(args) {}
void *EmitIR(IRBuilder &builder, llvm::LLVMContext &context) { return NULL; }
};

class ASTFunctionDeclaration : public ASTStatement
{
public:
ASTIdentifier &identifier;
ASTIdentifier &return_type;
std::vector<const char *> &arguments;
ASTFunctionDeclaration() : identifier(*new ASTIdentifier("function id: TBD")), return_type(*new ASTIdentifier("return type: TBD")), arguments(*new std::vector<const char *>) {}
ASTFunctionDeclaration(ASTIdentifier &ret_type, ASTIdentifier &id, std::vector<const char *>&args) : identifier(id), return_type(ret_type), arguments(args) {}
void *EmitIR(IRBuilder &builder, llvm::LLVMContext &context)
{
printf("Function return type: "); return_type.EmitIR();
printf("Function name identifier: "); identifier.EmitIR();
return NULL;
}
};

class ASTFunctionDefinition : public ASTStatement
{
public:
ASTFunctionDeclaration &declaration;
ASTBlock &block;
ASTFunctionDefinition() : declaration(*new ASTFunctionDeclaration()), block(*new ASTBlock()) {}
ASTFunctionDefinition(ASTIdentifier &id, ASTIdentifier &ret_type, std::vector<const char *> &args, ASTBlock &block) : declaration(*new ASTFunctionDeclaration(id, ret_type, args)), block(block) {}
void *EmitIR(IRBuilder &builder, llvm::LLVMContext &context)
{
declaration.EmitIR();
block.EmitIR();
return NULL;
}
//ASTFunctionDefinition(ASTFunctionDeclaration &decl, ASTBlock &bl) :
//declaration(decl), block(block) {}
};
#endif
