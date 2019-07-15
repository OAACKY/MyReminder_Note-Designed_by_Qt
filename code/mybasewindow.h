#ifndef MYBASEWINDOW_H
#define MYBASEWINDOW_H

#include <QMainWindow>
#include<QTextEdit>
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlQuery>
#include<QDebug>
#include<QtSql/QSqlError>
#include<QTimer>
namespace Ui {
class Mybasewindow;
}

class Mybasewindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit Mybasewindow(QWidget *parent = nullptr);
    ~Mybasewindow();

private slots:
    void on_action12_2_triggered();

    void on_actiont_triggered();

    void on_actionsh_triggered();

    void on_toolButton_4_clicked();

    void on_toolButton_3_clicked();

    void on_toolButton_2_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_tabWidget_tabBarDoubleClicked(int index);

    void clickcolor(int);
    void on_actiont_2_triggered();

    void on_actionb_triggered();

    void on_action12_triggered();

    void on_actiont_3_triggered();

    void time_update();
private:
    Ui::Mybasewindow *ui;
    int tabnum;
    int curtab;
    QTextEdit *mytextt[15];
    QWidget *mywidget[15];
    QTimer *remindti;
};

#endif // MYBASEWINDOW_H
