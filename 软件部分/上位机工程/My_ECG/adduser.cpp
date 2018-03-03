#include "adduser.h"
#include "ui_adduser.h"
#include <string>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>



AddUser::AddUser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddUser)
{
    ui->setupUi(this);
    ui->UserIDLineEdit->setFocus();
}

AddUser::~AddUser()
{
    delete ui;
}

void AddUser::UserAdd()
{
    bool ok;
    QString FileRootDir="E:/my-qt-example/MyECG/MyECG/My_ECG _V1.3/User/";

    QString UserID=ui->UserIDLineEdit->text();
    QString UserName=ui->UserNameLineEdit->text();
    QString UserAge=ui->UserAgeLineEdit->text();
    QString UserSex=ui->UserSexLineEdit->text();
    QString UserDeviceNumber=ui->UserDeviceLineEdit->text();
    QString UserPhoneNumber=ui->UserPhoneNumberLineEdit->text();

    QString FilePath=FileRootDir+UserID+".txt";
//以用户ID号创建文件
    QFile UserFile(FilePath);
    bool exit=UserFile.exists();
    if(exit)
    {
       QMessageBox::warning(this,tr("创建新用户"),tr("该用户已经存在！请重新选择用户ID"));
    }
    else if((ui->UserIDLineEdit->text().length())!=6)
    {
         QMessageBox::warning(this,tr("请输入正确的ID号"),tr("用户ID为6位数！！"));
    }
    else if((ui->UserNameLineEdit->text().length()>32))
    {
         QMessageBox::warning(this,tr("请输入正确的姓名"),tr("您输入的名字太长，请重新输入！！"));
    }
    else if((ui->UserAgeLineEdit->text().toInt(&ok,10)<0)||(ui->UserAgeLineEdit->text().toInt(&ok,10)>130))
    {
        QMessageBox::warning(this,tr("请输入正确的年龄"),tr("您输入的年龄有误！！"));
    }
    else if((ui->UserDeviceLineEdit->text().length()!=8))
    {
        QMessageBox::warning(this,tr("请输入正确的设备编号"),tr("您输入的设备编号有误，请重新输入！！"));
    }
    else if((ui->UserPhoneNumberLineEdit->text().length()!=11))
    {
        QMessageBox::warning(this,tr("请输入正确的手机号码"),tr("您输入的手机号码有误，请重新输入！！"));
    }
    else
    {
        UserFile.open(QIODevice::WriteOnly);
        UserFile.close();
//打开用户文件写入数据
        QFile UserFile1(FilePath);
        UserFile1.open(QIODevice::ReadWrite|QIODevice::Text);
        QTextStream textStream(&UserFile1);
        textStream<<"User ID:"<<UserID<<endl<<tr("\n");
        textStream<<"User Name:"<<UserName<<endl<<tr("\n");
        textStream<<"User Age:"<<UserAge<<endl<<tr("\n");
        textStream<<"User Gender:"<<UserSex<<endl<<tr("\n");
        textStream<<"User Device Number:"<<UserDeviceNumber<<endl<<tr("\n");
        textStream<<"User Phone Number:"<<UserPhoneNumber<<endl<<tr("\n");
        textStream.flush();
        UserFile1.close();
        QMessageBox::warning(this,tr("创建新用户"),tr("用户创建成功！！"));
    }
}


void AddUser::on_OkPushBt_clicked()
{
       UserAdd();
}

void AddUser::on_CanclePushButton_2_clicked()
{
    ui->UserIDLineEdit->clear();
    ui->UserNameLineEdit->clear();
    ui->UserAgeLineEdit->clear();
    ui->UserDeviceLineEdit->clear();
    ui->UserSexLineEdit->clear();
    ui->UserPhoneNumberLineEdit->clear();
}


void AddUser::on_UserIDLineEdit_textChanged(const QString &arg1)
{
    ;
}

void AddUser::on_ReturnPushBt_clicked()
{
    ;
}
