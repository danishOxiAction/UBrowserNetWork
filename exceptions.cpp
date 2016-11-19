#include "exceptions.h"

Exceptions::Exceptions()
{
    _name   = "Unidentidied exception.";
    _id     = UNIDENTIFIED;
}

Exceptions::Exceptions(Excp_type type)
{
    set_info(type);
}

Exceptions::Exceptions(Excp_type type, std::exception ex)
    :std::exception(ex)
{
    if(type == STD_EXCEPTION)
    {
        _name   = ex.what();
        _id     = STD_EXCEPTION;
    }
    else
    {
        _name   = "Unidentidied exception.";
        _id     = UNIDENTIFIED;
    }
}

const QString& Exceptions::name()
{
    return _name;
}

const int& Exceptions::id()
{
    return _id;
}

void Exceptions::set_info(Excp_type type)
{
    switch (type)
    {
    case PROBLEM:
        _name   = "Some problem.";
        _id     = PROBLEM;
        break;
    default:
        _name   = "Unidentidied exception.";
        _id     = UNIDENTIFIED;
        break;
    }
}
