#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <QString>
#include <QList>
#include <QPair>

class Attributes
{
    typedef QPair<QString, QString> Attribute;
    typedef QList<Attribute>::iterator iterator;

    QList<Attribute> attributes;

public:
    Attributes();
    Attributes(const Attributes& other);

    bool    isEmpty();

    void    push(const QString& name, const QString& value);
    void    push(const Attribute& attribute);

    iterator begin();
    iterator end();

};

#endif // ATTRIBUTE_H
