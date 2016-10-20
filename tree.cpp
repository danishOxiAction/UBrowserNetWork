#include "tree.h"
#include <QDebug>
#include <QTextStream>

Tree::Node::Node()
{
    tag = "";
    p = nullptr;
    type = NONE;
    level = 0;
}

Tree::Node::Node(const QString& tag_name, Tag_type _type)
{
    tag = tag_name;
    p = nullptr;
    type = _type;
    level = 0;
}


Tree::Node::Node(const QString& tag_name, int _level)
{
    tag = tag_name;
    p = nullptr;
    type = NONE;
    level = _level;
}

Tree::Node::Node(const QString& tag_name, int _level, Tag_type _type)
{
    tag = tag_name;
    p = nullptr;
    type = _type;
    level = _level;
}


Tree::Tree()
{
    root = nullptr;
    now = nullptr;
}

void Tree::insert(const QString& tag_name, Tag_type type)
{
    if(root == nullptr)
    {
        root = new Node(tag_name,0,type);
        now = root;
    }
    else
    {
        if(type == CLOSE_TAG)
        {
            if(now != nullptr)
            {
                now = find(now,tag_name);
            }
        }
        else
        {
            if(now != nullptr)
            {
                now->child.push_back(new Node(tag_name,now->level,type));
                now->child.back()->p=now;
                now = now->child.back();
                now->level++;
            }
        }
    }
}

Tree::Node* Tree::find(Node* node, const QString& tag_name)
{
    if(node->tag == tag_name && node->type == OPEN_TAG)
    {
        return node->p;
    }
    else
    {
        find(node->p,tag_name);
    }
    return nullptr;
}

void Tree::print_node(Tree::Node* node)
{
    QTextStream sout(stdout);

    for(int i = 0; i < node->level; i++)
    {
        sout << " ";
    }
    sout << node->tag << "\n";

    for(int i = 0; i < node->child.size(); i++)
    {
        print_node(node->child[i]);
    }
}

void Tree::print()
{
    print_node(root);
}
