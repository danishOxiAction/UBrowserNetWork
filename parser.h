#pragma once

#include "tree.h"

#include <QRegExp>

class Parser
{
    QString html;

    Tree tree;
public:
    Parser();
    Parser(const QString& raw_html);

    void            new_html_page(const QString&);
    void            parse();
    const QString   print_tree();
};
