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
    Class m_Root;

    void parseTokens(File &file);

public:
    Parser();
    QHash<QString, File> m_Files;

    void readProject(const QString &rootPath, const QString &package);
    Class *getRoot();
};
