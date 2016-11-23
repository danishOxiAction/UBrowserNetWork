#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMap>
#include <QDateTime>
#include <QFile>


MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent),
     ui(new Ui::MainWindow),
     request()
{
    ui->setupUi(this);
    ui->lineEdit->setText("http://shotinleg.ru/test/index.php");  //  http://easy-qt.blogspot.ru/

    logs.add_note("New session");
}

MainWindow::~MainWindow()
{
    logs.add_note("Successful completion of the session");
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QMap<QString,QString> data;

//    QFile file("some.html");
//    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QString html = request.get(ui->lineEdit->text(),data);

    parser.new_html_page(html);
    parser.parse();


    logs.add_note("test log");
    QString tree = parser.print_tree();

    ui->plainTextEdit->setPlainText(tree);
}

//void MainWindow::on_ck_clicked()
//{
//    QList<QString> list_remove;
//    list_remove.push_back("test.ru");
//    list_remove.push_back("shotinleg.ru");

//  request.remove_part_of_the_cook(list_remove);
//}

