#ifndef JC_ASTEXPRESSION_H
#define JC_ASTEXPRESSION_H

#include <include/AST/ASTStatement.hpp>

class ASTExpression : public ASTStatement
{
public:
    ASTExpression(const NODE_TYPE &type);
    virtual ~ASTExpression();
};

#endif