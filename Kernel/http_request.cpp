#include "http_request.h"
#include <QDateTime>
#include <QTextStream>

//QList<QString> HttpRequest::last_host;
QMap <QString,QByteArray> HttpRequest::last_hosts_with_cookies;

// ++написать функцию которая проверяет наличее куки по хосту в листе
//++если он есть, возвращает как QByteArray
// ++если нет, то подгружает из файла, добавляет его в Мар и возращает как QBA
//++убрать ввод ввывод файла из метода запроса

//++убрать лист, оставить только мап
//++ структурировать get, вынести часть запроса в функцию: принимает QNetworkRequest request
//++ и QNetworkAccessManager* manager, возвращает QNetworkReply* reply

HttpRequest::HttpRequest()
{
    QFile cookiesfile("Cookies");
    if(cookiesfile.open(QFile::ReadOnly | QFile::Text))
    {
        if(!cookiesfile.atEnd())
        {
            QByteArray host = cookiesfile.readLine();
            host = host.left(host.indexOf('|'));
            last_hosts_with_cookies[host]= "empty";
        }
    }
    else
    {
        //throw;
    }
    cookiesfile.close();
}

bool HttpRequest::check_host_to_visit(QString host)
{
    for( QMap<QString,QByteArray>::iterator it =last_hosts_with_cookies.begin();it!=last_hosts_with_cookies.end();++it)
    {
        if(it.key()==host)
        {
            return true;
        }
    }
    return false;
}


QByteArray HttpRequest::get_cookie_from_file(QString host)
{
    QFile cookiesfile("Cookies");
    if(cookiesfile.open(QFile::ReadOnly | QFile::Text))
    {
        if(!cookiesfile.atEnd())
        {
            QByteArray cookie = cookiesfile.readLine();
            QByteArray _host = cookie.left(cookie.indexOf('|'));
            if(host==_host)
            {
                cookie=cookie.mid(cookie.indexOf('|')+1,(cookie.size()));
                cookie=cookie.mid(0,cookie.size()-1);
                return cookie;
            }
            
        }
        else
        {
            //throw;
        }
    }
    else
    {
        //throw;
    }
    cookiesfile.close();
}


QByteArray HttpRequest::get_cookie_by_host(QString host)
{
    if(last_hosts_with_cookies[host]=="empty")
    {
        QByteArray cookie =get_cookie_from_file(host);
        last_hosts_with_cookies[host]=cookie;
        return last_hosts_with_cookies[host];
    }
    else
    {
        return last_hosts_with_cookies[host];
    }
}



void HttpRequest::set_new_host_and_cookies(QString host, QList<QNetworkCookie>&  cookies)
{
    QByteArray cookie;
    for(int i(0);i<cookies.size();i++)
    {
        cookie+=cookies.at(i).name()+'='+cookies.at(i).value()+';';
    }
    
    last_hosts_with_cookies[host]=cookie;
    
    QFile cookiesfile("Cookies");
    if(cookiesfile.open(QFile::Append | QFile::Text))
    {
        QString host_and_cookie=host +'|'+cookie;
        QTextStream out(&cookiesfile);
        out << host_and_cookie << "\n";
    }
    else
    {
        //throw;
    }
    cookiesfile.close();
    
}

QNetworkReply *HttpRequest::get_reply_by_request(QNetworkRequest& request, QNetworkAccessManager*manager)
{
    QNetworkReply* reply = manager->get( request );
    QEventLoop wait;
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), &wait, SLOT(quit()));
    QTimer::singleShot(300000, &wait, SLOT(quit()));

    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));
    wait.exec();
    return reply;
}


QString HttpRequest::get(const QString &url)
{
    
    
    QNetworkRequest request;
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkReply* reply;

    request.setUrl( QUrl(url) );
    if(check_host_to_visit(QUrl(url).host()))// проверяем посещали ли мы этот хост
    {
        QByteArray cook=get_cookie_by_host(QUrl(url).host()); // если да, выгружагем куку
        request.setRawHeader("Cookie", cook);
        reply = get_reply_by_request(request,manager); // соверщаем запрос с передачей куки
    }
    else                                    // если нет
    {
        reply = get_reply_by_request(request,manager); // совершаем запрос

        QNetworkCookieJar * cookie = manager->cookieJar();
        QList<QNetworkCookie>  cookies = cookie->cookiesForUrl( QUrl(url) );


        set_new_host_and_cookies(QUrl(url).host(),cookies); // выгружаем куку и сохраняем ее


    }
    
    QByteArray answer = reply->readAll();
    reply->deleteLater();
    
    return answer;

}

QString HttpRequest::post(const QString &url, QMap<QString, QString> data)
{
    QNetworkRequest request;
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkReply* reply;
    QString boundary = "1BEF0A57BE110FD467A";
    QByteArray post_data;

    post_data.append("\r\n");

    for(QMap <QString, QString>::iterator it = data.begin();it !=data.end(); ++it)
    {

        post_data.append("--" + boundary + "\r\n");
        post_data.append("Content-Disposition: form-data; name=\""+it.key()+"\"\r\n");
        post_data.append("\r\n");
        post_data.append(it.value()+ "\r\n");
    }
    post_data.append("--" + boundary + "--" + "\r\n");

    QByteArray host;
    host.append(QUrl(url).host());

    QByteArray type;
    type.append( "multipart/form-data; boundary="+boundary+"" );

    QByteArray length;
    length.append( QString::number( post_data.length() ) );

    request.setUrl( QUrl(url) );
    request.setRawHeader("Host", host );
    request.setRawHeader("Referer", host );
    if(check_host_to_visit(QUrl(url).host()))
    {
        QByteArray cook=get_cookie_by_host(QUrl(url).host());
        request.setRawHeader("Cookie", cook);
    }
    else
    {
        request.setRawHeader("Cookie", "income=1");
    }
    request.setRawHeader("Content-Type", type );
    request.setRawHeader("Content-Length", length );


    reply = manager->post(request,post_data);
    QEventLoop wait;
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), &wait, SLOT(quit()));
    QTimer::singleShot(300000, &wait, SLOT(quit()));

    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));
    wait.exec();
    QByteArray answer = reply->readAll();
    reply->deleteLater();


}



//QString HttpRequest::get_host_by_url(QString url)
//{
//    url=url.mid((url.indexOf('/')+2),url.size());
//    url= url.left(url.indexOf('/'));
//    return url;
//}

