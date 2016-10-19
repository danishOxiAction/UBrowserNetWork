#ifndef TREE_H
#define TREE_H

#include <QMap>
#include <QList>
#include <QString>

class Tree
{
    struct Node
    {
          //QMap<QString,QString> attributes;
          QString tag;
          Node* p;
          QList<Node*> child;
          int level;

          Node();
          Node(const QString&, int);
};

    Node* now;
    Node* root;
public:
    Tree();

    void    insert(const QString&);
    void    print_node(Node*);
    void    print();
};

#endif // TREE_H
