#include "tree.h"

Tree::Tree() noexcept
{
    root = nullptr;
    now = nullptr;
}

void Tree::push(Tag_type tag_type, const QString& tag_name, const QString& attributes) noexcept
{
    switch (tag_type)
    {
    case START_TAG || TEXT:
        _push(now, tag_name, attributes);
        break;
    case INDEPENDENT_TAG:
        _push(now, tag_name, attributes);

        now = now->parent;
    case END_TAG:
        now = search(tag_name)->parent;
    default:
        break;
    }
}

//
//-------------------- Private Methods --------------------
//

typename Tree::Node* Tree::create_node(const QString& tag_name, const QString& attributes) const throw( Exceptions )
{
    try
    {
        Node* node  = new Node;
        node->tag_name = tag_name;
        node->attributes = Attribute(); // set_attributes(attributes);

        return node;
    }
    catch(std::bad_alloc& ba)
    {
        throw Exceptions(ex::STD_EXCEPTION,ba);
    }
}

void Tree::_push(Tree::Node* parent, const QString& tag_name, const QString& attributes) throw( Exceptions )
{
    Node* node = create_node(tag_name, attributes);
    node->parent = parent;

    if(parent != nullptr)
    {
        parent->child.push_front(node);
    }
    else
    {
        root = node;
    }

    node = nullptr;
}

Tree::Node* Tree::search(const QString& tag_name) const throw( Exceptions )
{
    Node* temp = now;

    while(temp->parent)
    {
        if(temp->tag_name == tag_name)
        {
            return temp;
        }
        else
        {
            temp = temp->parent;
        }
    }

    throw Exceptions(ex::INVALID_HTML);
}

