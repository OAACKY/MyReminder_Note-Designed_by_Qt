#include "login.h"
#include "ui_login.h"
#include "mybasewindow.h"
#include<QMessageBox>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    setWhatsThis("The password is NKU");
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{  QSqlQuery sql_query;
   QString select_sql = "select id,passport from user";
   QString mystring=ui->lineEdit->text();
   QString temp;
   sql_query.exec(select_sql);
   sql_query.first();
   temp=sql_query.value(1).toString();
   if(temp==mystring)
   {   QMessageBox::information(NULL, QStringLiteral("��¼��Ϣ"), QStringLiteral("��¼�ɹ���"), QMessageBox::Yes);
   this->hide();
    Mybasewindow *w=new Mybasewindow;
   w->show();
   }
   else {
       QMessageBox::warning(NULL, QStringLiteral("��¼��Ϣ"), QStringLiteral("��¼ʧ��"), QMessageBox::Yes, QMessageBox::Yes);
   }
}
