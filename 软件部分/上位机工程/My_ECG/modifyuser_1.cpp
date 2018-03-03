#include "modifyuser_1.h"
#include "ui_modifyuser_1.h"
#include <QFile>
#include <QTextStream>
#include "modifyuser.h"
#include <QMessageBox>


extern QString path1;

ModifyUser_1::ModifyUser_1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyUser_1)
{
    ui->setupUi(this);
    ShowUserInfo();
}

ModifyUser_1::~ModifyUser_1()
{
    delete ui;
}

QString ModifyUser_1::InforExtraction(QString str)
{
    QStringList strlist = str.split(":");
    QString str1;
    for(int i=0;i<strlist.count();i++)
    {
       str1=(strlist.at(i).toLocal8Bit().data());
    }

    return str1;

}


void ModifyUser_1::ShowUserInfo()
{
    qint64 i=0;
    QString FileRootDir="E:/my-qt-example/MyECG/MyECG/My_ECG _V1.3/User/";
    QString FilePath=FileRootDir+path1+".txt";
    QString lineStr;
    QString lineStr1;
    QFile UserFile(FilePath);
    QTextStream in(&UserFile);
    QTextStream cout(stdout,  QIODevice::WriteOnly);
    if(UserFile.open(QIODevice::ReadOnly))
    {
        while(!in.atEnd())
        {
            lineStr=in.readLine();
            i++;
            lineStr1=InforExtraction(lineStr);
            lineStr1.toStdString();
            cout<<i<<":"<<lineStr1<<endl;
            switch(i)
            {
                case 1:ui->IDLineEdit->setText(lineStr1);break;
                case 4:ui->NameLineEdit->setText(lineStr1);break;
                case 7:ui->AgeLineEdit->setText(lineStr1);break;
                case 10:ui->SexLineEdit->setText(lineStr1);break;
                case 13:ui->DeviceNumberLineEdit->setText(lineStr1);break;
                case 16:ui->PhoneNumberLineEdit->setText(lineStr1);break;
                default:i++;break;
            }
        }
    }
    UserFile.close();
}

void ModifyUser_1::ModifyUser_2()
{

    QString NewId;
    QString NewName;
    QString NewSex;
    QString NewAge;
    QString NewDeviceNumber;
    QString NewPhoneNumber;

    if(IdChangeFlag==1)
    {
        IdChangeFlag=0;
        NewId=ui->IDLineEdit->text();
    }
    if(NameChangeFlag==1)
    {
        NameChangeFlag=0;
        NewName=ui->NameLineEdit->text();
    }
    if(AgeChangeFlag==1)
    {
        AgeChangeFlag=0;
        NewAge=ui->AgeLineEdit->text();
    }
    if(SexChangeFlag==1)
    {
        SexChangeFlag=0;
        NewSex=ui->SexLineEdit->text();
    }
    if(DeviceNumberChangeFlag==1)
    {
        DeviceNumberChangeFlag=0;
        NewDeviceNumber=ui->DeviceNumberLineEdit->text();
    }
    if(PhoneNumberChangeFlag==1)
    {
        PhoneNumberChangeFlag=0;
        NewPhoneNumber=ui->PhoneNumberLineEdit->text();
    }
    QString FileRootDir="E:/my-qt-example/MyECG/MyECG/My_ECG _V1.3/User/";
    QString FilePath=FileRootDir+path1+".txt";
    QFile UserFile1(FilePath);
    UserFile1.close();
    UserFile1.remove();
    FilePath=FileRootDir+NewId+".txt";
    QFile UserFile2(FilePath);
    UserFile2.open(QIODevice::ReadWrite|QIODevice::Text);
    QTextStream textStream(&UserFile2);
    textStream<<"User ID:"<<NewId<<endl<<tr("\n");
    textStream<<"User Name:"<<NewName<<endl<<tr("\n");
    textStream<<"User Age:"<<NewAge<<endl<<tr("\n");
    textStream<<"User Gender:"<<NewSex<<endl<<tr("\n");
    textStream<<"User Device Number:"<<NewDeviceNumber<<endl<<tr("\n");
    textStream<<"User Phone Number:"<<NewPhoneNumber<<endl<<tr("\n");
    textStream.flush();
    UserFile2.close();
    QMessageBox::warning(this,tr("修改用户"),tr("用户修改成功！！"));

}

void ModifyUser_1::on_SurePushBt_clicked()
{
    ModifyUser_2();
}

void ModifyUser_1::on_IDLineEdit_textChanged(const QString &arg1)
{
    IdChangeFlag=1;
}

void ModifyUser_1::on_NameLineEdit_textChanged(const QString &arg1)
{
    NameChangeFlag=1;
}

void ModifyUser_1::on_AgeLineEdit_textChanged(const QString &arg1)
{
    AgeChangeFlag=1;
}

void ModifyUser_1::on_SexLineEdit_textChanged(const QString &arg1)
{
    SexChangeFlag=1;
}

void ModifyUser_1::on_DeviceNumberLineEdit_textChanged(const QString &arg1)
{
    DeviceNumberChangeFlag=1;
}

void ModifyUser_1::on_PhoneNumberLineEdit_textChanged(const QString &arg1)
{
    PhoneNumberChangeFlag=1;
}

void ModifyUser_1::on_OffPushBt_clicked()
{
    ui->IDLineEdit->clear();
    ui->NameLineEdit->clear();
    ui->AgeLineEdit->clear();
    ui->SexLineEdit->clear();
    ui->DeviceNumberLineEdit->clear();
    ui->PhoneNumberLineEdit->clear();
}
