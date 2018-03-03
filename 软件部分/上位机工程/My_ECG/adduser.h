#ifndef ADDUSER_H
#define ADDUSER_H

#include <QWidget>

namespace Ui {
class AddUser;
}

class AddUser : public QWidget
{
    Q_OBJECT

public:
    explicit AddUser(QWidget *parent = 0);
    ~AddUser();

private slots:
    void on_UserIDLineEdit_textChanged(const QString &arg1);

    void on_OkPushBt_clicked();

    void on_CanclePushButton_2_clicked();

    void on_ReturnPushBt_clicked();

private:
    Ui::AddUser *ui;
    void UserAdd();
};

#endif // ADDUSER_H
