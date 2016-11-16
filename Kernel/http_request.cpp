#include "http_request.h"
#include <QDateTime>
#include <QTextStream>
#include <QImage>
#include <QDir>


//QList<QString> HttpRequest::list_host;
QMap <QString,QByteArray> HttpRequest::list_hosts_with_cookies;

// ++написать функцию которая проверяет наличее куки по хосту в листе
//++если он есть, возвращает как QByteArray
// ++если нет, то подгружает из файла, добавляет его в Мар и возращает как QBA
//++убрать ввод ввывод файла из метода запроса

//++убрать лист, оставить только мап
//++ структурировать get, вынести часть запроса в функцию: принимает QNetworkRequest request
//++ и QNetworkAccessManager* manager, возвращает QNetworkReply* reply

//++ добавить data для get
// сохранение новых куки с вымищением старых

// SQLite -- если будет время | статья Qt и SQLite
// возвращать куку как QMap<QString,QVector<QString>> в векторе разбито на имя = значение
// история возвращает как QData,QString


HttpRequest::HttpRequest()
{
    QDir().mkdir("image");
    QFile cookiesfile("Cookies");
    if(cookiesfile.open(QFile::ReadOnly | QFile::Text))
    {
        if(!cookiesfile.atEnd())
        {
            QByteArray host = cookiesfile.readLine();
            host = host.left(host.indexOf('|'));
            list_hosts_with_cookies[host]= "empty";
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
    for( QMap<QString,QByteArray>::iterator it =list_hosts_with_cookies.begin();it!=list_hosts_with_cookies.end();++it)
    {
        if(it.key()==host)
        {
            return true;
        }
    }
    return false;
}


void HttpRequest::add_url_in_the_history(QString url)
{
    QDateTime dt = QDateTime::currentDateTime();
    QFile history("History");
    if(history.open(QFile::Append | QFile::Text))
    {
        QTextStream out(&history);
        QString item = dt.toString() + '|' + url + "\n";
        out << item;
    }
    else
    {
        //throw;
    }
    history.close();
}


void HttpRequest::clear_the_history()
{
    QFile("History").remove();
}

QMap<QDateTime, QString> HttpRequest::get_history()
{
    QMap<QDateTime, QString> list_history;
    QFile history("History");
    if(history.open(QFile::ReadOnly | QFile::Text))
    {

        while(!history.atEnd())
        {
            QByteArray tmp = history.readLine();

            list_history[QDateTime().fromString(tmp.left(tmp.indexOf('|')))]=tmp.mid((tmp.indexOf('|')+1),tmp.size());
        }


    }
    else
    {
        //throw;
    }
    history.close();
    return list_history;
}

void HttpRequest::clear_the_cookies()
{
    QFile("Cookies").remove();
}

//potom
//QMap<QString, QVector<QString> > HttpRequest::get_cookies()
//{
//    QMap<QString, QVector<QString> > list_cookies;
//    QFile cookies("Cookies");
//    if(cookiesfile.open(QFile::ReadOnly | QFile::Text))
//    {
//        while(!cookiesfile.atEnd())
//        {
//            QByteArray cookie = cookiesfile.readLine();
//            QByteArray _host = cookie.left(cookie.indexOf('|'));
//            cookie=cookie.mid(cookie.indexOf('|')+1,(cookie.size()-1));
//            QVector<QString> cook;
//            while (cookie.indexOf(';')!=(cookie.size()-1))
//            {
//                cook.push_back();
//            }




//        }
//        else
//        {
//            //throw;
//        }
//    }
//    else
//    {
//        //throw;
//    }
//    cookiesfile.close();
//}



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
    if(list_hosts_with_cookies[host]=="empty")
    {
        QByteArray cookie =get_cookie_from_file(host);
        list_hosts_with_cookies[host]=cookie;
        return list_hosts_with_cookies[host];
    }
    else
    {
        return list_hosts_with_cookies[host];
    }
}


QByteArray HttpRequest::swap_cookies_by_host(QByteArray txt_begin,QByteArray txt, const QString &host, const QByteArray cookie)
{
    QByteArray txt_now=txt.left(txt.indexOf('\n'));
    txt=txt.mid((txt.indexOf('\n')+1),txt.size());
    if(host==txt_now.left(txt_now.indexOf('|')))
    {
        txt_now=txt_now.left(txt_now.indexOf('|'))+"|"+cookie+'\n';
        return(txt_begin+txt_now+txt);
    }
    else
    {
        txt_begin+=(txt_now+'\n');
        return swap_cookies_by_host(txt_begin,txt,host,cookie);
    }


}

//декомпозировать! и сделать более наглядной!
void HttpRequest::check_the_relevance_cookies(QString host, QList<QNetworkCookie> & cookies)
{
    QByteArray tmp_cook = list_hosts_with_cookies[host];
    int size(0); //определяем количество пар name=value
    for(int i(0);i<tmp_cook.size();i++)
    {
        if(tmp_cook[i]==';')
        {
            size++;
        }
    }
    QList<QPair<QByteArray,QByteArray> > tmp_cook_list;

    //заполняем ими список
    for(int i(0);i<size;i++)
    {
        QByteArray tmp=tmp_cook.left(tmp_cook.indexOf(';'));
        QByteArray _name=tmp.left(tmp.indexOf('='));
        QByteArray _value=tmp.mid((tmp.indexOf('=')+1),tmp.size());

        tmp_cook_list.push_back(QPair<QByteArray,QByteArray> (_name,_value));

        tmp_cook=tmp_cook.mid((tmp_cook.indexOf(';')+1),tmp_cook.size());
    }



    //сверяем имеющиеся куки с теми что пришли после запроса

    bool fg_one(false);// флаг о наличии изменений в куке
    for(int i(0);i<cookies.size();i++)
    {
        bool flage(true); // флаг является ли кука с данным именем новой
        for(int j(0);j<size;j++)
        {
            if(tmp_cook_list.at(j).first==cookies.at(i).name())
            {
                fg_one=true;
                flage=false; // если нет проверяем новое ли значение
                if(tmp_cook_list.at(j).second!=cookies.at(i).value())
                {
                    //если да, заменяем новым
                    tmp_cook_list[j]=QPair<QByteArray,QByteArray>(cookies.at(i).name(),cookies.at(i).value());
                }
            }
        }

        if(flage) //а если кука новая, то мы ее добовляем
        {
            fg_one=true;
            tmp_cook_list.push_back(QPair<QByteArray,QByteArray>(cookies.at(i).name(),cookies.at(i).value()));
        }
    }

    if(fg_one)//если в куке есть изменения то мы обновляем мап и файл куки
    {

        tmp_cook = "";
        for(int i(0);i<tmp_cook_list.size();i++) // записываем в tmp_cook актуальную куку
        {
            tmp_cook +=tmp_cook_list.at(i).first+'='+tmp_cook_list.at(i).second+';';
        }
        list_hosts_with_cookies[host]=tmp_cook; // кладем ее в мап


        QByteArray txt;
        QFile cookiefile("Cookies");
        if(cookiefile.open(QFile::ReadOnly))
        {

            txt =cookiefile.readAll(); //считали куку
            //qDebug() << txt;
            txt=swap_cookies_by_host("",txt,host,list_hosts_with_cookies[host]); //внесли изменения


        }
        else
        {
            //throw;
        }
        cookiefile.close();
        if(cookiefile.open(QFile::WriteOnly))
        {

            cookiefile.write(txt); //записали изменения

        }
        else
        {
            //throw;
        }
        cookiefile.close();

    }

    //иначе выходим
}


void HttpRequest::set_new_host_and_cookies(QString host, QList<QNetworkCookie>&  cookies)
{
    QByteArray cookie;
    for(int i(0);i<cookies.size();i++)
    {
        cookie+=cookies.at(i).name()+'='+cookies.at(i).value()+';';
    }
    
    list_hosts_with_cookies[host]=cookie;
    
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




QString HttpRequest::get(const QString &url, QMap <QString,QString> data)
{
    QString url_prm(url);
    for(QMap<QString,QString>::iterator it=data.begin();it!=data.end();++it)
    {
        if(!url_prm.contains("?"))
        {
            url_prm += "?";
        }
        else
        {
            url_prm += "&";
        }
        url_prm +=it.key() + "=" + it.value();
    }
    
    QNetworkRequest request;
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkReply* reply;

    request.setUrl( QUrl(url_prm) );
    if(check_host_to_visit(QUrl(url).host()))// проверяем посещали ли мы этот хост
    {
        QByteArray cook=get_cookie_by_host(QUrl(url).host()); // если да, выгружагем куку
        request.setRawHeader("Cookie", cook);
        reply = get_reply_by_request(request,manager);// соверщаем запрос с передачей куки

        QNetworkCookieJar * cookie = manager->cookieJar();
        QList<QNetworkCookie>  cookies = cookie->cookiesForUrl(QUrl(url_prm) );
        check_the_relevance_cookies(QUrl(url).host(),cookies);
    }
    else                                    // если нет
    {
        reply = get_reply_by_request(request,manager); // совершаем запрос

        QNetworkCookieJar * cookie = manager->cookieJar();
        QList<QNetworkCookie>  cookies = cookie->cookiesForUrl(QUrl(url_prm) );


        set_new_host_and_cookies(QUrl(url).host(),cookies); // выгружаем куку и сохраняем ее


    }
    
    QByteArray answer = reply->readAll();
    reply->deleteLater();
    
    add_url_in_the_history(url_prm);
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

    for(QMap <QString, QString>::iterator it = data.begin();it !=data.end(); ++it) //QMap <QString, QString>::iterator it ~ auto it
    {

        //post_data.append(it.key()+"="+it.value())
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
    QNetworkCookieJar * cookie = manager->cookieJar();
    QList<QNetworkCookie>  cookies = cookie->cookiesForUrl( QUrl(url) );
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), &wait, SLOT(quit()));
    QTimer::singleShot(300000, &wait, SLOT(quit()));

    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));
    wait.exec();
    QByteArray answer = reply->readAll();
    reply->deleteLater();



    if(!check_host_to_visit(QUrl(url).host()))
    {
        QNetworkCookieJar * cookie = manager->cookieJar();
        QList<QNetworkCookie>  cookies = cookie->cookiesForUrl( QUrl(url) );
        set_new_host_and_cookies(QUrl(url).host(),cookies);
    }
    else
    {
        QNetworkCookieJar * cookie = manager->cookieJar();
        QList<QNetworkCookie>  cookies = cookie->cookiesForUrl( QUrl(url) );
        check_the_relevance_cookies(QUrl(url).host(),cookies);
    }

    add_url_in_the_history(url);
    return answer;

    
}


QString HttpRequest::get_image_name_by_url(const QString &url)
{
    QString name(url);

    int index(0);
    for(int i(0);i<name.size();i++)
    {
        if(name[i]=='/')
        {
            index=i;
        }
    }

    return name.mid(index+1,name.size());
}

QString HttpRequest::get_image(const QString &url)
{
    QNetworkRequest request;
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkReply* reply;
    request.setUrl(QUrl(url));
    
    reply = get_reply_by_request(request,manager);
    QByteArray answer = reply->readAll();
    reply->deleteLater();

    QImage image;
    image.loadFromData(answer);
    if(image.save("image/"+get_image_name_by_url(url)))//пытаемся сохранить картинку
    {

        return "image/"+get_image_name_by_url(url);
    }
    else //если нельзя
    {
        QDir().mkdir("image"); //пытаемся решить проблему создав каталог
        if(image.save("image/"+get_image_name_by_url(url)))// и пробуем снова
        {

            return "image/"+get_image_name_by_url(url);
        }
        else
        {
            return "error"; //throw;
        }
    }

    

    
    
}





//QString HttpRequest::get_host_by_url(QString url)
//{
//    url=url.mid((url.indexOf('/')+2),url.size());
//    url= url.left(url.indexOf('/'));
//    return url;
//}

