#pragma once

#include <QVector>

#include "Class.h"

class File;

class Package : public Class
{
private:
    QVector<File *> m_Files;
    QVector<Package *> m_Packages;

public:
    Package(const QString &name);
};
