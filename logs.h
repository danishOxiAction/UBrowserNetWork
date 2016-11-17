#ifndef LOGS_H
#define LOGS_H

#include <QFile>
#include <QByteArray>

class Logs
{
   QFile log_file;
public:
    Logs();

    void    add_note(const QString&);
};

#endif // LOGS_H
