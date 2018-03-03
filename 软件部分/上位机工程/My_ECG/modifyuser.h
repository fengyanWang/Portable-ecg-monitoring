#ifndef MODIFYUSER_H
#define MODIFYUSER_H

#include <QDialog>



namespace Ui {
class ModifyUser;
}

class ModifyUser : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyUser(QWidget *parent = 0);
    ~ModifyUser();




private slots:
    void on_ModifyUserOkPushBt_clicked();

    void on_ModifyUserCanclePushBt_clicked();

private:
     Ui::ModifyUser *ui;

    void UserModify();
};

#endif // MODIFYUSER_H
