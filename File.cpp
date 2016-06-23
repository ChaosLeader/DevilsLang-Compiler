#include <stdexcept>

#include "File.h"
#include "Token.h"


bool File::skipSpaces()
{
    auto oldCursor = this->cursor;
    while (this->cursor < this->rawData.size())
    {
        switch (this->rawData.at(this->cursor))
        {
            case '\n':
                this->row++;
                this->col = 1;
                this->cursor++;
                break;

            case '\t':
                this->col += 4;
                this->cursor++;
                break;

            case ' ':
            case '\r':
            case '\v':
            case '\f':
                this->col++;
                this->cursor++;
                break;

            default:
                return oldCursor != this->cursor;
        }
    }

    return false;
}

Token File::getNextToken(uint32_t &size)
{
    int pos;

    size = 0;
    if (this->cursor >= this->rawData.size())
        return Token::EndOfFile;

    size = 1;
    this->col++;

    switch (this->rawData.at(this->cursor))
    {
        case '.':
            return Token::Point;

        case ',':
            return Token::Comma;

        case ':':
            return Token::Colon;

        case ';':
            return Token::Semicolon;

        case '=':
            return Token::Equals;

        case '(':
            return Token::ParenthesesOpen;

        case ')':
            return Token::ParenthesesClose;

        case '[':
            return Token::BracketOpen;

        case ']':
            return Token::BracketClose;

        case '{':
            return Token::BraceOpen;

        case '}':
            return Token::BraceClose;

        case '<':
            return Token::AngleBracketOpen;

        case '>':
            return Token::AngleBracketClose;

        case '&': // TODO &&
            return Token::Ampersand;

        case '|': // TODO ||
            return Token::VerticalBar;

        case '/': // TODO /
            pos = this->cursor + 1;
            if (pos != this->rawData.size())
            {
                switch (this->rawData.at(pos))
                {
                    case '/':
                        while (pos + 1 < this->rawData.size() && this->rawData.at(pos + 1) != '\n')
                            pos++;
                        size = (uint32_t)(pos - this->cursor + 1);
                        this->row++;
                        this->col = 1;
                        return Token::Comment;

                    case '*':
                        //                        while(true)
                        //                        {
                        //                            if (pos >= this->rawData.size() - 1)
                        //                                throw std::runtime_error(qPrintable(QString("%1 in '%2 %3:%4'").arg("Multiline comment not closed", this->path, QString::number(this->row), QString::number(this->col))));
                        //
                        //                            switch(this->rawData.at(pos))
                        //                            {
                        //                                case '\n':
                        //                                    this->row++;
                        //                                    this->col = 1;
                        //                                    this->cursor++;
                        //                                    break;
                        //
                        //                                case '\t':
                        //                                    this->col += 4;
                        //                                    this->cursor++;
                        //                                    break;
                        //
                        //                                case '*':
                        //                                    break;
                        //                            }
                        //                        }
                        //                        while (pos < this->rawData.size() - 1 && this->rawData.at(pos) != '\n')
                        //                            pos++;
                        //
                        //                        pos = this->rawData.indexOf("*/", pos + 1);
                        //                        if (pos != -1)
                        //                            this->cursor = pos + 2;
                        break;

                    default:
                        return Token::Unknown; // TODO
                }
            }
            break;

        case '0'...'9': // TODO Not yet finished
            return Token::ReadNumber;

        case '_':
        case 'a'...'z':
        case 'A'...'Z':
            pos = this->cursor + 1;
            while (pos != this->rawData.size())
            {
                switch (this->rawData.at(pos))
                {
                    case '_':
                    case 'a'...'z':
                    case 'A'...'Z':
                    case '0'...'9':
                        pos++;
                        this->col++;
                        break;

                    default:
                    {
                        size = (uint32_t)(pos - this->cursor);
                        auto data = this->rawData.mid(this->cursor, size);

                        auto token = getTokenByName(data);
                        if (token != Token::Unknown)
                            return token;

                        return Token::ReadName;
                    }
                }
            }

        default:
            break;
    }

    return Token::Unknown;
}

void File::readTokens()
{
    while (this->cursor < this->rawData.size())
    {
        this->skipSpaces();

        RawToken s;
        s.row = this->row;
        s.col = this->col;

        uint32_t tokenSize;
        auto token = this->getNextToken(tokenSize);
        if (token == Token::EndOfFile)
            break;
        else if (token == Token::Unknown)
            throw std::runtime_error(qPrintable(QString("Unknown: %1").arg(QString(this->rawData.mid(this->cursor, 10)))));

        s.token = token;
        s.offset = this->cursor;
        s.length = tokenSize;
        this->tokens += s;

        this->cursor += tokenSize;
    }
}