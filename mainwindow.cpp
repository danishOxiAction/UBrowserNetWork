#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMap>
#include <QDateTime>
#include <QTreeWidget>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setText("http://shotinleg.ru/test/index.php");  //  http://easy-qt.blogspot.ru/
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    HttpRequest request;
    QMap<QString,QString> data;

    QString html =  request.get(ui->lineEdit->text(),data);

    html.replace("\n", "");
    html.replace("\t", "");

    tokenizer.new_html_page(html);
    tokenizer.start_tokenization();

    QString tree = tokenizer.print_tree();

    ui->plainTextEdit->setPlainText(tree);
}

