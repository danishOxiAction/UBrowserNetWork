#include "tokenizer.h"

#include <QApplication>
#include <QFile>
#include <QString>
#include <QDebug>

int main(/*int argc, char *argv[]*/)
{
    //QApplication a(argc, argv);

    QFile doc("index.html");

    if(doc.open(QFile::ReadOnly | QFile::Text))
    {
        QString str = doc.readAll();

        Tokenizer t(str);
        t.start_tokenization();
        t.print_tokens();

        doc.close();
    }
    else
    {
        qDebug() << "Файл не был открыт";
    }

    //return a.exec();
}
