#ifndef TREE_H
#define TREE_H

#include "parser.h"

#include <QList>
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
        QList<Node*> child;

        QString tag_name;
        QString /*Attribute*/ attributes;
    };

    Node* now;
    Node* root;

    void                    search_node(Node*, const QString&);
    void                    push_open_or_close_tag(Token_type, const QString&);
    void                    push_text_tag(const QString&);
public:

    Tree();

    QPair<QString,QString>  cut_on_name_and_attributes(const QString&);
    void                    push(Token_type, const QString&);
};

#endif // TREE_H
