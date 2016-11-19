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

enum Excp_type {UNIDENTIFIED    = 0x000000,
                STD_EXCEPTION   = 0x000001,
                PROBLEM         = 0x100001};

class Exceptions : public std::exception
{
    QString _name;
    int _id;
public:
    Exceptions();
    Exceptions(Excp_type);
    Exceptions(Excp_type, std::exception);

    const QString&  name();
    const int&      id();
private:
    void    set_info(Excp_type);
};

#endif // EXCEPTIONS_H
