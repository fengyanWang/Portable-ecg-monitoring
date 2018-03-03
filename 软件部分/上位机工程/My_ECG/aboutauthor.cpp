#include "aboutauthor.h"
#include "ui_aboutauthor.h"

AboutAuthor::AboutAuthor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutAuthor)
{
    ui->setupUi(this);
    showauthor();

}

AboutAuthor::~AboutAuthor()
{
    delete ui;
}

void AboutAuthor::showauthor()
{
    setWindowTitle(tr("关于作者"));
    ui->AboutAuthorTextBrowser->append(tr("/***************************************************************************************/"));
    ui->AboutAuthorTextBrowser->append(tr("\n"));
    ui->AboutAuthorTextBrowser->append(tr("本软件是一个心电监测管理软件，实现的功能主要有：心电的监测，心电的回放，用户管理等。"));
    ui->AboutAuthorTextBrowser->append(tr("\n"));
    ui->AboutAuthorTextBrowser->append(tr("王丰焱，Vincent Wang,喜欢编程"));
    ui->AboutAuthorTextBrowser->append(tr("\n"));
    ui->AboutAuthorTextBrowser->append(tr("QQ:2314963088    邮箱：2314963088@qq.com"));
    ui->AboutAuthorTextBrowser->append(tr("\n"));
    ui->AboutAuthorTextBrowser->append(tr("/***************************************************************************************/"));
}
