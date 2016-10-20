#ifndef TREE_H
#define TREE_H

#include <QMap>
#include <QList>
#include <QString>

enum Tag_type {NONE     = 0,
               OPEN_TAG  = 1,
               CLOSE_TAG = 2,
               TEXT      = 3};

class Tree
{
    struct Node
    {
        //QMap<QString,QString> attributes;
        QString tag;
        Node* p;
        QList<Node*> child;
        Tag_type type;
        int level;

        Node();
        Node(const QString&, Tag_type);
        Node(const QString&, int);
        Node(const QString&, int, Tag_type);
    };

    Node* now;
    Node* root;
public:
    Tree();

    void            insert(const QString&, Tag_type);
    Node*           find(Node*,const QString&);
    void            print_node(Node*);
    void            print();
};

#endif // TREE_H
