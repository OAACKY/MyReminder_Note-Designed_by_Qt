#include "about.h"
#include "ui_about.h"
#include<QDesktopServices>
About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    ui->label->setWhatsThis("This is Gongjiao");
    ui->label_2->setWhatsThis("This is XueHuo");

}

About::~About()
{
    delete ui;
}

void About::on_toolButton_clicked()
{
   QDesktopServices::openUrl(QUrl(QLatin1String("https://github.com/OAACKY")));
}
