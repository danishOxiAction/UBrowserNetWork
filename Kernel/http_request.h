#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QByteArray>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>
#include <QTimer>
#include <QNetworkCookieJar>
#include <QList>
#include <QNetworkCookie>
#include <QMap>
#include <QFile>


class HttpRequest
{
public:

    QString get( const QString& url );
    HttpRequest();



protected:


    static QMap<QString,QByteArray> last_hosts_with_cookies;
    static void set_new_host_and_cookies(QString,QList<QNetworkCookie>&);
    //static QString get_host_by_url(QString url); //получение host по url
    static bool check_host_to_visit(QString host);
    QByteArray get_cookie_by_host(QString);
    QByteArray get_cookie_from_file(QString);
};

#endif // HTTPREQUEST_H
