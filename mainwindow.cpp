#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setText("http://easy-qt.blogspot.ru/");
    // Создаем объект менеджера
    manager = new QNetworkAccessManager(this);
}

void MainWindow::on_pushButton_clicked()
{
   // берем адрес введенный в текстовое поле
   QUrl url(ui->lineEdit->text());

   // создаем объект для запроса
   QNetworkRequest request(url);

   // Выполняем запрос, получаем указатель на объект
   // ответственный за ответ
   QNetworkReply* reply=  manager->get(request);

   // Подписываемся на сигнал о готовности загрузки
   connect( reply, SIGNAL(finished()),
            this, SLOT(replyFinished()) );
}

void MainWindow::replyFinished()
{
  QNetworkReply *reply=
    qobject_cast<QNetworkReply *>(sender());

  if (reply->error() == QNetworkReply::NoError)
  {
    // Получаем содержимое ответа
    QByteArray content= reply->readAll();

    // Реализуем преобразование кодировки
    // (зависит от кодировки сайта)
    QTextCodec *codec = QTextCodec::codecForName("utf8");

    // Выводим результат
    ui->textEdit->setPlainText(codec->toUnicode(content.data()) );
  }
  else
  {
    // Выводим описание ошибки, если она возникает.
    ui->textEdit->setPlainText(reply->errorString());
  }

  // разрешаем объекту-ответа "удалится"
  reply->deleteLater();
}
MainWindow::~MainWindow()
{
    delete ui;
}
