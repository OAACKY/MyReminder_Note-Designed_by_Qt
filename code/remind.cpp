#include "remind.h"
#include "ui_remind.h"


Remind::Remind(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Remind)
{
    ui->setupUi(this);
}

Remind::~Remind()
{
    delete ui;
}

void Remind::on_pushButton_clicked()
{
      myhour=ui->lineEdit->text();
      myminu=ui->lineEdit_2->text();
      QMessageBox::information(NULL, QStringLiteral("������Ϣ"), QStringLiteral("�������óɹ���"), QMessageBox::Yes);
      this->hide();
}
