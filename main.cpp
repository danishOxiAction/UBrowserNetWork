#include "tokenizer.h"

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

        Tokenizer tokenizer("index.html");
        tokenizer.start_tokenization();
        tokenizer.print_tokens();
    }
    else
    {
        qDebug() << "File is not open";
    }
    index.close();

    //    return app.exec();
}
