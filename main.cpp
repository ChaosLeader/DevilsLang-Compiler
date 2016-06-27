#include <QDebug>

#include "Parser.h"

int main(int argc, char **argv)
{
    try
    {
        if (argc < 3)
            throw std::runtime_error("Invalid arguments");

        QString rootPath(argv[1]);
        rootPath += "/";

        QString entrypoint = argv[2];
        auto pos = entrypoint.lastIndexOf('.');
        if (pos == -1)
            throw std::runtime_error("Expected entry point format '<package>.<class>'");

        auto package = entrypoint.mid(0, pos);
        auto entryclass = entrypoint.mid(pos + 1);

        Parser parser;
        parser.setRootPath(rootPath);
        parser.readPackage(package);

        for (auto &p : parser.m_Packages)
            p->debugPrint();
    }
    catch (std::exception &e)
    {
        qDebug() << e.what();
        return 1;
    }
    return 0;
}
