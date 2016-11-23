#pragma once

#include "tree.h"

#include <QRegExp>

class Parser
{
    QString html;

    Tree tree;
public:
    Parser(QString raw_html);

    void    parse();
    void    print_tree();
};
