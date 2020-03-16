#ifndef JC_ASTEXPRESSION_H
#define JC_ASTEXPRESSION_H

#include <include/AST/ASTStatement.hpp>

/*!
* \brief AST Expression Node
* Base class for AST Nodes that represent expressions
*/
class ASTExpression : public ASTStatement
{
public:
    ASTExpression(const NODE_TYPE &type);
    virtual ~ASTExpression();
};

#endif