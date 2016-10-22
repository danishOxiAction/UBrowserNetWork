#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <QList>
#include <QPair>
#include <QString>

enum Token_type {TEXT           = 0,
                 START_TAG      = 1,
                 END_TAG        = 2};

class Tokenizer
{
    typedef QPair<Token_type, QString> Token;

    QString html;

    QList< Token > tokens;

public:
    Tokenizer(QString = "");
    void                    new_html_page(QString);
    void                    start_tokenization();
    QString::iterator       skip_html_tag(QString::iterator, QString::iterator);
    QString::iterator       skip_text(QString::iterator, QString::iterator);
    void                    open_tag_token(QString::iterator, QString::iterator);
    void                    text_token(QString::iterator, QString::iterator);

    void                    print_tokens();
};

#endif // TOKENIZER_H
