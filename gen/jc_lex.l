%option nounistd
%option never-interactive
%option outfile="gen/jc_lex.cpp"
%option header-file= "gen/jc_lex.hpp"
%{
enum yytokentype
{
IDENTIFIER = 257,
STRING = 258,
INTEGER = 259,
FLOAT = 260,


LEFT_BRACKET = 261,
RIGHT_BRACKET = 262,
LEFT_BRACE = 263,
RIGHT_BRACE = 264,
LEFT_SQUARE_BRACKET = 265,
RIGHT_SQUARE_BRACKET = 266,

COMMA = 267,
FSTOP = 268,
SEMICOLON = 269,

PLUS = 270,
MINUS = 271,
ASTERISK = 272,
FORWARD_SLASH = 273,

EQUAL = 274,
EQUAL_EQUAL = 275,

EXCLAMATION = 276,
EXCLAMATION_EQUAL = 277,

GREATER = 278,
GREATER_EQUAL = 279,

LESSER = 280,
LESSER_EQUAL = 281,

AND = 282,
AND_AND = 283,

OR = 284,
OR_OR = 285,

RETURN = 286,


UNKNOWN = 999
};
%}


%%
[[:space:]]+ { return 1; }
\"[^"]*\" { return STRING; }

"(" { return LEFT_BRACKET; }
")" { return RIGHT_BRACKET; }
"{" { return LEFT_BRACE; }
"}" { return RIGHT_BRACE; }
"[" { return LEFT_SQUARE_BRACKET; }
"]" { return RIGHT_SQUARE_BRACKET; }

"," { return COMMA; }
"." { return FSTOP; }
";" { return SEMICOLON; }

"+" { return PLUS; }
"-" { return MINUS; }
"/" { return FORWARD_SLASH; }
"*" { return ASTERISK; }

"=" { return EQUAL; }
"==" { return EQUAL_EQUAL; }

"!" { return EXCLAMATION; }
"!=" { return EXCLAMATION_EQUAL; }

">" { return GREATER; }
">=" { return GREATER_EQUAL; }

"<" { return LESSER; }
"<=" { return LESSER_EQUAL; }

"&" { return AND; }
"&&" { return AND_AND; }

"|" { return OR; }
"||" { return OR_OR; }

"return" { return RETURN; }

[a-zA-Z0-9]+ { return IDENTIFIER; }
. { return UNKNOWN; }
<<EOF>> { return 0; }
%%


#ifdef SCANNER_DRIVER

#include <vector>

int yywrap() { return 1; }
int main(int argc, char *argv[])
{
yyin = fopen(argv[1], "r");
int token = 0;
std::vector<int> tokens;
while (token = yylex())
{
if (token != 1)
{
printf("Token: %d  Text: %s\n", token, yytext);
tokens.push_back(token);
}
}

return 0;
}

#endif
