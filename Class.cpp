#include <QDebug>

#include "Class.h"
#include "Parser.h"

Class::Class(Class *parent, const QString &name, Token visibility, Token type) :
    m_pParent(parent),
    m_Name(name),
    m_Visibility(visibility),
    m_Type(type)
{
}

const QString &Class::getName() const
{
    return this->m_Name;
}

QString Class::getFullName() const
{
    return (this->m_pParent ? this->m_pParent->getFullName() + "." : "") + this->m_Name;
}

const QVector<Class *> &Class::getClasses() const
{
    return this->m_Classes;
}

Class *Class::addClass(const QString &name, Token visibility, Token type)
{
    auto c = new Class(this, name, visibility, type);
    this->m_Classes += c;
    return c;
}

void Class::debugPrint(int layer)
{
    qDebug() << qPrintable(this->getFullName());
    for(auto &c : this->m_Classes)
        c->debugPrint(layer + 1);
}
