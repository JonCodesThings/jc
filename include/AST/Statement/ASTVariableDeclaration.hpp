#ifndef JC_ASTVARIABLEDECLARATION_H
#define JC_ASTVARIABLEDECLARATION_H

#include <include/AST/ASTStatement.hpp>
#include <include/AST/Constant/ASTConstantInt.hpp>
#include <include/AST/Expression/ASTIdentifier.hpp>

class ASTVariableDeclaration : public ASTStatement
{
public:
    ASTIdentifier &type;
    ASTIdentifier &id;

    ASTNode *node;
    ASTConstant *array_size;

    ASTVariableDeclaration(ASTIdentifier &type, ASTIdentifier &id);
    
    ASTVariableDeclaration(ASTIdentifier &type, ASTIdentifier &id, ASTNode &node);

    ASTVariableDeclaration(ASTIdentifier &type, ASTIdentifier &id, ASTConstant &array_size);

    llvm::Value *EmitIR(IREmitter::EmitterState &state);
};

#endif