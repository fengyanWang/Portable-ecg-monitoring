#include "delateuser.h"
#include "ui_delateuser.h"
#include <QFile>
#include <QMessageBox>

DelateUser::DelateUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DelateUser)
{
    ui->setupUi(this);
}

DelateUser::~DelateUser()
{
    delete ui;
}


void DelateUser::delateUser()
{
    QString FileRootDir="E:/my-qt-example/MyECG/MyECG/My_ECG _V1.3/User/";
    QString UserID=ui->DelateUserLineEdit->text();

    QString FilePath=FileRootDir+UserID+".txt";
    QFile UserFile(FilePath);
    bool exit=UserFile.exists();
    if(!exit)
    {
       QMessageBox::warning(this,tr("删除用户"),tr("您要删除的用户不存在，请确认用户ID是否输入正确！！！"));
    }
    else
    {
       UserFile.close();
       switch(QMessageBox::question(this,tr("删除用户"),tr("是否要删除您选择的用户，用户一经删除将无法恢复，请慎重考虑！！"),
                                    QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok))
       {
       case QMessageBox::Ok:
        {
           UserFile.remove();
           QMessageBox::warning(this,tr("删除用户"),tr("用户删除成功！！！"));
           break;
        }
       case QMessageBox::Cancel:
        {
           break;
        }
       default:
        {
           break;
        }
       }
    }

}

void DelateUser::on_OkPushBt_DU_clicked()
{
    delateUser();
}



void DelateUser::on_CanclePushBt_DU_clicked()
{
    ui->DelateUserLineEdit->clear();
}
