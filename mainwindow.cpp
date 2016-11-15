#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMap>
#include <QDateTime>


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
    QString html;
    if(   !((ui->lineEdit_name1->text().isEmpty()) && (ui->lineEdit_value1->text().isEmpty()))  )
    {
        if( !((ui->lineEdit_name2->text().isEmpty()) && (ui->lineEdit_value2->text().isEmpty())))
        {

            QMap<QString,QString> data;
            data[ui->lineEdit_name1->text()]=ui->lineEdit_value1->text();
            data[ui->lineEdit_name2->text()]=ui->lineEdit_value2->text();
            html= request.post(ui->lineEdit->text(), data);
        }
        else
        {
            QMap<QString,QString> data;
            data[ui->lineEdit_name1->text()]=ui->lineEdit_value1->text();
          html =  request.get(ui->lineEdit->text(),data );
        }
    }
    else
    {
        QMap<QString,QString> data;
        html =  request.get(ui->lineEdit->text(),data);

    }
//    html=request.get_image(ui->lineEdit->text());

    //      qDebug() << ui->lineEdit_name1->text();
    //      QString html = HttpRequest::get(ui->lineEdit->text() );
    //      HttpRequest request;
    //      QString html =  request.get(ui->lineEdit->text() );



    //request.clear_the_history();
//    QMap<QDateTime,QString> history(request.get_history());
//    for(QMap<QDateTime,QString>::Iterator it = history.begin();it!=history.end();++it)
//    {
//        qDebug() << it.key() << " " << it.value() <<"\n";
//    }
     ui->plainTextEdit->setPlainText( html );

}

