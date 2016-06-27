#include "Package.h"
#include "Parser.h"


Package::Package(const QString &name) :
    Package::Class(nullptr, name, Token::Public, Token::Class)
{
}
