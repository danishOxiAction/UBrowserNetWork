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
    ~Tree() noexcept;

    void                push(Tag_type, const QString&, const QString&) noexcept;

    void                clear();

    void                print() const;
private:
    Node*               create_node(const QString&, const QString&) const throw( Exceptions );

    void                free_resoureces(Node*) noexcept;

    void                _push(Node* parent, const QString&, const QString&) noexcept;
    Node*               search(const QString&) const throw( Exceptions );

    const Attribute     set_attributes(const QString&) const;

    void                _print_tree(QString&, Node*, int) const;
};

#endif // TREE_H
