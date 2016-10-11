#include "http_request.h"


QList<QNetworkCookie> HttpRequest::cookies;
QString HttpRequest::last_host;

QString HttpRequest::get(const QString &url)
{

    QNetworkRequest request;

    request.setUrl( QUrl(url) );
    if(true)
    {
        QByteArray ck;

        for(int i = 0; i < cookies.size(); i++)
            ck.append( cookies.at(i).name()+"="+cookies.at(i).value()+";" );

        request.setRawHeader("Cookie", ck);
    }

    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkReply* reply = manager->get( request );
    QEventLoop wait;
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), &wait, SLOT(quit()));
    QTimer::singleShot(300000, &wait, SLOT(quit()));

    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));
    wait.exec();



    QByteArray answer = reply->readAll();
    reply->deleteLater();

    QNetworkCookieJar * cookie = manager->cookieJar();
    cookies = cookie->cookiesForUrl( QUrl(url) );

    return answer;
}
