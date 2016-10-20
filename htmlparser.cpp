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
            it = c;
        }
//        else
//            if(it->isLetterOrNumber())
//            {
//                QString::iterator c = skip_text(it,end);
//                parse_text(it,c);
//                it = c;
//            }

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
    Tag_type type = OPEN_TAG;
    if(begin != end)
    {
        if(*begin =='/')
        {
            type = CLOSE_TAG;
            it++;
        }
    }

    while(it != end)
    {
        tag_name += *it;
        it++;
    }

    tree->insert(tag_name,type);
}

QString::iterator HtmlParser::skip_text(QString::iterator begin, QString::iterator end)
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
    return it;
}

void HtmlParser::parse_text(QString::iterator begin, QString::iterator end)
{
    QString::iterator it = begin;
    QString str;
    while(it != end)
    {
        str += *it;
        it++;
    }
    tree->insert(str,TEXT);
}
