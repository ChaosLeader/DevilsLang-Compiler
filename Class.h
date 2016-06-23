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

    QVector<Class *> m_Classes;

public:
    Class(const QString &name, Token visibility, Token type);

    const QString &getName() const;
    const QVector<Class *> &getClasses() const;

    Class *addClass(const QString &name, Token visibility, Token type);

    void debugPrint(int layer = 0);
};
