#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlQuery>
#include<QDebug>
#include<QtSql/QSqlError>
namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_pushButton_clicked();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
