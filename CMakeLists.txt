cmake_minimum_required(VERSION 3.10)
project(jc)

find_package(BISON)
find_package(FLEX)
find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})
llvm_map_components_to_libnames(llvm_libs support core irreader bitwriter)

BISON_TARGET(jc_type_parser gen/jc_type_parser.y gen/jc_type_parser.cpp)
FLEX_TARGET(jc_type_scanner gen/jc_type_scanner.l gen/jc_type_scanner.cpp)

ADD_FLEX_BISON_DEPENDENCY(jc_type_scanner jc_type_parser)

BISON_TARGET(jc_parser gen/jc_parser.y gen/jc_parser.cpp)
FLEX_TARGET(jc_scanner gen/jc_lex.l gen/jc_lex.cpp)

ADD_FLEX_BISON_DEPENDENCY(jc_scanner jc_parser)

set(SOURCE_FILES src/main.cpp 

    src/AST/ASTConstant.cpp
    src/AST/ASTExpression.cpp
    src/AST/ASTNode.cpp
    src/AST/ASTStatement.cpp

    src/AST/Constant/ASTConstantFloat.cpp
    src/AST/Constant/ASTConstantInt.cpp
    src/AST/Constant/ASTConstantString.cpp

    src/AST/Expression/ASTBinaryOperator.cpp
    src/AST/Expression/ASTFunctionCall.cpp
    src/AST/Expression/ASTIdentifier.cpp
    src/AST/Expression/ASTMemberOperator.cpp
    src/AST/Expression/ASTUnaryOperator.cpp
    src/AST/Expression/ASTVariableAssignment.cpp

    src/AST/Statement/ASTBlock.cpp
    src/AST/Statement/ASTDeferredStatement.cpp
    src/AST/Statement/ASTForStatement.cpp
    src/AST/Statement/ASTFunctionArgs.cpp
    src/AST/Statement/ASTFunctionDeclaration.cpp
    src/AST/Statement/ASTFunctionDefinition.cpp
    src/AST/Statement/ASTIfStatement.cpp
    src/AST/Statement/ASTReturnStatement.cpp
    src/AST/Statement/ASTStructDefinition.cpp
    src/AST/Statement/ASTTypeSystemModStatement.cpp
    src/AST/Statement/ASTVariableDeclaration.cpp
    src/AST/Statement/ASTWhileStatement.cpp

    src/IREmitter.cpp 
    src/SymbolTable.cpp
    src/SymbolTableStack.cpp
	src/Tokenizer.cpp
    src/TypeRegistry.cpp)

add_executable(jc ${SOURCE_FILES} ${BISON_jc_type_parser_OUTPUTS} ${FLEX_jc_type_scanner_OUTPUTS} ${BISON_jc_parser_OUTPUTS} ${FLEX_jc_scanner_OUTPUTS})
include_directories(.)
target_link_libraries(jc ${llvm_libs})

