#ifndef CHANGEPASSWD_H
#define CHANGEPASSWD_H

#include <QDialog>

namespace Ui {
class ChangePassWd;
}

class ChangePassWd : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePassWd(QWidget *parent = 0);
    ~ChangePassWd();

private slots:
    void on_OkPushBt_CW_clicked();

    void on_CanclePushBt_CW_clicked();

private:
    Ui::ChangePassWd *ui;
    void changePSW();
    void SetLineEchoMode();
};

#endif // CHANGEPASSWD_H
