#ifndef TREE_H
#define TREE_H

#include "parser.h"

#include <QVector>
#include <QString>
#include <QMap>
#include <QPair>


class Tree
{
public:
    typedef QMap<QString,QString> Attribute;

    struct Node
    {
        Node* parent;
        QVector<Node*> child;

        QString tag_name;
        QString /*Attribute*/ attributes;
    };

    Node* now;
    Node* root;

    Node*                   search_node(Node*, const QString&);
    void                    push_open_tag(const QString&);
    void                    push_text_or_close_tag(Token_type, const QString&);
public:

    Tree();

    QPair<QString,QString>  cut_on_name_and_attributes(const QString&);
    void                    push(Token_type, const QString&);
};

#endif // TREE_H
