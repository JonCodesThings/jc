#include <include/AST/Statement/ASTEnumParts.hpp>

ASTEnumPart::ASTEnumPart(ASTIdentifier & id, ASTConstantInt * val) : id(&id), val(val)
{
}
