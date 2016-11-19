#include "exceptions.h"

Exceptions::Exceptions()
{
    _name   = "Unidentidied exception.";
    _id     = ex::UNIDENTIFIED;
}

Exceptions::Exceptions(ex::Excp_type type)
{
    set_info(type);
}

Exceptions::Exceptions(ex::Excp_type type, std::exception ex)
    :std::exception(ex)
{
    if(type == ex::STD_EXCEPTION)
    {
        _name   = ex.what();
        _id     = ex::STD_EXCEPTION;
    }
    else
    {
        _name   = "Unidentidied exception.";
        _id     = ex::UNIDENTIFIED;
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

void Exceptions::set_info(ex::Excp_type type)
{
    switch (type)
    {
    //--- Network Module Exceptions ---

    //--- Parser Exceptions ---
    case ex::INVALID_HTML:
        _name   = "Invalid HTML page.";
        _id     = ex::INVALID_HTML;
        break;

    //--- Render Exceptions ---

    //--- Other Exceptions ---
    default:
        _name   = "Unidentidied exception.";
        _id     = ex::UNIDENTIFIED;
        break;
    }
}
