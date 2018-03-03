#ifndef DELATEUSER_H
#define DELATEUSER_H

#include <QDialog>

namespace Ui {
class DelateUser;
}

class DelateUser : public QDialog
{
    Q_OBJECT

public:
    explicit DelateUser(QWidget *parent = 0);
    ~DelateUser();

private slots:
    void on_OkPushBt_DU_clicked();

    void on_CanclePushBt_DU_clicked();

private:
    Ui::DelateUser *ui;
    void delateUser();
};

#endif // DELATEUSER_H
