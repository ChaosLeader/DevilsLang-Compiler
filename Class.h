#pragma once

#include <QString>
#include <QVector>

#include "Token.h"

class Class
{
protected:
    QString m_Name;
    Token m_Visibility;
    Token m_Type;

    Class *m_pParent;
    QVector<Class *> m_Classes;

public:
    Class(Class *parent, const QString &name, Token visibility, Token type);

    const QString &getName() const;
    QString getFullName() const;
    const QVector<Class *> &getClasses() const;

    Class *addClass(const QString &name, Token visibility, Token type);

    void debugPrint(int layer = 0);
};
