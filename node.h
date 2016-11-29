#ifndef NODE_H
#define NODE_H

#include <QList>
#include <QMap>

struct Node
{
    typedef QMap<QString,QString> Attribute;

    Node* parent;

    Node* next;
    Node* prev;

    QList<Node*> child;

    QString tag_name;
    Attribute attributes;
};

#endif // NODE_H
