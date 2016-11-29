#ifndef TAB_H
#define TAB_H

#include "Kernel/http_request.h"
#include "parser.h"

#include <QWidget>
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
class Tab;
}

class Tab : public QWidget
{
    Q_OBJECT

public:
    explicit Tab(QWidget *parent = 0);
    ~Tab();

private slots:
    void on_Go_clicked();

private:
    Ui::Tab *ui;

    Parser          parser;
    HttpRequest     request;
};

#endif // TAB_H
