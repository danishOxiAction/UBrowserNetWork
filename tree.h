#ifndef TREE_H
#define TREE_H

#include "exceptions.h"
#include "node.h"

#include <functional>

#include <QString>
#include <QQueue>

enum Tag_type {TEXT             = 0,
               START_TAG        = 1,
               END_TAG          = 2,
               INDEPENDENT_TAG  = 3};

class Tree
{   
    typedef Node::Attribute Attribute;

    Node* now;
    Node* root;
public:
    class iterator // Обход в глубину
    {
        typedef QPair<QString, Node::Attribute> value;

        Node* node;
    public:
        typedef std::forward_iterator_tag iterator_category;

        iterator() :node(nullptr) {}
        iterator(Node* _node) :node(_node) {}
        iterator(const iterator& other) :node(other.node) {}

        QString&    tag_name() const { return node->tag_name; }
        Attribute&  attributes() const { return node->attributes; }

        Node&       operator  * () const { return *node; }
        Node*       operator -> () const { return node; }

        bool        operator != (const iterator& o) const { return node != o.node; }
        bool        operator == (const iterator& o) const { return node == o.node; }

        iterator&   operator ++ ()
        {
            node = node->next;
            return *this;
        }
        iterator    operator ++ (int)
        {
            Node* r = node;
            node = node->next;
            return r;
        }
    };
    friend class iterator;

    Tree() noexcept;
    ~Tree() noexcept;

    iterator            begin() const noexcept;
    iterator            end() const noexcept;

    void                push(Tag_type, const QString&, const QString&) noexcept;

    void                breadth_first_traversal(std::function<void (Node*)>) const noexcept;

    void                clear();

    void                print() const;

private:
    void                _push(Node* parent, const QString&, const QString&) noexcept;

    Node*               create_node(const QString&, const QString&) const throw( Exceptions );
    const Attribute     set_attributes(const QString&) const;
    Node*               set_prev(Node*) noexcept; // Связывает добавленный узел с предыдущим

    void                free_resoureces(Node*) noexcept;

    Node*               search(const QString&) const throw( Exceptions );

    void                _print_tree(QString&, Node*, int) const;
};

#endif // TREE_H
