#include "http_request.h"
#include <QDateTime>
#include <QTextStream>

QList<QString> HttpRequest::last_host;
QMap <QString,QString> HttpRequest::last_hosts_with_cookies;

// написать функцию которая проверяет наличее куки по хосту в мапе
//если он есть, возвращает как QByteArray
// если нет, то подгружает из файла, добавляет его в Мар и возращает как QBA

//убрать ввод ввывод файла из метода запроса

//босле обновления надо будет удалить файл с кукой ( работать будет по другому)
HttpRequest::HttpRequest()
{
    //    QFile cookiesfile("Cookies");
    //    if(cookiesfile.open(QFile::ReadOnly | QFile::Text))
    //    {
    //        if(!cookiesfile.atEnd())
    //        {
    //            QString host = cookiesfile.readLine();
    //            host = host.left(host.indexOf('|'));
    //            last_hosts_with_cookies[host]= "empty"; // тут же push host в last_host
    //        }
    //    }
    //    else
    //    {
    //        //throw;
    //    }
    //    cookiesfile.close();
}

void HttpRequest::set_new_host_and_cookies(QString& host, QList<QNetworkCookie>&  cookies)
{
    //    QString cookie;
    //    for(int i(0);i<cookies.size();i++)
    //    {
    //        cookie+=cookies.at(i).name()+'='+cookies.at(i).value()+';';
    //    }

    //    last_hosts_with_cookies[host]=cookie;  // тут же push host в last_host

    //    QFile cookiesfile("Cookies");
    //    if(cookiesfile.open(QFile::Append | QFile::Text))
    //    {
    //        QString host_and_cookie=host +'|'+cookie;
    //        QTextStream out(&cookiesfile);
    //        out << host_and_cookie << "\n";
    //    }
    //    else
    //    {
    //        //throw;
    //    }
    //    cookiesfile.close();




}



QString HttpRequest::get(const QString &url)
{
    QFile cookiesfile("Cookies");


    QNetworkRequest request;

    request.setUrl( QUrl(url) );
    if(check_host_to_visit(QUrl(url).host()))//  функция определения хоста /передавать ссылку на инт счетчик и он будет кидать номер хоста
    {
        // пишем функцию для получения по мапу см выше
        //пользуемся QMap, ключь QUrl(url).host() и выгружаем кук от туда
        cookiesfile.open(QFile::ReadOnly | QFile::Text);
        QByteArray cook  = cookiesfile.readLine();
        cook=cook.mid(0,cook.size()-2); // при чтении строки "всплывает" \n, тут удаляем для корректнгости запроса
        request.setRawHeader("Cookie", cook);
    }

    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkReply* reply = manager->get( request );
    QEventLoop wait;
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), &wait, SLOT(quit()));
    QTimer::singleShot(300000, &wait, SLOT(quit()));

    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));
    wait.exec();

    if(!check_host_to_visit(get_host_by_url(url)))
    {

        QNetworkCookieJar * cookie = manager->cookieJar();
        QList<QNetworkCookie>  cookies = cookie->cookiesForUrl( QUrl(url) );

        cookiesfile.open(QFile::WriteOnly | QFile::Text);
        QTextStream out(&cookiesfile);
        for( int i=0; i < cookies.size(); i++)
            out  << cookies.at(i).name() << "=" << cookies.at(i).value() << ";";
        out << "\n";


        cookiesfile.close();
        last_host.push_front(get_host_by_url(url));
    }

    QByteArray answer = reply->readAll();
    reply->deleteLater();

    return answer;
}



//QString HttpRequest::get_host_by_url(QString url)
//{
//    url=url.mid((url.indexOf('/')+2),url.size());
//    url= url.left(url.indexOf('/'));
//    return url;
//}

bool HttpRequest::check_host_to_visit(QString host)
{
    for(int i(0);i<last_host.size();i++)
    {
        if(host==last_host.at(i))
        {
            return true;
        }
    }

    return false;

}
