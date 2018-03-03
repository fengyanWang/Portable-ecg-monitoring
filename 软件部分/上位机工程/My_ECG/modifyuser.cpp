#include "modifyuser.h"
#include "ui_modifyuser.h"
#include "modifyuser_1.h"
#include <QMessageBox>
#include <QFile>

QString path1;


ModifyUser::ModifyUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyUser)
{
    ui->setupUi(this);
}

ModifyUser::~ModifyUser()
{
    delete ui;
}


void ModifyUser::UserModify()
{
    QString FileRootDir="E:/my-qt-example/MyECG/MyECG/My_ECG _V1.3/User/";
    QString UserID=ui->ModifyUserLineEdit->text();
    path1=UserID;
    QString UserFilePath=FileRootDir+UserID+".txt";
    QFile UserFile(UserFilePath);
    bool exit=UserFile.exists();
    if(!exit)
    {
       QMessageBox::warning(this,tr("修改用户"),tr("您要修改的用户不存在，请确认用户ID是否输入正确！！！"));
    }
    else
    {
        UserFile.close();
        ModifyUser_1 *modifyuser1=new ModifyUser_1;
        modifyuser1->show();

    }

}

void ModifyUser::on_ModifyUserOkPushBt_clicked()
{

    UserModify();



}


void ModifyUser::on_ModifyUserCanclePushBt_clicked()
{
    ui->ModifyUserLineEdit->clear();

}
