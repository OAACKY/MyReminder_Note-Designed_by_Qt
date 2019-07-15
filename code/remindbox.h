#ifndef REMINDBOX_H
#define REMINDBOX_H

#include <QDialog>

namespace Ui {
class Remindbox;
}

class Remindbox : public QDialog
{
    Q_OBJECT

public:
    explicit Remindbox(QWidget *parent = nullptr);
    ~Remindbox();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Remindbox *ui;
};

#endif // REMINDBOX_H
