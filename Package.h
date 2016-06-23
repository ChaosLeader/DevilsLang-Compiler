#pragma once

#include <QVector>

class Class;
class File;

class Package
{
private:
    QVector<File *> m_Files;
    QVector<Package *> m_Packages;
    QVector<Class *> m_Classes;

public:
    Package(const QString &name);
};
