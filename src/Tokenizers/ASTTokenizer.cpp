#include <include/Tokenizers/ASTTokenizer.hpp>

ASTTokenizer::ASTTokenizer() {}
ASTTokenizer::~ASTTokenizer() {}

std::vector<Token> ASTTokenizer::Tokenize(const std::string & in)
{
	std::vector<Token> tokens;
	std::string accum;

	for (int i = 0; i < in.length(); ++i)
	{
		Token t;
		t.token_type = AST_TOKENS::UNKNOWN;

		if (in[i] == ' ' || in[i] == '\n' || in[i] == '\t' || in[i] == '\r' || in[i] == ';')
		{
			if (accum.length() > 0)
			{
				if (accum[0] == '"' && accum[accum.length() - 1] == '"')
				{
					Token tok;
					tok.token_type = AST_TOKENS::STRING;
					tok.string = new std::string(accum);
					tokens.push_back(tok);
					accum.clear();
					continue;
				}
				else if (accum[accum.length() - 1] == 'f')
				{
					Token tok;
					tok.token_type = AST_TOKENS::FLOAT;
					tok.string = new std::string(accum);
					tokens.push_back(tok);
					accum.clear();
					continue;
				}
				else if (isdigit(accum[0]) && isdigit(accum[accum.length() - 1]))
				{
					Token tok;
					tok.token_type = AST_TOKENS::INTEGER;
					tok.string = new std::string(accum);
					tokens.push_back(tok);
					accum.clear();
					continue;
				}
				else if (accum == "if")
					t.token_type = AST_TOKENS::IF;
				else if (accum == "else")
					t.token_type = AST_TOKENS::ELSE;
				else if (accum == "return")
					t.token_type = AST_TOKENS::RETURN;
				else if (accum == "defer")
					t.token_type = AST_TOKENS::DEFER;
				else if (accum == "for")
					t.token_type = AST_TOKENS::FOR;
				else if (accum == "while")
					t.token_type = AST_TOKENS::WHILE;
				else if (accum == "typedef")
					t.token_type = AST_TOKENS::TYPEDEF;
				else if (accum == "alias")
					t.token_type = AST_TOKENS::ALIAS;
				else if (accum == "auto")
					t.token_type = AST_TOKENS::AUTO;
				else if (accum == "enum")
					t.token_type = AST_TOKENS::ENUM;
				else if (accum == "union")
					t.token_type = AST_TOKENS::UNION;
				else if (accum == "true")
					t.token_type = AST_TOKENS::TRUE;
				else if (accum == "false")
					t.token_type = AST_TOKENS::FALSE;
				else if (accum == "mut")
					t.token_type = AST_TOKENS::MUT;
				else if (accum == "extern")
					t.token_type = AST_TOKENS::EXTERN;
				else if (accum == "import")
					t.token_type = AST_TOKENS::IMPORT;
				else if (accum == "export")
					t.token_type = AST_TOKENS::EXPORT;
				else if (accum == "include")
					t.token_type = AST_TOKENS::INCLUDE;
				else if (accum == "link")
					t.token_type = AST_TOKENS::LINK;
				else if (accum == "import")
					t.token_type = AST_TOKENS::IMPORT;
				else if (accum == "funcptr")
					t.token_type = AST_TOKENS::FUNCPTR;
				else if (accum == "nullptr")
					t.token_type = AST_TOKENS::NULLPTR;
				else if (accum == "struct")
					t.token_type = AST_TOKENS::STRUCT;
				else
				{
					Token tok;
					tok.token_type = AST_TOKENS::IDENTIFIER;
					tok.string = new std::string(accum);
					tokens.push_back(tok);
					accum.clear();
					continue;
				}
				accum.clear();
			}
			else
				continue;
		}


		switch (in[i])
		{
		case '(':
		{
			t.token_type = AST_TOKENS::LEFT_BRACKET;
			break;
		}
		case ')':
		{
			t.token_type = AST_TOKENS::RIGHT_BRACKET;
			break;
		}
		case '{':
		{
			t.token_type = AST_TOKENS::LEFT_BRACE;
			break;
		}
		case '}':
		{
			t.token_type = AST_TOKENS::RIGHT_BRACE;
			break;
		}
		case '[':
		{
			t.token_type = AST_TOKENS::LEFT_SQUARE_BRACKET;
			break;
		}
		case ']':
		{
			t.token_type = AST_TOKENS::RIGHT_SQAURE_BRACKET;
			break;
		}
		case '|':
		{
			if (in[i + 1] == '|')
			{
				t.token_type = AST_TOKENS::OR_OR;
				i += 2;
			}
			else
				t.token_type = AST_TOKENS::OR;
			break;
		}
		case '&':
		{
			if (in[i + 1] == '&')
			{
				t.token_type = AST_TOKENS::AND_AND;
				i += 2;
			}
			else
				t.token_type = AST_TOKENS::AND;
			break;
		}
		case '=':
		{
			if (in[i + 1] == '=')
			{
				t.token_type = AST_TOKENS::EQUAL_EQUAL;
				i += 2;
			}
			else
				t.token_type = AST_TOKENS::EQUAL;
			break;
		}
		case '!':
		{
			if (in[i + 1] == '=')
			{
				t.token_type = AST_TOKENS::EXCLAMATION_EQUAL;
				i += 2;
			}
			else
				t.token_type = AST_TOKENS::EXCLAMATION;
			break;
		}
		case '<':
		{
			if (in[i + 1] == '<')
			{
				t.token_type = AST_TOKENS::LEFT_SHIFT;
				i += 2;
			}
			else if (in[i + 1] == '=')
			{
				t.token_type = AST_TOKENS::LESSER_EQUAL;
				i += 2;
			}
			else
				t.token_type = AST_TOKENS::LESSER;
			break;
		}
		case '>':
		{
			if (in[i + 1] == '>')
			{
				t.token_type = AST_TOKENS::RIGHT_SHIFT;
				i += 2;
			}
			else if (in[i + 1] == '=')
			{
				t.token_type = AST_TOKENS::GREATER_EQUAL;
				i += 2;
			}
			else
				t.token_type = AST_TOKENS::GREATER;
			break;
		}
		case ';':
		{
			t.token_type = AST_TOKENS::SEMICOLON;
			break;
		}
		case ':':
		{
			t.token_type = AST_TOKENS::COLON;
			break;
		}
		case '+':
		{
			t.token_type = AST_TOKENS::PLUS;
			break;
		}
		case '-':
		{
			if (in[i + 1] == '>')
			{
				t.token_type = AST_TOKENS::ARROW;
				i += 2;
			}
			else
				t.token_type = AST_TOKENS::MINUS;
			break;
		}
		case '*':
		{
			t.token_type = AST_TOKENS::ASTERISK;
			break;
		}
		case '/':
		{
			t.token_type = AST_TOKENS::FORWARD_SLASH;
			break;
		}
		case '%':
		{
			t.token_type = AST_TOKENS::PERCENT;
			break;
		}
		case ',':
		{
			t.token_type = AST_TOKENS::COMMA;
			break;
		}
		case '.':
		{
			t.token_type = AST_TOKENS::FSTOP;
			break;
		}
		}

		if (t.token_type != AST_TOKENS::UNKNOWN)
			tokens.push_back(t);
		else
			accum += in[i];	
	}

	return tokens;
}

