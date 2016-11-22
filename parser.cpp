#include "parser.h"
//#include <QDebug>
//enum Tag_type {TEXT             = 0,
//               START_TAG        = 1,
//               END_TAG          = 2,
//               INDEPENDENT_TAG  = 3};

//class Tree
//{
//public:
//    Tree(){}
//    void push(Tag_type token_type, QString token_name, QString token_attributes){
//        switch (token_type) {
//        case TEXT:
//            qDebug()<< "Type: " << "TEXT";
//            break;
//        case START_TAG:
//            qDebug()<< "Type: " << "START_TAG";
//            break;
//        case END_TAG:
//            qDebug()<< "Type: " << "END_TAG";
//            break;
//        case INDEPENDENT_TAG:
//            qDebug()<< "Type: " << "INDEPENDENT_TAG";
//            break;
//        }
//        qDebug() <<"Tag: " << token_name << ", attributes: " << token_attributes << endl;
//    }
//};

Parser::Parser(QString raw_html)
{
//    Tree tree; //MFD

    html = raw_html;
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
