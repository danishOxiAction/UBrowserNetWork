#include "parser.h"
#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QFile>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MainWindow window;

    window.show();

    return app.exec();
}
