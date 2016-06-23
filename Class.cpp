#include <QDebug>

#include "Class.h"
#include "Parser.h"

Class::Class(const QString &name, Token visibility, Token type) :
    m_Name(name),
    m_Visibility(visibility),
    m_Type(type)
{
}

const QString &Class::getName() const
{
    return this->m_Name;
}

const QVector<Class *> &Class::getClasses() const
{
    return this->m_Classes;
}

Class *Class::addClass(const QString &name, Token visibility, Token type)
{
    auto c = new Class(name, visibility, type);
    this->m_Classes += c;
    return c;
}

void Class::debugPrint(int layer)
{
    char *visibility, *type;

    switch(this->m_Visibility)
    {
        case Token::Private:
            visibility = (char *)"private";
            break;

        case Token::Protected:
            visibility = (char *)"protected";
            break;

        case Token::Public:
            visibility = (char *)"public";
            break;
    }

    switch(this->m_Type)
    {
        case Token::Class:
            type = (char *)"class";
            break;

        case Token::Interface:
            type = (char *)"interface";
            break;
    }

    qDebug() << qPrintable(QString().leftJustified(layer * 2, ' ')) << visibility << type << qPrintable(this->m_Name);
    qDebug() << qPrintable(QString().leftJustified(layer * 2, ' ')) << "{";
    for(auto &c : this->m_Classes)
        c->debugPrint(layer + 1);
    qDebug() << qPrintable(QString().leftJustified(layer * 2, ' ')) << "}";
}
