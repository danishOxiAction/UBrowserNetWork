#include "logs.h"

#include <QDateTime>
#include <QTextStream>
#include <QDebug>


Logs::Logs()
{
    log_file.setFileName("logs.log");
    log_file.open(QIODevice::Append | QIODevice::Text);
    {
        if(log_file.size()!=0)
        {
            log_file.write("\n"); // если файл не пуст, то перенести строку
        }
    }


    if(!log_file.isOpen())
    {
        // exception
    }
}

void Logs::add_note(const QString& message)
{
    QDateTime time = QDateTime::currentDateTime();

    QTextStream out(&log_file);

    out << time.toString("[dd.MM.yyyy - hh:mm:ss] ") + message+"\n";
}

void Logs::remove_log()
{
    log_file.remove();
}
