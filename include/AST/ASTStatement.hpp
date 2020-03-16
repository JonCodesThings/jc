#ifndef JC_ASTSTATEMENT_H
#define JC_ASTSTATEMENT_H

#include <include/AST/ASTNode.hpp>

/*!
* \brief AST Statement Node
* Base class for AST Nodes that represent statements
*/
class ASTStatement : public ASTNode
{
public:
    ASTStatement(const NODE_TYPE &type);
    virtual ~ASTStatement();
};

#endif