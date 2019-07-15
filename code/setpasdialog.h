#ifndef SETPASDIALOG_H
#define SETPASDIALOG_H

#include <QDialog>

namespace Ui {
class Setpasdialog;
}

class Setpasdialog : public QDialog
{
    Q_OBJECT

public:
    explicit Setpasdialog(QWidget *parent = nullptr);
    ~Setpasdialog();
    QString temp1;

private slots:
    void on_pushButton_clicked();

private:
    Ui::Setpasdialog *ui;
};

#endif // SETPASDIALOG_H
