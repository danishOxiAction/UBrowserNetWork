#ifndef HTMLPARSER_H
#define HTMLPARSER_H

#include <tree.h>

#include <QMainWindow>
#include <QString>

class HtmlParser
{ 
    Tree* tree;
public:
    HtmlParser();
    ~HtmlParser();

    void                    parse(QString::iterator, QString::iterator);
    QString::iterator       skip_tag(QString::iterator, QString::iterator);
    void                    parse_tag(QString::iterator, QString::iterator);
    QString::iterator       skip_text(QString::iterator, QString::iterator);
    void                    parse_text(QString::iterator, QString::iterator);
    void                    print()
    {
        tree->print();
    }
};

#endif // HTMLPARSER_H
