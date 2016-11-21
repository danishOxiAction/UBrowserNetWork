#include "tree.h"

#include <QTextStream>

Tree::Tree() noexcept
{
    root = nullptr;
    now = nullptr;
}

Tree::~Tree() noexcept
{
    free_resoureces(root);

    root = nullptr;
    now = nullptr;
}

Tree::iterator Tree::begin() const noexcept
{
    return iterator(root);
}

Tree::iterator Tree::end() const noexcept
{
    return iterator(nullptr);
}

void Tree::push(Tag_type tag_type, const QString& tag_name, const QString& attributes) noexcept
{
    switch (tag_type)
    {
    case START_TAG:
        _push(now, tag_name, attributes);
        break;
    case INDEPENDENT_TAG:
        _push(now, tag_name, attributes);
        now = now->parent;
        break;
    case END_TAG:
        now = search(tag_name)->parent;
        break;
    case TEXT:
        _push(now, tag_name, attributes);
        break;
    default:
        break;
    }
}

void Tree::breadth_first_traversal(std::function<void (Node*)> func) const noexcept
{
    QQueue<Node*> queue;
    queue.push_back(root);

    while(!queue.isEmpty())
    {
        Node* temp = queue.takeFirst();

        for(auto it = temp->child.begin(); it < temp->child.end(); ++it)
        {
            queue.push_back(*it);
        }

        func(temp);
    }
}

void Tree::clear()
{
    free_resoureces(root);

    root = nullptr;
    now = nullptr;
}

void Tree::print() const
{
    QTextStream str(stdout);

    QString tree = "";
    _print_tree(tree, root, 0);

    str << tree;
}

//
//-------------------- Private Methods --------------------
//

Node* Tree::create_node(const QString& tag_name, const QString& attributes) const throw( Exceptions )
{
    try
    {
        Node* node  = new Node;
        node->tag_name = tag_name;
        node->attributes = set_attributes(attributes);

        return node;
    }
    catch(std::bad_alloc& ba)
    {
        throw Exceptions(ex::STD_EXCEPTION,ba);
    }
}

Node* Tree::set_prev(Node* node) noexcept
{
    Node* prev = nullptr;

    if(!node->parent->child.isEmpty())
    {
        Node* temp = node->parent->child.back();
        while(temp)
        {
            if(!temp->child.isEmpty())
            {
                temp = temp->child.back();
            }
            else break;
        }

        prev = temp;
    }
    else
        prev = node->parent;

    prev->next = node;
    node->prev = prev;
}

void Tree::free_resoureces(Node* node) noexcept
{
    if(node)
    {
        int i = 0;
        while(i = node->child.size())
        {
            free_resoureces( node->child.takeAt(i-1) );
        }

        node->tag_name = "";
        node->attributes = Attribute();
        node->parent = nullptr;

        delete node;

        node = nullptr;
    }
}

void Tree::_push(Node* parent, const QString& tag_name, const QString& attributes) noexcept
{
    Node* node = create_node(tag_name, attributes);
    node->parent = parent;

    if(parent != nullptr)
    {
        set_prev(node);
        node->next = nullptr;

        parent->child.push_back(node);
    }
    else
    {
        node->next = nullptr;
        node->prev = nullptr;

        root = node;
    }

    now = node;

    node = nullptr;
}

Node* Tree::search(const QString& tag_name) const throw( Exceptions )
{
    Node* temp = now;

    while(temp)
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

const Tree::Attribute Tree::set_attributes(const QString& attr) const
{
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
        else if(*it == '\'' && condition == NAME)
        {
            condition = VALUE;
            ++it;
        }
        else if(*it == '\'' && condition == VALUE)
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

    return attributes;
}

void Tree::_print_tree(QString& tree, Node* node, int level) const
{
    if(node == nullptr) return;

    for(int i = 0; i < level; i++)
    {
        tree += "_";
    }
    tree += node->tag_name + "\n";

    //    if(!node->attributes.isEmpty())
    //    {
    //        auto it = node->attributes.begin();
    //        auto end = node->attributes.end();

    //        while(it != end)
    //        {
    //            for(int i = 0; i <= level; i++)
    //            {
    //                tree += " ";
    //            }
    //            tree += it.key() + " = " + it.value() + "\n";

    //            ++it;
    //        }
    //    }

    for(int i = 0; i < node->child.size(); i++)
    {
        _print_tree(tree, node->child[i], level+1);
    }
}
