#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMap>
#include <QDateTime>
#include <QTreeWidget>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    request()
{
    ui->setupUi(this);
    ui->lineEdit->setText("http://shotinleg.ru/test/index.php");  //  http://easy-qt.blogspot.ru/

    logs.add_note("New session");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QMap<QString,QString> data;

    QString html =  request.get(ui->lineEdit->text(),data);   

    tokenizer.new_html_page(html);

    QString tree = tokenizer.print_tree();

    ui->plainTextEdit->setPlainText(tree);
}

//void MainWindow::on_ck_clicked()
//{
//    request.clear_the_cookies();
//}

