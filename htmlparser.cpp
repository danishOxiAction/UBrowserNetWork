#include "htmlparser.h"
#include <QDebug>

HtmlParser::HtmlParser()
{
    tree = new Tree;
}

HtmlParser::~HtmlParser()
{
    delete tree;
}

void HtmlParser::parse(QString::iterator begin, QString::iterator end)
{
    QString::iterator it = begin;

    while(it != end)
    {     
        if(*it == '<')
        {
            QString::iterator c = skip_tag(++it,end);
            parse_tag(it,c);
        }

        it++;
    }
}

QString::iterator HtmlParser::skip_tag(QString::iterator begin, QString::iterator end)
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
    return end;
}

void HtmlParser::parse_tag(QString::iterator begin, QString::iterator end)
{
    QString::iterator it = begin;

    QString tag_name;
    while(it != end)
    {
        tag_name += *it;
        it++;
    }

    tree->insert(tag_name);
}
