#include "attributes.h"

Attributes::Attributes() {}

Attributes::Attributes(const Attributes &other)
    :attributes(other.attributes) {}

bool Attributes::isEmpty()
{
    return attributes.isEmpty();
}

void Attributes::push(const QString &name, const QString &value)
{
    attributes.push_back(Attribute(name, value));
}

void Attributes::push(const Attributes::Attribute& attribute)
{
    attributes.push_back(attribute);
}

Attributes::iterator Attributes::begin()
{
    return attributes.begin();
}

Attributes::iterator Attributes::end()
{
    return attributes.end();
}
