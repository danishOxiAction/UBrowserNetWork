#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Kernel/http_request.h"
#include "domparser.h"
#include "logs.h"

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QString>
#include <QList>
#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QTextCodec>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    //void on_ck_clicked();
private:
    Ui::MainWindow* ui;

    Logs            logs;
    DomParser       tokenizer;
    HttpRequest     request;
};

#endif // MAINWINDOW_H
