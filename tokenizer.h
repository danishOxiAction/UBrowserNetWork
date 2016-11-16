#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "parser.h"
#include "tree.h"

#include <QList>
#include <QPair>
#include <QString>

class Tokenizer
{
public:
    typedef QPair<Token_type, QString> Token;

    QString html;

    QList< Token > tokens;

    Tree* tree;
public:
    Tokenizer(QString = "");

    void                    new_html_page(QString);
    void                    start_tokenization();
    QString::iterator       skip_html_tag(QString::iterator, QString::iterator) const;
    QString::iterator       skip_text(QString::iterator, QString::iterator) const;
    void                    open_tag_token(QString::iterator, QString::iterator);
    void                    text_token(QString::iterator, QString::iterator);

    void                    make_tree();

    QString                 print_tokens() const;
    QString                 print_tree() const;
};

#endif // TOKENIZER_H
