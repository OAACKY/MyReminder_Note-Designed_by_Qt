#include "setpasdialog.h"
#include "ui_setpasdialog.h"
#include<QMessageBox>
Setpasdialog::Setpasdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Setpasdialog)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground);
}

Setpasdialog::~Setpasdialog()
{
    delete ui;
}

void Setpasdialog::on_pushButton_clicked()
{
    temp1=ui->lineEdit->text();
    QMessageBox::information(NULL, QStringLiteral("设置信息"), QStringLiteral("密码设置成功！"), QMessageBox::Yes);
       this->hide();

}
