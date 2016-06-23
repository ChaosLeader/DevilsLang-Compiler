#include <QFile>
#include <QDebug>
#include <QDir>
#include <QDirIterator>

#include "Parser.h"

Parser::Parser() :
    m_Root("<root>", Token::Public, Token::Class)
{
}

void Parser::readProject(const QString &rootPath, const QString &package)
{
    QString fileName = package;
    fileName.replace('.', '/');
    fileName += ".dl";

    QString path = rootPath;
    auto pos = fileName.lastIndexOf('/');
    if (pos != -1)
    {
        path += fileName.mid(0, pos);
        fileName = fileName.mid(pos + 1, fileName.length() - (pos + 1));
    }

    int importCount = 0;
    QDirIterator it(path, QStringList() << fileName, QDir::Files);
    while (it.hasNext())
    {
        importCount++;

        auto filePath = it.next();
        auto tmpLen = rootPath.length();
        QString p = filePath.mid(tmpLen, filePath.length() - tmpLen - 3);
        p.replace('/', '.').replace('\\', '.');

        if (this->m_Files.contains(p))
            continue;

        File tmp;
        tmp.path = filePath;
        tmp.cursor = 0;
        tmp.row = 1;
        tmp.col = 1;

        QFile file(tmp.path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            throw std::runtime_error(qPrintable(QString("Error opening file '%1'").arg(tmp.path)));

        tmp.rawData = file.readAll();
        file.close();

        auto &data = *this->m_Files.insert(p, tmp);
        data.readTokens();
        parseTokens(data);
    }

    if (importCount == 0)
        throw std::runtime_error(qPrintable(QString("Import '%1' has not been found.").arg(package)));
}

Class *Parser::getRoot()
{
    return &this->m_Root;
}
