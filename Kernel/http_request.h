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
    HttpRequest();
    QString                             get( const QString& url,QMap <QString,QString> data );
    QString                             post(const QString& url,QMap <QString,QString> data);
    QString                             get_image(const QString& url);
    void                                clear_the_history();
    QMap<QDateTime, QString>            get_history();
    void                                clear_the_cookies();
    QMap<QString, QVector<QString > >   get_cookies();
    void                                remove_part_of_the_story(QList<QString>);
    void                                remove_part_of_the_cook(QList<QString>);

protected:
    static QMap<QString,QByteArray>     list_hosts_with_cookies;
    static void                         set_new_host_and_cookies(QString,QList<QNetworkCookie>&);
    //static QString get_host_by_url(QString url); //получение host по url
    static bool                         check_host_to_visit(QString);
    QString                             get_image_name_by_url(const QString &url);
    QByteArray                          get_cookie_by_host(QString);
    QByteArray                          get_cookie_from_file(QString);
    QNetworkReply*                      get_reply_by_request(QNetworkRequest&,QNetworkAccessManager*);
    QNetworkReply*                      post_reply_by_request(QNetworkRequest&, QNetworkAccessManager*, QByteArray);
    void                                add_url_in_the_history(QString url);
    void                                check_the_relevance_cookies(QString,QList<QNetworkCookie>&);
    QByteArray                          swap_cookies_by_host(QByteArray txt_begin, QByteArray txt, const QString &host, const QByteArray cookie);
    int                                 get_qty_pair_name_value(QByteArray);
    QByteArray                          remove_part_by_key(QList<QString>,QByteArray,QByteArray);// в доработке + декомпозиции

};

#endif // HTTPREQUEST_H
