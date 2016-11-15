#include "tokenizer.h"
#include "mainwindow.h"

#include <QApplication>
#include <QTextStream>
#include <QLabel>
#include <QFile>
#include <QDebug>

#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;

//    QFile file("/home/sm4ll_3gg/html.htm");
//    if(file.open(QFile::ReadOnly | QFile::Text))
//    {
//        QString str = file.readAll();
//        str.replace("\n","");
//        str.replace("\t","");

//        Tokenizer tokenizer(str);
//        tokenizer.start_tokenization();
//        //tokenizer.print_tokens();
//        print_tree(0,tokenizer.tree->root);

//        file.close();
//    }
//    else
//    {
//        qDebug() << "File is not open";
//    }

    window.show();

    return app.exec();
}
