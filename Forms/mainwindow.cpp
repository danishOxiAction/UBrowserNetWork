#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tab.h"

#include <QMap>
#include <QDateTime>
#include <QFile>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget* fst_tab = new QWidget;
    ui->tabs->addTab(fst_tab,"First Tab");
    Tab* tab = new Tab(fst_tab);

    logs.add_note("New session");
}

MainWindow::~MainWindow()
{
    logs.add_note("Successful completion of the session");
    delete ui;
}
