#ifndef JC_ASTSTATEMENT_H
#define JC_ASTSTATEMENT_H

#include <include/AST/ASTNode.hpp>

class ASTStatement : public ASTNode
{
public:
    virtual ~ASTStatement();
};

#endif