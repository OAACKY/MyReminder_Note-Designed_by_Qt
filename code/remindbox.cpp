#include "remindbox.h"
#include "ui_remindbox.h"

Remindbox::Remindbox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Remindbox)
{
    ui->setupUi(this);
}

Remindbox::~Remindbox()
{
    delete ui;
}

void Remindbox::on_pushButton_clicked()
{
    this->close();
}
