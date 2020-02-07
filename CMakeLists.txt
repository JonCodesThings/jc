cmake_minimum_required(VERSION 3.10)
project(jc)

find_package(BISON)
find_package(FLEX)
find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})
llvm_map_components_to_libnames(llvm_libs support core irreader bitwriter)

BISON_TARGET(jc_parser gen/jc_parser.y gen/jc_parser.cpp)
FLEX_TARGET(jc_scanner gen/jc_lex.l gen/jc_lex.cpp)

ADD_FLEX_BISON_DEPENDENCY(jc_scanner jc_parser)

set(SOURCE_FILES src/main.cpp src/AST.cpp src/IREmitter.cpp)

add_executable(jc ${SOURCE_FILES} ${BISON_jc_parser_OUTPUTS} ${FLEX_jc_scanner_OUTPUTS})
include_directories(.)
include_directories(../llvm/include)
target_link_libraries(jc ${llvm_libs})

