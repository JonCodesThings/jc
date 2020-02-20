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


class ASTNode
{
public:
    unsigned int line_number;
    unsigned int start_char;

    static llvm::Function *current_function;
    static llvm::BasicBlock *prev_block;

    enum NODE_TYPE
    {
        IDENTIFIER,
        CONSTANT,

        UNARY_OP,
        BINARY_OP,

        VARIABLE_ASSIGNMENT,
        VARIABLE_DECLARATION,

        FUNCTION_CALL,
        FUNCTION_DECLARATION,
        FUNCTION_DEFINITION,

        IF_STATEMENT,
        RETURN_STATEMENT,

        BLOCK,

        NODE_TYPE_COUNT
    } node_type;

    static NODE_TYPE prev_processed;

    ASTNode(const NODE_TYPE &type);
    virtual ~ASTNode();
    virtual const Symbol *GetSymbol(IREmitter::EmitterState &state);
    virtual const std::string *GetType(IREmitter::EmitterState &state);
    virtual const NODE_TYPE GetNodeType();
    virtual llvm::Value *EmitIR(IREmitter::EmitterState &state) = 0;
};

#endif