#include "Token.h"

QHash<QString, Token> tokens = {{".",         Token::Point},
                                 {",",         Token::Comma},
                                 {":",         Token::Colon},
                                 {";",         Token::Semicolon},
                                 {"=",         Token::Equals},
                                 {"&",         Token::Ampersand},
                                 {"|",         Token::VerticalBar},
                                 {"(",         Token::ParenthesesOpen},
                                 {")",         Token::ParenthesesClose},
                                 {"[",         Token::BracketOpen},
                                 {"]",         Token::BracketClose},
                                 {"{",         Token::BraceOpen},
                                 {"}",         Token::BraceClose},
                                 {"<",         Token::AngleBracketOpen},
                                 {">",         Token::AngleBracketClose},

                                 {"&&",        Token::LogicAnd},
                                 {"||",        Token::LogicOr},

                                 {"import",    Token::Import},

                                 {"class",     Token::Class},
                                 {"interface", Token::Interface},

                                 {"const",     Token::Const},
                                 {"static",    Token::Static},

                                 {"private",   Token::Private},
                                 {"protected", Token::Protected},
                                 {"public",    Token::Public}};

Token getTokenByName(const QString &value)
{
    if (!tokens.contains(value))
        return Token::Unknown;

    return tokens[value];
}

const QString &getTokenName(Token token)
{
    static QHash<Token, QString> tokenNames;

    if (tokenNames.size() == 0)
    {
        for (auto &s : tokens.keys())
            tokenNames.insert(tokens[s], s);
    }

    return tokenNames[token];
}