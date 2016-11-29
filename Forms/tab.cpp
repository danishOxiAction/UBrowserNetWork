#include "tab.h"
#include "ui_tab.h"

Tab::Tab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab)
{
    ui->setupUi(this);

    ui->AddresBar->setText("http://shotinleg.ru/test/index.php");  //  http://easy-qt.blogspot.ru/
}

Tab::~Tab()
{
    delete ui;
}

void Tab::on_Go_clicked()
{
    QMap<QString,QString> data;

//    QFile file("image.html");
//    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QString html = request.get(ui->AddresBar->text(),data);

    parser.new_html_page(html);
    parser.parse();


    //logs.add_note("test log");
    QString tree = parser.print_tree();

    ui->textBrowser->setText(tree);
}
