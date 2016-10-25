#include "tree.h"

Tree::Node* Tree::search_node(Node* node, const QString& name)
{
    if(node->tag_name == name)
    {
        return node->parent;
    }
    else
    {
        search_node(node->parent,name);
    }
}

Tree::Tree()
{
    root = nullptr;
    now = nullptr;
}

QPair<QString, QString> Tree::cut_on_name_and_attributes(const QString& tag)
{
    QString name;
    QString attributes;

    bool is_name = true;

    for(int i = 0; i < tag.size(); i++)
    {
        if(tag[i] == ' ') is_name = false;

        if(is_name)
            name += tag[i];
        else
            attributes += tag[i];
    }

    return QPair<QString,QString>(name, attributes);
}

void Tree::push(Token_type type, const QString& tag)
{
    if(type == START_TAG)
        push_open_tag(tag);
    else
        push_text_or_close_tag(type, tag);
}

void Tree::push_open_tag(const QString & tag)
{
    QPair<QString,QString> _tag = cut_on_name_and_attributes(tag);

    if(root == nullptr)
    {
        root = new Node;

        root->parent = nullptr;
        root->tag_name = _tag.first;
        root->attributes = _tag.second;

        now = root;
    }
    else
    {
        now->child.push_front(new Node);

        Node* temp = now->child.front();

        temp->parent = now;
        temp->tag_name = _tag.first;
        temp->attributes = _tag.second;

        now = temp;

        temp = nullptr;
    }
}

void Tree::push_text_or_close_tag(Token_type type, const QString& tag)
{
    if(type == TEXT)
    {
        now->child.push_front(new Node);

        Node* temp = now->child.front();

        temp->parent = now;
        temp->tag_name = tag;

        now = temp;

        temp = nullptr;
    }
    else // type == END_TAG
    {
        now = search_node(now,tag);
    }
}
