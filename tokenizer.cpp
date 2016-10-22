#include "tokenizer.h"

#include <QDebug>

Tokenizer::Tokenizer(QString str)
    :html(str) {}

void Tokenizer::new_html_page(QString new_html)
{
    html = new_html;
}

void Tokenizer::start_tokenization()
{
    QString::iterator it = html.begin();

    while(it != html.end())
    {
        if(*it == '<')
        {
            QString::iterator c = skip_html_tag(++it, html.end()); // it = '<'
            open_tag_token(it,c);
            it = c;
        }
        else
            if(it->isLetterOrNumber())
            {
                QString::iterator c = skip_text(it, html.end());
                text_token(it,c);
                it = --c;
            }
        it++;
    }
}

QString::iterator Tokenizer::skip_html_tag(QString::iterator begin, QString::iterator end)
{
    QString::iterator it = begin;
    while(it != end)
    {
        if(*it == '>')
        {
            return it;
        }

        it++;
    }

    return it; // end
}

QString::iterator Tokenizer::skip_text(QString::iterator begin, QString::iterator end)
{
    QString::iterator it = begin;
    while(it != end)
    {
        if(*it == '<')
        {
            return it;
        }

        it++;
    }

    return it; // end
}

void Tokenizer::open_tag_token(QString::iterator begin, QString::iterator end)
{
    QString::iterator it = begin;

    Token_type type = START_TAG;
    QString token_name;

    while(it != end)
    {
        if(*it == '/')
        {
            type = END_TAG;
            it++;
        }

        token_name += *it;

        it++;
    }

    tokens.push_back(Token(type,token_name));
}

void Tokenizer::text_token(QString::iterator begin, QString::iterator end)
{
    QString::iterator it = begin;

    QString token_name;

    while(it != end)
    {
        token_name += *it;

        it++;
    }

    tokens.push_back(Token(TEXT,token_name));
}

void Tokenizer::print_tokens()
{
    for(int i = 0; i < tokens.size(); i++)
    {
        qDebug() << "Type: " << tokens[i].first << "; Name: " << tokens[i].second << endl;
    }
}