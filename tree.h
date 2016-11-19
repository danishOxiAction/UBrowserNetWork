#ifndef TREE_H
#define TREE_H

#include "exceptions.h"

#include <QList>
#include <QString>
#include <QMap>
#include <QPair>


enum Tag_type {TEXT             = 0,
               START_TAG        = 1,
               END_TAG          = 2,
               INDEPENDENT_TAG  = 3};

class Tree
{
public:
    typedef QMap<QString,QString> Attribute;

    struct Node
    {
        Node* parent;
        QList<Node*> child;

        QString tag_name;
        Attribute attributes;
    };

    Node* now;
    Node* root;
public:
    Tree() noexcept;

    void    push(Tag_type, const QString&, const QString&) noexcept;

private:
    Node*   create_node(const QString&, const QString&) const throw( Exceptions );

    void    _push(Node* parent, const QString&, const QString&) throw( Exceptions );
    Node*   search(const QString&) const throw( Exceptions );
};

#endif // TREE_H
