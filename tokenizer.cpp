#include "tokenizer.h"

#include <QDebug>

Tokenizer::Tokenizer(QString str)
    :html(str)
{
    tree = new Tree;
}

void Tokenizer::new_html_page(QString new_html)
{
    html = new_html;

    tokens.clear();
    delete tree;
    tree = new Tree;
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

                it = --c; // чтобы не потерять тег
            }
        it++;
    }

    make_tree();
}

QString::iterator Tokenizer::skip_html_tag(QString::iterator begin, QString::iterator end) const
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

QString::iterator Tokenizer::skip_text(QString::iterator begin, QString::iterator end) const
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

    QString tag;


    while(it != end)
    {
        if(*it == '/')
        {
            if(it == begin)
            {
                type = END_TAG;
                it++;
            }
            else if(it+1 == end)
            {
                // Если встречается тег типа <* />, то для него создаётся закрывающийся
                tokens.push_back(Token(START_TAG,tag));
                tokens.push_back(Token(END_TAG,tag));
                return;
            }
        }

        if(*it == '!' && it == begin)   return; // комменты, DOCTYPE etc

        tag += *it;

        it++;
    }

    tokens.push_back(Token(type,tag));
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

void Tokenizer::make_tree()
{
    for(int i = 0; i < tokens.size(); i++)
    {
        tree->push(tokens[i].first, tokens[i].second);
    }
}

QString Tokenizer::print_tokens() const
{
    QString _tokens = "";
    for(int i = 0; i < tokens.size(); i++)
    {
        _tokens += tokens[i].second + "\n";
    }
    return _tokens;
}

QString Tokenizer::print_tree() const
{
    return tree->print_tree();
}
