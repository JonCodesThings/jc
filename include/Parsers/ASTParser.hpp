#ifndef JC_ASTPARSER_HPP
#define JC_ASTPARSER_HPP

#include <include/Tokenizers/ASTTokenizer.hpp>
#include <include/Parsers/Parser.hpp>
#include <include/AST/ASTNode.hpp>

class ASTParser : public Parser
{
public:
	ASTParser();
	const bool Parse(const std::vector<Token> &tokens);
	struct ASTParserNode
	{
		std::shared_ptr<ASTParserNode> parent;
		std::vector<std::shared_ptr<ASTParserNode>> children;
		ASTTokenizer::AST_TOKENS tokenType;
		ASTNode::NODE_TYPE astNodeType;
		ASTParserNode() {}
		ASTParserNode(ASTTokenizer::AST_TOKENS tokenT) { tokenType = tokenT; astNodeType = ASTNode::NODE_TYPE::NODE_TYPE_COUNT; }
		ASTParserNode(ASTTokenizer::AST_TOKENS tokenT, ASTNode::NODE_TYPE nodeType) 
		: tokenType(tokenT), astNodeType(nodeType) {}
		std::shared_ptr<ASTParserNode> FindChildNodeWithToken(ASTTokenizer::AST_TOKENS token)
		{
			for (int i = 0; i < children.size(); ++i)
			{
				if (children[i]->tokenType == tokenType)
					return children[i];
			}
			return nullptr;
		}
		unsigned int GetJumpsToRoot()
		{
			return parent->GetJumpsToRoot() + 1;
		}

		void AddChild(std::shared_ptr<ASTParserNode> child)
		{
			child->parent = std::make_shared<ASTParserNode>(*this);
			children.push_back(child);
		}

	};
private:
	static void BuildParserTree();
	static ASTParserNode tree;
};

#endif