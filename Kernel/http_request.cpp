#include "http_request.h"
#include <QDateTime>
#include <QTextStream>

QList<QString> HttpRequest::last_host;
QMap <QString,QByteArray> HttpRequest::last_hosts_with_cookies;

// ++написать функцию которая проверяет наличее куки по хосту в листе
//++если он есть, возвращает как QByteArray
// ++если нет, то подгружает из файла, добавляет его в Мар и возращает как QBA
//++убрать ввод ввывод файла из метода запроса

//убрать лист, оставить только мап


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
            last_host.push_front(host);
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
    for(int i(0);i<last_host.size();i++)
    {
        if(host==last_host.at(i))
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
    
    last_host.push_front(host); // ошибка двойного попадания хоста в лист (даже если есть условие отсудствие хотста в списке)
    
    
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



QString HttpRequest::get(const QString &url)
{
    
    
    QNetworkRequest request;
    
    request.setUrl( QUrl(url) );
    if(check_host_to_visit(QUrl(url).host()))//  функция определения хоста
    {
        QByteArray cook=get_cookie_by_host(QUrl(url).host());
        request.setRawHeader("Cookie", cook);
    }
    
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkReply* reply = manager->get( request );
    QEventLoop wait;
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), &wait, SLOT(quit()));
    QTimer::singleShot(300000, &wait, SLOT(quit()));
    
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));
    wait.exec();
    
    if(!check_host_to_visit(QUrl(url).host()))
    {
        
        QNetworkCookieJar * cookie = manager->cookieJar();
        QList<QNetworkCookie>  cookies = cookie->cookiesForUrl( QUrl(url) );
        
        
        set_new_host_and_cookies(QUrl(url).host(),cookies);
        
        
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

