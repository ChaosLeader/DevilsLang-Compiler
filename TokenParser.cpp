#include <QDebug>
#include <QStack>

#include "Parser.h"
#include "Token.h"

class StateMachineContext
{
private:
    Parser *m_pParser;
    File *m_pFile;
    int m_Current;
    QStack<RawToken> m_Stack;

    QStack<Token> m_Scope;
    QStack<Class *> m_ScopeContainer;
    Token m_Visibility;

public:
    StateMachineContext(Parser *parser, File *file, int current = 0) :
        m_pParser(parser),
        m_pFile(file),
        m_Current(current)
    {
        this->setScope(Token::Unknown);
        this->setScopeContainer(this->m_pFile->getPackage());
    }

    Class *addClass(const QString &name)
    {
        return this->getScopeContainer()->addClass(name, this->m_Visibility, this->getScope());
    }

    Parser *getParser()
    {
        return this->m_pParser;
    }

    bool isEmpty() const
    {
        return this->m_Current >= this->m_pFile->tokens.size();
    }

    const RawToken &getNextToken()
    {
        return this->m_pFile->tokens[this->m_Current++];
    }

    int getTokenCursor()
    {
        return this->m_Current;
    }

    void setTokenCursor(int pos)
    {
        this->m_Current = pos;
    }

    File *getFile() const
    {
        return this->m_pFile;
    }

    char getChar(int offset) const
    {
        return this->getFile()->rawData[offset];
    }

    QString getString(int offset, int length) const
    {
        return this->getFile()->rawData.mid(offset, length);
    }

    bool isStackEmpty()
    {
        return this->m_Stack.empty();
    }

    void push(const RawToken &s)
    {
        this->m_Stack.push(s);
    }

    RawToken pop()
    {
        return this->m_Stack.pop();
    }

    const RawToken &top()
    {
        return this->m_Stack.top();
    }

    void reset()
    {
        this->m_Visibility = Token::Private;
    }

    void setScope(Token s)
    {
        this->m_Scope.push(s);
    }

    Token getScope()
    {
        return this->m_Scope.top();
    }

    void backtrackScope()
    {
        this->m_Scope.pop();
    }

    void setScopeContainer(Class *c)
    {
        this->m_ScopeContainer += c;
    }

    Class *getScopeContainer()
    {
        return this->m_ScopeContainer.top();
    }

    void backtrackScopeContainer()
    {
        this->m_ScopeContainer.pop();
    }

    void setVisibility(Token v)
    {
        this->m_Visibility = v;
    }

    Token getVisibility() const
    {
        return this->m_Visibility;
    }
};

void parseImports(StateMachineContext &context);
void q0(StateMachineContext &context, bool newLayer = true);
void q1(StateMachineContext &context);
void q2(StateMachineContext &context);
void q3(StateMachineContext &context);
void q4(StateMachineContext &context);
void q5(StateMachineContext &context);
void q6(StateMachineContext &context);
void q7(StateMachineContext &context);
void q8(StateMachineContext &context);
void q9(StateMachineContext &context);
void q10(StateMachineContext &context);
void q11(StateMachineContext &context);
void q12(StateMachineContext &context);
void q13(StateMachineContext &context);
void q14(StateMachineContext &context);
void q15(StateMachineContext &context);
void q16(StateMachineContext &context);
void q17(StateMachineContext &context);
void q18(StateMachineContext &context);
void q19(StateMachineContext &context);

void error(StateMachineContext &context, const RawToken &token, const QString &msg)
{
//    int line = 1;
//    int column = 1;
//    int current = 0;
//    while (current < token.offset)
//    {
//        auto c = context.getChar(current);
//        if (c == '\n')
//        {
//            line++;
//            column = 1;
//        } else
//            column += c == '\t' ? 4 : 1;
//        current++;
//    }
//
//    throw std::runtime_error(qPrintable(QString("%1 in '%2 %3:%4'").arg(msg, context.getFile().path, QString::number(line), QString::number(column))));
    throw std::runtime_error(qPrintable(QString("%1 in '%2 %3:%4'").arg(msg, context.getFile()->path, QString::number(token.row), QString::number(token.col))));
}

void errorUnexpected(StateMachineContext &context, const RawToken &token)
{
    QString msg;
    switch (token.token)
    {
        case Token::ReadName:
        case Token::ReadNumber:
            msg = context.getString(token.offset, token.length);
            break;

        default:
            msg = getTokenName(token.token);
            break;
    }

    error(context, token, QString("Unexpected '%1'").arg(msg));
}

void errorMissing(StateMachineContext &context, RawToken token, const QString &name)
{
    token.offset += token.length;
    error(context, token, QString("Missing '%1'").arg(name));
}

void Parser::parseTokens(File *file)
{
    StateMachineContext context(this, file);

    parseImports(context);

    while (!context.isEmpty())
    {
        q0(context);
    }

    if (!context.isStackEmpty())
    {
        auto &s = context.top();
        switch(s.token)
        {
            case Token::BraceOpen:
                errorMissing(context, s, "}");
                break;

            default:
                errorUnexpected(context, s);
                break;
        }
    }
}

void Parser::setRootPath(const QString &rootPath)
{
    this->m_RootPath = rootPath;
}

void parseImports(StateMachineContext &context)
{
    while(true)
    {
        bool parsed = false;
        auto currentToken = context.getTokenCursor();

        do
        {
            if (context.isEmpty() || context.getNextToken().token != Token::Import)
                break;

            if (context.isEmpty())
                break;

            QString import;

            READ_NEXT:
            auto &s = context.getNextToken();
            import += context.getString(s.offset, s.length);

            if (context.isEmpty())
                break;

            auto &s2 = context.getNextToken();
            if (s2.token == Token::Point)
            {
                import += '.';
                goto READ_NEXT;
            }

            if (s2.token != Token::Semicolon)
                break;

            context.getFile()->impots += import;
            parsed = true;

            context.getParser()->readPackage(import);
        } while(false);

        if (!parsed)
        {
            context.setTokenCursor(currentToken);
            break;
        }
    }
}

/*
 * Initial parsing function
 */
void q0(StateMachineContext &context, bool newLayer)
{
    while (!context.isEmpty())
    {
        context.reset();
        const auto &s = context.getNextToken();
        switch (s.token)
        {
            case Token::BraceOpen:
                context.push(s);
                if (!newLayer)
                    q0(context, false);
                break;

            case Token::BraceClose:
                if (context.isStackEmpty() || context.pop().token != Token::BraceOpen)
                    errorUnexpected(context, s);
                return;

                //region parse visibility
            case Token::Private:
                context.setVisibility(Token::Private);
                goto CASE_VISIBILITY;

            case Token::Protected:
                context.setVisibility(Token::Protected);
                goto CASE_VISIBILITY;

            case Token::Public:
                context.setVisibility(Token::Public);
                goto CASE_VISIBILITY;

            CASE_VISIBILITY:
                q1(context);
                break;
                //endregion

                //region parse scope
            case Token::Interface:
                if (context.getScope() == Token::Interface)
                    errorUnexpected(context, s);
                context.setScope(Token::Interface);
                goto CASE_SCOPE;

            case Token::Class:
                if (context.getScope() == Token::Interface)
                    errorUnexpected(context, s);
                context.setScope(Token::Class);
                goto CASE_SCOPE;

            CASE_SCOPE:
                q2(context);
                context.backtrackScope();
                break;
                // endregion

            default:
                errorUnexpected(context, s);
                break;
        }
    }
}

/*
 * Visibility parsed, now parse class, interface or function
 */
void q1(StateMachineContext &context)
{
    const auto &s = context.getNextToken();
    switch (s.token)
    {
        //region parse scope
        case Token::Interface:
            if (context.getScope() == Token::Interface)
                errorUnexpected(context, s);
            context.setScope(Token::Interface);
            goto CASE_SCOPE;

        case Token::Class:
            if (context.getScope() == Token::Interface)
                errorUnexpected(context, s);
            context.setScope(Token::Class);
            goto CASE_SCOPE;

        CASE_SCOPE:
            q2(context);
            context.backtrackScope();
            break;
            // endregion

        default:
            errorUnexpected(context, s);
            break;
    }
}

/*
 * All stuff read, read file interface / class name
 */
void q2(StateMachineContext &context)
{
    const auto &s = context.getNextToken();
    switch (s.token)
    {
        case Token::ReadName:
            context.setScopeContainer(context.addClass(context.getString(s.offset, s.length)));
            q0(context);
            context.backtrackScopeContainer();
            break;

        default:
            errorUnexpected(context, s);
            break;
    }
}

void q3(StateMachineContext &context)
{
}

void q4(StateMachineContext &context)
{
}

void q5(StateMachineContext &context)
{
}

void q6(StateMachineContext &context)
{
}

void q7(StateMachineContext &context)
{
}

void q8(StateMachineContext &context)
{
}

void q9(StateMachineContext &context)
{
}
