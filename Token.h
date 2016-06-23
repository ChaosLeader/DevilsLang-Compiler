#pragma once

#include <QHash>
#include <QString>

enum class Token
{
    Unknown,
    EndOfFile,
    Comment,
    ReadName,
    ReadNumber,
    Point,
    Comma,
    Colon,
    Semicolon,
    Equals,
    Ampersand,
    VerticalBar,
    ParenthesesOpen,
    ParenthesesClose,
    BracketOpen,
    BracketClose,
    BraceOpen,
    BraceClose,
    AngleBracketOpen,
    AngleBracketClose,
    LogicAnd,
    LogicOr,
    Import,
    Class,
    Interface,
    Const,
    Static,
    Private,
    Protected,
    Public,
};

inline uint qHash(const Token &key)
{
    return (uint)key;
}

struct RawToken
{
    Token token;
    int offset;
    int length;
    int row;
    int col;
};

Token getTokenByName(const QString &value);
const QString &getTokenName(Token token);
