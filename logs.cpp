#include "logs.h"

#include <QDateTime>
#include <QTextStream>

Logs::Logs()
{
    log_file.setFileName("logs.log");
    log_file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);

    if(!log_file.isOpen())
    {
        // exception
    }
}

void Logs::add_note(const QString& message)
{
    QDateTime time = QDateTime::currentDateTime();

    QTextStream out(&log_file);

    out << time.toString("[dd.MM.yyyy - hh:mm:ss] ") + message;
}
