#ifndef JC_ASTVARIABLEDECLARATION_H
#define JC_ASTVARIABLEDECLARATION_H

#include <include/AST/ASTStatement.hpp>
#include <include/AST/Constant/ASTConstantInt.hpp>
#include <include/AST/Expression/ASTIdentifier.hpp>

/*!
* \brief AST Variable Declaration Node
* AST Node for variable declarations
*/
class ASTVariableDeclaration : public ASTStatement
{
public:
    std::unique_ptr<ASTIdentifier> type;
    std::unique_ptr<ASTIdentifier> id;

    std::unique_ptr<ASTNode> node;
    std::unique_ptr<ASTConstant> array_size;

    ASTVariableDeclaration(ASTIdentifier &type, ASTIdentifier &id);
    
    ASTVariableDeclaration(ASTIdentifier &type, ASTIdentifier &id, ASTNode &node);

    ASTVariableDeclaration(ASTIdentifier &type, ASTIdentifier &id, ASTConstant &array_size);

    llvm::Value *EmitIR(IREmitter::EmitterState &state);
};

#endif