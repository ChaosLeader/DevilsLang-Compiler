#pragma once

#include <QByteArray>
#include <QString>
#include <QHash>
#include <QVector>

#include "Class.h"
#include "Package.h"
#include "File.h"

class Parser
{
    friend class StateMachineContext;

private:
    QString m_RootPath;

    void parseTokens(File *file);

public:
    Parser();
    QHash<QString, File *> m_Files;
    QHash<QString, Package *> m_Packages;

    void setRootPath(const QString &rootPath);
    void readPackage(const QString &package);
};
