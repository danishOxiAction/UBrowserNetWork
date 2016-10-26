#include "tokenizer.h"

#include <QApplication>
#include <QTextStream>
#include <QLabel>
#include <QFile>
#include <QDebug>

#include <QTextStream>

void print_tree(int level, Tree::Node* node)
{
    QTextStream str(stdout);

    if(node == nullptr) return;

    for(int i = 0; i < level; i++)
    {
        str << "_";
    }
    str << node->tag_name << "\n";

    level++;
    for(int i = 0; i < node->child.size(); i++)
    {
        print_tree(level, node->child[i]);
    }
}

int main(/*int argc, char *argv[]*/)
{
    //QApplication app(argc, argv);

    QFile file("/home/sm4ll_3gg/html.htm");
    if(file.open(QFile::ReadOnly | QFile::Text))
    {
        QString str = file.readAll();
        str.replace("\n","");
        str.replace("\t","");

        Tokenizer tokenizer(str);
        tokenizer.start_tokenization();
        //tokenizer.print_tokens();
        print_tree(0,tokenizer.tree->root);

        file.close();
    }
    else
    {
        qDebug() << "File is not open";
    }

    //    return app.exec();
}
