#include <include/Parsers/ASTParser.hpp>

#include <include/AST.hpp>

ASTParser::ASTParserNode ASTParser::tree = ASTParser::ASTParserNode();

ASTParser::ASTParser()
{
}

std::shared_ptr<ASTNode> GetNodeFromNodeType(const std::vector<Token>& tokens, unsigned int currentIndex, unsigned int difference, ASTNode::NODE_TYPE type)
{
	switch (type)
	{
	default:
		return nullptr;
	case ASTNode::NODE_TYPE::BLOCK:
	{
		return std::make_shared<ASTBlock>();
	}
	case ASTNode::NODE_TYPE::RETURN_STATEMENT:
	{
		ASTNode *ret = nullptr;
		switch (tokens[currentIndex - 1].token_type)
		{
		default:
			break;
		case ASTTokenizer::AST_TOKENS::INTEGER:
			ret = new ASTConstantInt(atoi(tokens[currentIndex - 1].string->c_str()));
			break;
		}
		return std::make_shared<ASTReturnStatement>(*ret);
		}
		
	}
}

const bool ASTParser::Parse(const std::vector<Token>& tokens)
{
	tree.parent = nullptr;
	ASTParserNode *currentNode = &tree;

	std::stack<std::shared_ptr<ASTBlock>> block;

	for (int i = 0; i < tokens.size(); ++i)
	{
		switch (tokens[i].token_type)
		{
		default:
			std::shared_ptr<ASTParserNode> node = currentNode->FindChildNodeWithToken((ASTTokenizer::AST_TOKENS)tokens[i].token_type);

			if (node != nullptr)
			{
				if (node->astNodeType != ASTNode::NODE_TYPE::NODE_TYPE_COUNT)
				{
					unsigned int tokenGap = node->GetJumpsToRoot();
					std::shared_ptr<ASTNode> ast = GetNodeFromNodeType(tokens, i, tokenGap, node->astNodeType);
				}
			}

			break;
		}
	}

	return false;
}

void ASTParser::BuildParserTree()
{
	if (tree.children.size() == 0)
	{
		tree.AddChild(std::make_shared<ASTParserNode>(ASTTokenizer::AST_TOKENS::LEFT_BRACE, ASTNode::NODE_TYPE::BLOCK));
		tree.AddChild(std::make_shared<ASTParserNode>(ASTTokenizer::AST_TOKENS::RETURN));
		tree.children.back()->AddChild(std::make_shared<ASTParserNode>(ASTTokenizer::AST_TOKENS::INTEGER));
		tree.children.back()->children.back()->AddChild(std::make_shared<ASTParserNode>(ASTTokenizer::SEMICOLON, ASTNode::NODE_TYPE::RETURN_STATEMENT));
	}
}
