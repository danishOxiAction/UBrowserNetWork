#ifndef NODE_H
#define NODE_H

#include "attributes.h"

#include <QList>

struct Node
{
    Node* parent;

    Node* next;
    Node* prev;

    QList<Node*> child;

    QString     tag_name;
    Attributes  attributes;
};

#endif // NODE_H
