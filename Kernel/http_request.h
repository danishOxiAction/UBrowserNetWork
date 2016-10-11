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

class HttpRequest
{
public:

    static QString get( const QString& url );

protected:
    static QList<QNetworkCookie> cookies;
    static QString last_host;
};

#endif // HTTPREQUEST_H
