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

        Parser parser;
        parser.readProject(rootPath, argv[2]);

        parser.getRoot()->debugPrint();
    }
    catch (std::exception &e)
    {
        qDebug() << e.what();
        return 1;
    }
    return 0;
}
