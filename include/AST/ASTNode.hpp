#ifndef JC_ASTNODE_H
#define JC_ASTNODE_H

#include <string>
#include <vector>

#include <llvm/ADT/APFloat.h>
#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>

#include <stdio.h>
#include <stdlib.h>

#include <include/IREmitter.hpp>


/*!
* \brief AST Node
* Base class for all AST Nodes
*/
class ASTNode
{
public:
    unsigned int line_number;
    unsigned int start_char;
	std::string filename;

	static llvm::Function *ASTNode::current_function;

    enum NODE_TYPE
    {
        IDENTIFIER,
        CONSTANT,

        UNARY_OP,
        BINARY_OP,
        MEMBER_OP,

        VARIABLE_ASSIGNMENT,
        VARIABLE_DECLARATION,

        FUNCTION_CALL,
        FUNCTION_DECLARATION,
        FUNCTION_DEFINITION,

        IF_STATEMENT,
        RETURN_STATEMENT,
        
        FOR_STATEMENT,
        WHILE_STATEMENT,

        DEFER_STATEMENT,

        IMPORT_STATEMENT,
		INCLUDE_STATEMENT,

        TYPE_MOD,

        STRUCT_DEFINITION,
		UNION_DEFINITION,

		FUNCTION_PTR_DEFINITION,

        BLOCK,

		NULLPTR,

		ENUM_DEFINITION,

        NODE_TYPE_COUNT
    } node_type;

    ASTNode(const NODE_TYPE &type);
    virtual ~ASTNode();
    virtual const Symbol *GetSymbol(IREmitter::EmitterState &state);
    virtual const std::string *GetType(IREmitter::EmitterState &state);
    virtual const NODE_TYPE GetNodeType();
    virtual llvm::Value *EmitIR(IREmitter::EmitterState &state) = 0;
	virtual const bool SyntheticEval(IREmitter::EmitterState &state);
};

#endif