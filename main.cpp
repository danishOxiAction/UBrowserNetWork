#include "parser.h"

#include <QDebug>
#include <QFile>

int main()
{
    QFile file("some.html");

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString str = file.readAll();

        Parser p(str);
        p.parse();
        p.print_tree();
    }
    else
    {
        qDebug() << "File not open!";
    }
//    t.push(START_TAG, "html", "xmlns='http://www.w3.org/1999/xhtml' xml:lang='ru' lang='ru'");
//        t.push(START_TAG, "head", "");
//            t.push(START_TAG, "title", "");
//                t.push(TEXT, "I'm awesome!", "");
//            t.push(END_TAG, "title", "");
//            t.push(INDEPENDENT_TAG, "meta", "name='description' content='Im realy awesome!'");
//            t.push(START_TAG, "script", "src='what.html'");
//                t.push(TEXT, "*JS code*", "");
//            t.push(END_TAG, "script", "");
//        t.push(END_TAG, "head", "");
//        t.push(START_TAG, "body", "");
//            t.push(START_TAG, "div", "class='fst'");
//            t.push(END_TAG, "div", "");
//            t.push(START_TAG, "div", "class='snd'");
//                t.push(START_TAG, "div", "class='3-d'");
//                t.push(END_TAG, "div", "");
//                t.push(START_TAG, "div", "class='4-th'");
//                    t.push(START_TAG, "span", "style='color: #fff;'");
//                        t.push(TEXT, "WTF?", "");
//                    t.push(END_TAG, "span", "");
//                    t.push(INDEPENDENT_TAG, "br", "");
//                t.push(END_TAG, "div", "");
//                t.push(START_TAG, "div", "class='5-th");
//                t.push(END_TAG, "div", "");
//            t.push(END_TAG, "div", "");
//        t.push(END_TAG, "body", "");
//    t.push(END_TAG, "html", "");

    qDebug() << "\n\nNo problems, bro!\nYou awesome :3";
}
