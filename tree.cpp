#include "tree.h"
#include <QTextStream>
void Tree::search_node(Node* node, const QString& name)
{
    if(node->tag_name == name)
    {
        now = node->parent;
    }
    else
    {
        search_node(node->parent,name);
    }
}

Tree::Attribute Tree::parse_attributes(const QString& attr)
{
    QTextStream s(stdout);
    s << attr << "\n";

    enum Condition {NONE    = 0,
                    NAME    = 1,
                    VALUE   = 2};
    Condition condition = NONE;

    auto it = attr.begin();

    Attribute attributes;

    QString name;
    QString value;

    while(it != attr.end())
    {
        if(it->isLetter() && condition == NONE)
        {
            condition = NAME;
        }
        else if(*it == '"' && condition == NAME)
        {
            condition = VALUE;
            ++it;
        }
        else if(*it == '"' && condition == VALUE)
            condition = NONE;



        if( (*it == ' ' || (it+1) == attr.end() ) && condition == NONE)
        {
            attributes.insert(name,value);
            name = "";
            value = "";
        }

        if(condition == NAME) name += *it;
        if(condition == VALUE) value += *it;

        it++;

        if(*it == '=') ++it;
    }

    attributes.erase(attributes.find("")); // WTF?

    return attributes;
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
    switch (type)
    {
    case START_TAG:
    {
        QPair<QString,QString> _tag = cut_on_name_and_attributes(tag);

        if(root == nullptr)
        {
            root = new Node;

            root->parent = nullptr;
            root->tag_name = _tag.first;
            if(_tag.second != "")
                root->attributes = parse_attributes(_tag.second);

            now = root;
        }
        else
        {
            now->child.push_front(new Node);

            Node* temp = now->child.front();

            temp->parent = now;
            temp->tag_name = _tag.first;
            if(_tag.second != "")
                temp->attributes = parse_attributes(_tag.second);

            now = temp;

            temp = nullptr;
        }
        break;
    }
    case END_TAG:
    {
        QPair<QString,QString> _tag = cut_on_name_and_attributes(tag);
        search_node(now, _tag.first);
        break;
    }
    case TEXT:
    {
        now->child.push_front(new Node);

        Node* temp = now->child.front();

        temp->parent = now;
        temp->tag_name = tag;

        now = temp;

        temp = nullptr;
    }
    default:
        break;
    }
}
