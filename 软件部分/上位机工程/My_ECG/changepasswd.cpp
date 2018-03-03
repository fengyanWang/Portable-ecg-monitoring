#include "changepasswd.h"
#include "ui_changepasswd.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

ChangePassWd::ChangePassWd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePassWd)
{
    ui->setupUi(this);
    setFixedSize(568,341);
    ui->NoticeLabel->setVisible(false);

}

ChangePassWd::~ChangePassWd()
{
    delete ui;
}

void ChangePassWd::SetLineEchoMode()
{
    ui->RawPassWdLineEdit->setEchoMode(QLineEdit::Password);
    ui->NewPassWdLineEdit->setEchoMode(QLineEdit::Password);
    ui->NewPassWdLineEdit_1->setEchoMode(QLineEdit::Password);
}


void ChangePassWd::changePSW()
{

    ui->RawPassWdLineEdit->setFocus();
    QString PassWord;
    QString RawPSW=ui->RawPassWdLineEdit->text();
    QString NewPSW=ui->NewPassWdLineEdit->text();
    QString NewPSW_1=ui->NewPassWdLineEdit_1->text();
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
    PassWordFile.close();
    if(RawPSW!=PassWord)
    {
        QMessageBox::warning(this,tr("密码错误"),tr("您输入的密码错误，请重新输入"),QMessageBox::Ok);
        ui->RawPassWdLineEdit->clear();
        ui->RawPassWdLineEdit->setFocus();
    }
    else
    {
        if(NewPSW.length()<6)
        {
           QMessageBox::warning(this,tr("密码设置错误"),tr("您设置的密码有误，请按要求重新设置!!"),QMessageBox::Ok);
           ui->NoticeLabel->setVisible(true);
           ui->NewPassWdLineEdit->clear();
           ui->NewPassWdLineEdit_1->clear();
           ui->NewPassWdLineEdit->setFocus();
        }
        else
        {
           if(NewPSW!=NewPSW_1)
           {
              QMessageBox::warning(this,tr("密码设置错误"),tr("您两次输入的密码不同，请重新输入!!"),QMessageBox::Ok);
              ui->NoticeLabel->setVisible(false);
              ui->NewPassWdLineEdit->clear();
              ui->NewPassWdLineEdit_1->clear();
              ui->NewPassWdLineEdit->setFocus();
           }
           else
           {
               QFile PassWordFile1(filepath);
               PassWordFile1.open(QIODevice::ReadWrite|QIODevice::Text);
               QTextStream textStream(&PassWordFile1);
               textStream<<NewPSW;
               PassWordFile1.close();
               QMessageBox::warning(this,tr("修改密码"),tr("密码修改成功！！"));
           }
        }
    }

}

void ChangePassWd::on_OkPushBt_CW_clicked()
{
    changePSW();
}

void ChangePassWd::on_CanclePushBt_CW_clicked()
{
    ui->RawPassWdLineEdit->clear();
    ui->NewPassWdLineEdit->clear();
    ui->NewPassWdLineEdit_1->clear();
    ui->RawPassWdLineEdit->setFocus();
}
