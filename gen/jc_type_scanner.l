%option nounistd
%option never-interactive
%option outfile="gen/jc_type_scanner.cpp"
%option header-file= "gen/jc_type_scanner.hpp"
%option prefix="typescanner"
%{
#include "jc_parser.hpp"
extern "C" int typescannerwrap() { return 1; }
%}