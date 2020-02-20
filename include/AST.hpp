#ifndef JC_AST_HPP
#define JC_AST_HPP

#include <include/AST/ASTNode.hpp>

#include <include/AST/ASTConstant.hpp>
#include <include/AST/ASTExpression.hpp>
#include <include/AST/ASTStatement.hpp>

#include <include/AST/Constant/ASTConstantFloat.hpp>
#include <include/AST/Constant/ASTConstantInt.hpp>
#include <include/AST/Constant/ASTConstantString.hpp>

#include <include/AST/Expression/ASTBinaryOperator.hpp>
#include <include/AST/Expression/ASTFunctionCall.hpp>
#include <include/AST/Expression/ASTIdentifier.hpp>
#include <include/AST/Expression/ASTUnaryOperator.hpp>
#include <include/AST/Expression/ASTVariableAssignment.hpp>

#include <include/AST/Statement/ASTBlock.hpp>
#include <include/AST/Statement/ASTFunctionArgs.hpp>
#include <include/AST/Statement/ASTFunctionDeclaration.hpp>
#include <include/AST/Statement/ASTFunctionDefinition.hpp>
#include <include/AST/Statement/ASTIfStatement.hpp>
#include <include/AST/Statement/ASTReturnStatement.hpp>
#include <include/AST/Statement/ASTVariableDeclaration.hpp>
#include <include/AST/Statement/ASTWhileStatement.hpp>


#endif
