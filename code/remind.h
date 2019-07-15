#ifndef REMIND_H
#define REMIND_H

#include <QDialog>
#include<QMessageBox>
namespace Ui {
class Remind;
}

class Remind : public QDialog
{
    Q_OBJECT

public:
    explicit Remind(QWidget *parent = nullptr);
    ~Remind();
    QString myhour;
    QString myminu;

private slots:
    void on_pushButton_clicked();

private:
    Ui::Remind *ui;
};

#endif // REMIND_H
