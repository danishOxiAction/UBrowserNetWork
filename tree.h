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

        Node* next;
        Node* prev;

        QList<Node*> child;

        QString tag_name;
        Attribute attributes;
    };

    Node* now;
    Node* root;
public:
    class iterator
    {
        typedef Tree::Node Node;
        typedef QPair<QString, Attribute> value;

        Node* node;
    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef Node  value_type;
        typedef Node* pointer;
        typedef Node& reference;

        iterator() :node(nullptr) {}
        iterator(Node* _node) :node(_node) {}
        iterator(const iterator& other) :node(other.node) {}

        QString&    tag_name() const { return node->tag_name; }
        Attribute&  attributes() const { return node->attributes; }

        Node&       operator  * () const { return *node; }
        Node*      operator -> () const { return node; }

        bool        operator != (const iterator& o) const { return node != o.node; }
        bool        operator == (const iterator& o) const { return node == o.node; }

        iterator&   operator ++ ()
        {
            node = node->next;
        }
        iterator    operator ++ (int)
        {
            node = node->next;
        }
    };

    friend class iterator;

    Tree() noexcept;
    ~Tree() noexcept;

    iterator            begin() const noexcept;
    iterator            end() const noexcept;

    void                push(Tag_type, const QString&, const QString&) noexcept;

    //void                traversal();

    void                clear();

    void                print() const;

private:
    Node*               create_node(const QString&, const QString&) const throw( Exceptions );

    Node*               set_next(Node*) noexcept;
    Node*               set_prev(Node*) noexcept;

    void                free_resoureces(Node*) noexcept;

    void                _push(Node* parent, const QString&, const QString&) noexcept;
    Node*               search(const QString&) const throw( Exceptions );

    const Attribute     set_attributes(const QString&) const;

    void                _print_tree(QString&, Node*, int) const;
};

#endif // TREE_H
