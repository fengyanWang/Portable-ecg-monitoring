#include "logindialog.h"
#include "ui_logindialog.h"
#include "QMessageBox"
#include <QFile>
#include <QTextStream>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    setFixedSize(400,300);
    setWindowTitle(tr("登录"));
    ui->pwdLineEdit->setFocus();
    ui->loginBtn->setDefault(true);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginBtn_clicked()
{
    QString PassWord;
    if(ui->pwdLineEdit->text().isEmpty())
    {
        QMessageBox::information(this,tr("请输入密码"),tr("请先输入密码再登录！"),QMessageBox::Ok);
        ui->pwdLineEdit->setFocus();
    }
    else
    {
        QString filepath="E:/my-qt-example/MyECG/MyECG/My_ECG _V1.3/PassWord/PassWord.txt";
        QFile PassWordFile(filepath);
        QTextStream in(&PassWordFile);
        QTextStream cout(stdout,  QIODevice::WriteOnly);
        if(PassWordFile.open(QIODevice::ReadOnly))
        {
            while(!in.atEnd())
            {
                PassWord=in.readLine();
                cout<<"PassWord:"<<PassWord<<endl;
            }
        }
        if(PassWord==ui->pwdLineEdit->text())
        {
            QDialog::accept();
        }
        else
        {
            QMessageBox::warning(this,tr("密码错误"),tr("请输入正确密码再登录"),QMessageBox::Ok);
            ui->pwdLineEdit->clear();
            ui->pwdLineEdit->setFocus();
        }


    }
}

void LoginDialog::on_quitBtn_clicked()
{
    QDialog::reject();
}
