cmake_minimum_required(VERSION 3.10)
project(jc)

find_package(BISON)
find_package(FLEX)
find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})
llvm_map_components_to_libnames(llvm_libs support core irreader 
bitwriter AllTargetsAsmParsers AllTargetsCodeGens
AllTargetsDescs AllTargetsInfos Analysis
AsmPrinter CodeGen MC MIRParser Remarks ScalarOpts SelectionDAG
Target TransformUtils Vectorize)

BISON_TARGET(jc_parser gen/jc_parser.y gen/jc_parser.cpp)
FLEX_TARGET(jc_scanner gen/jc_lex.l gen/jc_lex.cpp)

ADD_FLEX_BISON_DEPENDENCY(jc_scanner jc_parser)

set(SOURCE_FILES src/main.cpp 

    src/AST/ASTConstant.cpp
    src/AST/ASTExpression.cpp
    src/AST/ASTNode.cpp
    src/AST/ASTStatement.cpp

	src/AST/Constant/ASTConstantEnumValue.cpp
    src/AST/Constant/ASTConstantFloat.cpp
    src/AST/Constant/ASTConstantInt.cpp
	src/AST/Constant/ASTConstantNullptr.cpp
    src/AST/Constant/ASTConstantString.cpp

    src/AST/Expression/ASTBinaryOperator.cpp
    src/AST/Expression/ASTFunctionCall.cpp
    src/AST/Expression/ASTIdentifier.cpp
	src/AST/Expression/ASTInitializerList.cpp
    src/AST/Expression/ASTMemberOperator.cpp
    src/AST/Expression/ASTUnaryOperator.cpp
    src/AST/Expression/ASTVariableAssignment.cpp

    src/AST/Statement/ASTBlock.cpp
    src/AST/Statement/ASTDeferredStatement.cpp
	src/AST/Statement/ASTEnumDefinition.cpp
	src/AST/Statement/ASTEnumParts.cpp
    src/AST/Statement/ASTForStatement.cpp
    src/AST/Statement/ASTFunctionArgs.cpp
    src/AST/Statement/ASTFunctionDeclaration.cpp
    src/AST/Statement/ASTFunctionDefinition.cpp
	src/AST/Statement/ASTFunctionPointerDefinition.cpp
    src/AST/Statement/ASTIfStatement.cpp
    src/AST/Statement/ASTImportStatement.cpp
	src/AST/Statement/ASTIncludeStatement.cpp
    src/AST/Statement/ASTReturnStatement.cpp
    src/AST/Statement/ASTStructDefinition.cpp
	src/AST/Statement/ASTStructMemberDeclarations.cpp
    src/AST/Statement/ASTTypeSystemModStatement.cpp
    src/AST/Statement/ASTVariableDeclaration.cpp
	src/AST/Statement/ASTUnionDefinition.cpp
    src/AST/Statement/ASTWhileStatement.cpp

    src/Build/BuildConfig.cpp
    src/Build/LinkerInvoke.cpp
    src/Build/ObjectFileEmitter.cpp

    src/Parsers/Parser.cpp
	src/Parsers/BuildParser.cpp
    src/Parsers/ModuleParser.cpp
    src/Parsers/TypeParser.cpp

    src/Tokenizers/Tokenizer.cpp
	src/Tokenizers/BuildTokenizer.cpp
    src/Tokenizers/ModuleTokenizer.cpp
    src/Tokenizers/TypeTokenizer.cpp

    src/IREmitter.cpp
    src/Module.cpp
    src/ModuleRegistry.cpp
    src/SymbolTable.cpp
    src/SymbolTableStack.cpp
    src/TypeRegistry.cpp)

set(HEADER_FILES  include/AST.hpp

	include/AST/ASTConstant.hpp
    include/AST/ASTExpression.hpp
    include/AST/ASTNode.hpp
    include/AST/ASTStatement.hpp

	include/AST/Constant/ASTConstantEnumValue.hpp
    include/AST/Constant/ASTConstantFloat.hpp
    include/AST/Constant/ASTConstantInt.hpp
	include/AST/Constant/ASTConstantNullptr.hpp
    include/AST/Constant/ASTConstantString.hpp

    include/AST/Expression/ASTBinaryOperator.hpp
    include/AST/Expression/ASTFunctionCall.hpp
    include/AST/Expression/ASTIdentifier.hpp
	include/AST/Expression/ASTInitializerList.hpp
    include/AST/Expression/ASTMemberOperator.hpp
    include/AST/Expression/ASTUnaryOperator.hpp
    include/AST/Expression/ASTVariableAssignment.hpp

    include/AST/Statement/ASTBlock.hpp
    include/AST/Statement/ASTDeferredStatement.hpp
	include/AST/Statement/ASTEnumDefinition.hpp
	include/AST/Statement/ASTEnumParts.hpp
    include/AST/Statement/ASTForStatement.hpp
    include/AST/Statement/ASTFunctionArgs.hpp
    include/AST/Statement/ASTFunctionDeclaration.hpp
    include/AST/Statement/ASTFunctionDefinition.hpp
	include/AST/Statement/ASTFunctionPointerDefinition.hpp
    include/AST/Statement/ASTIfStatement.hpp
    include/AST/Statement/ASTImportStatement.hpp
	include/AST/Statement/ASTIncludeStatement.hpp
    include/AST/Statement/ASTReturnStatement.hpp
    include/AST/Statement/ASTStructDefinition.hpp
	include/AST/Statement/ASTStructMemberDeclarations.hpp
    include/AST/Statement/ASTTypeSystemModStatement.hpp
	include/AST/Statement/ASTUnionDefinition.hpp
    include/AST/Statement/ASTVariableDeclaration.hpp
    include/AST/Statement/ASTWhileStatement.hpp

    include/Build/BuildConfig.hpp
    include/Build/LinkerInvoke.hpp
    include/Build/ObjectFileEmitter.hpp

    include/Parsers/Parser.hpp
	include/Parsers/BuildParser.hpp
    include/Parsers/ModuleParser.hpp
    include/Parsers/TypeParser.hpp

    include/Tokenizers/Tokenizer.hpp
	include/Tokenizers/BuildTokenizer.hpp
    include/Tokenizers/ModuleTokenizer.hpp
    include/Tokenizers/TypeTokenizer.hpp
	
	include/IREmitter.hpp
    include/Module.hpp
    include/ModuleRegistry.hpp
    include/SymbolTable.hpp
    include/SymbolTableStack.hpp
    include/TypeRegistry.hpp)

add_executable(jc ${SOURCE_FILES} ${HEADER_FILES} ${BISON_jc_parser_OUTPUTS} ${FLEX_jc_scanner_OUTPUTS})
include_directories(.)
target_link_libraries(jc ${llvm_libs})

