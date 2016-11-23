#include "parser.h"

Parser::Parser(QString raw_html)
{
        html = raw_html;
        html.replace("\n", "");
        html.replace("\t", "");
}

void Parser::parse()
{
    int pointer = 0;

    QRegExp reg_text("([^><]*)");
    QRegExp reg_scope("</?([^></]+)/?>");
    QRegExp reg_tag("([\\S]+)");
    QRegExp reg_attributes("\\s(.*)");
    int limit = html.size();
    while((pointer = reg_scope.indexIn( html, pointer )) != -1 && pointer < limit)
    {
        QString scope = reg_scope.cap(1);
        Tag_type type;
        QString tag;
        QString attributes = "";

        reg_tag.indexIn(scope, 0);
        tag = reg_tag.cap(1);

        reg_attributes.indexIn(scope, 0);
        attributes = reg_attributes.cap(1);

        QString full_scope = reg_scope.cap(0);

        if (full_scope[1]=='/')
            type = END_TAG;
        else if(full_scope[full_scope.size()-2] == '/')
            type = INDEPENDENT_TAG;
        else
            type = START_TAG;
        tree.push(type, tag, attributes);

        pointer+=full_scope.size();

        if (reg_text.indexIn(html, pointer) != -1 && reg_text.cap(1).size() != 0)
        {
            type = TEXT;
            tag = reg_text.cap(1);
            attributes = "";
            tree.push(type, tag, attributes);
        }
    }
}

void Parser::print_tree()
{
    tree.print();
}

