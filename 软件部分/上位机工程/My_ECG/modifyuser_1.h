#ifndef MODIFYUSER_1_H
#define MODIFYUSER_1_H

#include <QDialog>


namespace Ui {
class ModifyUser_1;
}

class ModifyUser_1 : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyUser_1(QWidget *parent = 0);
    ~ModifyUser_1();
    void ShowUserInfo();

private slots:
    void on_SurePushBt_clicked();

    void on_IDLineEdit_textChanged(const QString &arg1);

    void on_NameLineEdit_textChanged(const QString &arg1);

    void on_AgeLineEdit_textChanged(const QString &arg1);

    void on_SexLineEdit_textChanged(const QString &arg1);

    void on_DeviceNumberLineEdit_textChanged(const QString &arg1);

    void on_PhoneNumberLineEdit_textChanged(const QString &arg1);

    void on_OffPushBt_clicked();

private:
    Ui::ModifyUser_1 *ui;
    void ModifyUser_2();
    QString InforExtraction(QString str);

    bool IdChangeFlag;
    bool NameChangeFlag;
    bool AgeChangeFlag;
    bool SexChangeFlag;
    bool DeviceNumberChangeFlag;
    bool PhoneNumberChangeFlag;
};

#endif // MODIFYUSER_1_H
