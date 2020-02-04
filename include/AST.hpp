#include <vector>

#include <stdio.h>

class ASTNode
{
public:
virtual ~ASTNode() {}
virtual void *EmitIR() = 0;
};

class ASTStatement : public ASTNode
{
public:
virtual ~ASTStatement() {}
};

class ASTExpression : public ASTStatement
{
public:
virtual ~ASTExpression() {}
};

template <class T>
class ASTConstant : public ASTNode
{
public:
T constant;

ASTConstant(T value) { constant = value; }
void *EmitIR() { return &constant; }
};

class ASTIdentifier : public ASTExpression
{
public:
const char *id;
ASTIdentifier(const char *identifier) { id = identifier; }
void *EmitIR() { return NULL; }
};

class ASTBlock : public ASTStatement
{
public:
std::vector<ASTStatement*> &block;
ASTBlock(std::vector<ASTStatement*> &block);
void *EmitIR() 
{
printf("Block statement\n"); 
for (ASTStatement *statement : block)
statement->EmitIR();
}
};

class ASTFunctionCall : public ASTExpression
{
public:
ASTIdentifier &identifier;
std::vector<const char *> &arguments;
ASTFunctionCall(ASTIdentifier &id, std::vector<const char *> &args) : identifier(id), arguments(args) {}
void *EmitIR() { return NULL; }
};

class ASTFunctionDeclaration : public ASTStatement
{
public:
ASTIdentifier &identifier;
ASTIdentifier &return_type;
std::vector<const char *> &arguments;
};

class ASTFunctionDefinition : public ASTStatement
{
public:
ASTFunctionDeclaration &declaration;
ASTBlock &block;
ASTFunctionDefinition(ASTFunctionDeclaration &decl, ASTBlock &bl) :
declaration(decl), block(block)
{
}
};
