#ifndef JC_ASTSTATEMENT_H
#define JC_ASTSTATEMENT_H

#include <include/AST/ASTNode.hpp>

class ASTStatement : public ASTNode
{
public:
    ASTStatement(const NODE_TYPE &type);
    virtual ~ASTStatement();
};

#endif