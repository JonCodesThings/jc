#ifndef JC_ASTCONSTANT_H
#define JC_ASTCONSTANT_H

#include <include/AST/ASTNode.hpp>

/*!
* \brief AST Constant Node
* Base class for AST Nodes that represent constants
*/
class ASTConstant : public ASTNode
{
public:
    ASTConstant();
};

#endif