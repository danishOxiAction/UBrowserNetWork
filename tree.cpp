#include "tree.h"
#include <QDebug>
#include <QTextStream>

Tree::Node::Node()
{
    tag = "";
    p = nullptr;
    level = 0;
}

Tree::Node::Node(const QString& tag_name, int _level)
{
    tag = tag_name;
    p = nullptr;
    level = _level;
}

Tree::Tree()
{
    root = nullptr;
    now = nullptr;
}

void Tree::insert(const QString& tag_name)
{
    if(root == nullptr)
    {
        root = new Node(tag_name,0);
        now = root;
    }
    else
    {
        QTextStream sout(stdout);

        now->child.push_back(new Node(tag_name,now->level));
        now->child.back()->p=now;
        now = now->child.back();
        now->level++;
    }
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
