#pragma once

#include <QVector>

#include "Parser.h"

class Class;
class Package;

class File
{
private:
    Package *m_pPackage;

    QVector<Class *> m_Classes;
    QVector<Package *> m_Imports;

public:
    QVector<RawToken> tokens;
    QVector<QString> impots;
    QByteArray rawData;
    QString path;
    int cursor, row, col;

    File(Package *package);

    Package *getPackage() const;

    bool skipSpaces();
    Token getNextToken(uint32_t &size);

    void readTokens();
};
