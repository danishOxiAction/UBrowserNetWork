#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <QString>
#include <exception>

/* 0x10000n - network module exceptions
 * 0x20000n - parser exceptions
 * 0x30000n - render exceptions
 *
 * 0x00000n - other exceptions
 */

namespace ex
{
enum Excp_type {UNIDENTIFIED    = 0x000000,
                STD_EXCEPTION   = 0x000001,

                INVALID_HTML    = 0x200001};
}

class Exceptions : public std::exception
{
    QString _name;
    int _id;
public:
    Exceptions();
    Exceptions(ex::Excp_type);
    Exceptions(ex::Excp_type, std::exception);

    const QString&  name();
    const int&      id();
private:
    void    set_info(ex::Excp_type);
};

#endif // EXCEPTIONS_H
