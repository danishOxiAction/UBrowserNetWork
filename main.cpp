#include "htmlparser.h"

#include <QApplication>
#include <QTextStream>
#include <QLabel>
#include <QFile>
#include <QDebug>

int main(/*int argc, char *argv[]*/)
{
    //QApplication app(argc, argv);

    QFile index("index.html");
    if(index.open(QFile::ReadOnly | QFile::Text))
    {
        QString str = index.readAll();

        HtmlParser parser;
        parser.parse(str.begin(),str.end());
        parser.print();
    }
    else
    {
        qDebug() << "File is not open";
    }
    index.close();

    //    return app.exec();
}
