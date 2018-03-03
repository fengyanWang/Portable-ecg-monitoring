#include "myecg.h"
#include "ui_myecg.h"
#include "adduser.h"
#include "delateuser.h"
#include <QPixmap>
#include <string>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <stdio.h>
#include <modifyuser.h>
#include <aboutauthor.h>
#include <QInputDialog>
#include <QMessageBox>
#include "changepasswd.h"
#include "path.h"




//主界面的构造函数
MyECG::MyECG(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyECG)
{
    ui->setupUi(this);
    creatMenuBar();
    serialInit();
    ECGWavePlotInit();
    ECGWavePlotInit1();

    IDLabel=new QLabel;
    IDLabel->setFrameStyle(QFrame::Panel|QFrame::Sunken);

}

//主界面的析构函数
MyECG::~MyECG()
{
    delete ui;
}

//创建工具栏
void MyECG::creatMenuBar()
{
//心电部分
    LeadConnectAction=new QAction(tr("导联连接"),this);
    ECGWatchAction=new QAction(tr("心电监测"),this);
    ECGPlayBackAction=new QAction(tr("心电回放"),this);
    LeadConnectAction->setShortcut(tr("Ctrl+L"));
    ECGWatchAction->setShortcut(tr("Ctrl+W"));
    ECGPlayBackAction->setShortcut(tr("Ctrl+P"));

    ECGMenu=menuBar()->addMenu(tr("心电"));
    ECGMenu->addAction(LeadConnectAction);
    ECGMenu->addSeparator();
    ECGMenu->addAction(ECGWatchAction);
    ECGMenu->addSeparator();
    ECGMenu->addAction(ECGPlayBackAction);

//用户管理部分
    UserManageAction=new QAction(tr("用户管理"),this);
    ChangePassWdAction=new QAction(tr("修改密码"),this);
    UserManageAction->setShortcut(tr("Ctrl+M"));
    ChangePassWdAction->setShortcut(tr("Ctrl+C"));

    UserMenu=menuBar()->addMenu(tr("用户"));
    UserMenu->addAction(UserManageAction);
    UserMenu->addSeparator();
    UserMenu->addAction(ChangePassWdAction);

//其他
    ExitAction=new QAction(tr("退出"),this);
    ExitAction->setShortcut(tr("Ctrl+E"));

    AboutAuthorAction=new QAction(tr("关于作者"),this);
    AboutAuthorAction->setShortcut(tr("Ctrl+A"));

    ExitMenu=menuBar()->addMenu(tr("其他"));
    ExitMenu->addAction(AboutAuthorAction);
    ExitMenu->addSeparator();
    ExitMenu->addAction(ExitAction);

//功能实现部分
    connect(LeadConnectAction,SIGNAL(triggered()),this,SLOT(on_LeadConnect_clicked()));
    connect(ECGWatchAction,SIGNAL(triggered()),this,SLOT(on_ECGWatch_clicked()));
    connect(ECGPlayBackAction,SIGNAL(triggered()),this,SLOT(on_ECGPlayBack_clicked()));
    connect(UserManageAction,SIGNAL(triggered()),this,SLOT(on_UserManage_clicked()));
    connect(ChangePassWdAction,SIGNAL(triggered()),this,SLOT(on_ChangePassWd_clicked()));
    connect(ExitAction,SIGNAL(triggered()),this,SLOT(on_Exit_clicked()));
    connect(AboutAuthorAction,SIGNAL(triggered(bool)),this,SLOT(on_AboutAuthor_clicked()));

}



//工具栏的槽函数
//导联链接槽函数
void MyECG::on_LeadConnect_clicked()
{
     setFixedSize(750,534);
    ui->MyECGStackedWidget->setCurrentIndex(0);
}
//心电监测部分槽函数
void MyECG::on_ECGWatch_clicked()
{
    setFixedSize(740,548);
    ui->MyECGStackedWidget->setCurrentIndex(1);

}
//心电回放槽函数
void MyECG::on_ECGPlayBack_clicked()
{
     setFixedSize(745,429);
    ui->MyECGStackedWidget->setCurrentIndex(2);
}
//用户管理槽函数
void MyECG::on_UserManage_clicked()
{
    setFixedSize(750,534);
    ui->MyECGStackedWidget->setCurrentIndex(3);
}
//密码修改槽函数
void MyECG::on_ChangePassWd_clicked()
{

    ChangePassWd *changepwd=new ChangePassWd;
    changepwd->show();
}
//关于作者槽函数
void MyECG::on_AboutAuthor_clicked()
{

    AboutAuthor *aboutauthor=new AboutAuthor;
    aboutauthor->show();
}
//退出槽函数
void MyECG::on_Exit_clicked()
{
    this->close();
}


//page0
void MyECG::on_ThreeLeadPushBt_clicked()
{

    ui->label->setPixmap(QPixmap(":/new/leadConnectPage/picture/my/3.bmp"));
}

void MyECG::on_FiveLeadPushBt_clicked()
{
    ui->label->setPixmap(QPixmap(":/new/leadConnectPage/picture/my/5.bmp"));
}

void MyECG::on_ClearPushBt_clicked()
{
    ui->label->setPixmap(QPixmap(":/new/leadConnectPage/picture1/27.jpg"));
}


//page1
//串口的初始化
void MyECG::serialInit()
{
//支持的串口号
    ui->PortNameComboBox->addItem(tr("COM1"));
    ui->PortNameComboBox->addItem(tr("COM2"));
    ui->PortNameComboBox->addItem(tr("COM3"));
    ui->PortNameComboBox->addItem(tr("COM4"));
    ui->PortNameComboBox->addItem(tr("COM5"));
    ui->PortNameComboBox->addItem(tr("COM6"));
    ui->PortNameComboBox->addItem(tr("COM7"));
    ui->PortNameComboBox->addItem(tr("COM8"));
    ui->PortNameComboBox->addItem(tr("COM9"));
    ui->PortNameComboBox->addItem(tr("COM10"));
//支持的波特率
    ui->BaudRateComboBox->addItem(tr("110"));
    ui->BaudRateComboBox->addItem(tr("300"));
    ui->BaudRateComboBox->addItem(tr("600"));
    ui->BaudRateComboBox->addItem(tr("1200"));
    ui->BaudRateComboBox->addItem(tr("4800"));
    ui->BaudRateComboBox->addItem(tr("9600"));
    ui->BaudRateComboBox->addItem(tr("19200"));
    ui->BaudRateComboBox->addItem(tr("115200"));

}
//读取串口数据
void MyECG::readMyCom()
{
    //读取数据缓冲区中的所有数据给临时变量temp
    QByteArray temp = myCom->readAll();
}

//打开串口
void MyECG::on_OpenComPushBt_clicked()
{
    QString portName = ui->PortNameComboBox->currentText();//获取串口名
    myCom = new Win_QextSerialPort(portName,QextSerialBase::EventDriven);
    //定义串口对象
    myCom->open(QIODevice::ReadWrite);//以读写方式打开串口
    if(ui->BaudRateComboBox->currentText()==tr("110"))//根据波特率窗口设置串口波特率
    myCom->setBaudRate(BAUD110);
    else if(ui->BaudRateComboBox->currentText()==tr("300"))
    myCom->setBaudRate(BAUD300);
    else if(ui->BaudRateComboBox->currentText()==tr("600"))
    myCom->setBaudRate(BAUD600);
    else if(ui->BaudRateComboBox->currentText()==tr("1200"))
    myCom->setBaudRate(BAUD1200);
    else if(ui->BaudRateComboBox->currentText()==tr("2400"))
    myCom->setBaudRate(BAUD2400);
    else if(ui->BaudRateComboBox->currentText()==tr("4800"))
    myCom->setBaudRate(BAUD4800);
    else if(ui->BaudRateComboBox->currentText()==tr("9600"))
    myCom->setBaudRate(BAUD9600);
    else if(ui->BaudRateComboBox->currentText()==tr("19200"))
    myCom->setBaudRate(BAUD19200);
    else if(ui->BaudRateComboBox->currentText()==tr("115200"))
    myCom->setBaudRate(BAUD115200);
    //设置数据位
    myCom->setDataBits(DATA_8);
    //设置奇偶校验位
    myCom->setParity(PAR_NONE);
    //设置停止位
    myCom->setStopBits(STOP_1);
    myCom->setFlowControl(FLOW_OFF);//设置为无数据流控制
    myCom->setTimeout(500);//延时
    connect(myCom,SIGNAL(readyRead()),this,SLOT(readMyCom())); //信号和槽函数连接，当串口缓冲区有数据时，进行读串口操作
    ui->OpenComPushBt->setEnabled(false);//打开串口后“打开串口摁钮”不可用
    ui->CloseComPushBt->setEnabled(true);//打开串口后”关闭串口摁钮“可用
    ui->BaudRateComboBox->setEnabled(false);
    ui->PortNameComboBox->setEnabled(false);


    ui->LeadCheckBox_1->setCheckState(Qt::Checked);
    ui->LeadCheckBox_2->setCheckState(Qt::Checked);
    ui->LeadCheckBox_3->setCheckState(Qt::Checked);
    ui->LeadCheckBox_4->setCheckState(Qt::Checked);
    ui->LeadCheckBox_5->setCheckState(Qt::Checked);


    ui->HeartRateLabel_1->setText(tr("80"));

}

//关闭串口
void MyECG::on_CloseComPushBt_clicked()
{
    myCom->close();//关闭串口
    ui->OpenComPushBt->setEnabled(true);//关闭串口后“打开串口摁钮”可用
    ui->CloseComPushBt->setEnabled(false);//关闭串口后”关闭串口摁钮“不可用
    ui->BaudRateComboBox->setEnabled(true);
    ui->PortNameComboBox->setEnabled(true);
}


//画心电波形初始化函数
void MyECG::ECGWavePlotInit()
{
    QTime time;
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);

    for(int i=0;i<5001;i++)
    {
        ECGWave1Date.append(0);
        ECGWave2Date.append(0);
        ECGWave3Date.append(0);
    }
    //实例化3条曲线
    ECGWave1Plot = new QwtPlotCurve();
    ECGWave2Plot = new QwtPlotCurve();
    ECGWave3Plot = new QwtPlotCurve();
    //设置画布的标题
    ui->ECGWave1QwtPlot->setTitle(tr("ECG Wave I"));
    ui->ECGWave2QwtPlot->setTitle(tr("ECG Wave II"));
    ui->ECGWave3QwtPlot->setTitle(tr("ECG Wave III"));
    //设置画布的Y轴坐标名称
    ui->ECGWave1QwtPlot->setAxisTitle(QwtPlot::yLeft,"CH I");
    ui->ECGWave2QwtPlot->setAxisTitle(QwtPlot::yLeft,"CH II");
    ui->ECGWave3QwtPlot->setAxisTitle(QwtPlot::yLeft,"CH III");
    //设置画布的X轴坐标名称
    ui->ECGWave1QwtPlot->setAxisTitle(QwtPlot::xBottom,"Time/s");
    ui->ECGWave2QwtPlot->setAxisTitle(QwtPlot::xBottom,"Time/s");
    ui->ECGWave3QwtPlot->setAxisTitle(QwtPlot::xBottom,"Time/s");
    //设置画布的Y轴刻度
    ui->ECGWave1QwtPlot->setAxisScale(QwtPlot::yLeft,-1,3,1);
    ui->ECGWave2QwtPlot->setAxisScale(QwtPlot::yLeft,-1,3,1);
    ui->ECGWave3QwtPlot->setAxisScale(QwtPlot::yLeft,-1,3,1);
    //设置画布的X轴刻度
    ui->ECGWave1QwtPlot->setAxisScale(QwtPlot::xBottom,0,3,1);
    ui->ECGWave2QwtPlot->setAxisScale(QwtPlot::xBottom,0,3,1);
    ui->ECGWave3QwtPlot->setAxisScale(QwtPlot::xBottom,0,3,1);
    //设置画布的背景为深蓝色（canvas让我的深蓝色背景的四个角有一定的弧度，没有它的话，则深蓝色背景是一个矩形）
    QwtPlotCanvas *canvas1 = new QwtPlotCanvas();
    QwtPlotCanvas *canvas2 = new QwtPlotCanvas();
    QwtPlotCanvas *canvas3 = new QwtPlotCanvas();
    canvas1->setBorderRadius( 10 );
    canvas2->setBorderRadius( 10 );
    canvas3->setBorderRadius( 10 );
    ui->ECGWave1QwtPlot->setCanvas(canvas1);
    ui->ECGWave2QwtPlot->setCanvas(canvas2);
    ui->ECGWave3QwtPlot->setCanvas(canvas3);
    //设置缩放
    QwtPlotZoomer *zoomer1=new QwtPlotZoomer(ui->ECGWave1QwtPlot->canvas());
    zoomer1->setRubberBandPen( QColor( Qt::blue ) );
    zoomer1->setTrackerPen( QColor( Qt::yellow ) );
    zoomer1->setMousePattern(QwtEventPattern::MouseSelect2,Qt::RightButton, Qt::ControlModifier );
    zoomer1->setMousePattern(QwtEventPattern::MouseSelect3,Qt::RightButton); //默认的滑轮及右键缩放功能  图形的整体缩放

    QwtPlotZoomer *zoomer2=new QwtPlotZoomer(ui->ECGWave2QwtPlot->canvas());
    zoomer2->setRubberBandPen( QColor( Qt::blue ) );
    zoomer2->setTrackerPen( QColor( Qt::yellow ) );
    zoomer2->setMousePattern(QwtEventPattern::MouseSelect2,Qt::RightButton, Qt::ControlModifier );
    zoomer2->setMousePattern(QwtEventPattern::MouseSelect3,Qt::RightButton); //默认的滑轮及右键缩放功能  图形的整体缩放

    QwtPlotZoomer *zoomer3=new QwtPlotZoomer(ui->ECGWave3QwtPlot->canvas());
    zoomer3->setRubberBandPen( QColor( Qt::blue ) );
    zoomer3->setTrackerPen( QColor( Qt::yellow ) );
    zoomer3->setMousePattern(QwtEventPattern::MouseSelect2,Qt::RightButton, Qt::ControlModifier );
    zoomer3->setMousePattern(QwtEventPattern::MouseSelect3,Qt::RightButton); //默认的滑轮及右键缩放功能  图形的整体缩放

    //鼠标滚轮放大缩小
    QwtPlotMagnifier *PM1 = new QwtPlotMagnifier( ui->ECGWave1QwtPlot->canvas());
    QwtPlotMagnifier *PM2= new QwtPlotMagnifier( ui->ECGWave2QwtPlot->canvas());
    QwtPlotMagnifier *PM3= new QwtPlotMagnifier( ui->ECGWave3QwtPlot->canvas());

    //设置波形图背景为半夜蓝
    ui->ECGWave1QwtPlot->setCanvasBackground( QColor( "MidnightBlue" ));
    ui->ECGWave2QwtPlot->setCanvasBackground( QColor( "MidnightBlue" ));
    ui->ECGWave3QwtPlot->setCanvasBackground( QColor( "MidnightBlue" ));
    //绘制图中的虚线
    QwtPlotGrid * mygrid1 = new QwtPlotGrid;
    QwtPlotGrid * mygrid2 = new QwtPlotGrid;
    QwtPlotGrid * mygrid3 = new QwtPlotGrid;
    // 绘制对应于X轴单位刻度的小格子
    mygrid1->enableXMin(true);
    mygrid2->enableXMin(true);
    mygrid3->enableXMin(true);
    // 绘制对应于Y轴单位刻度的小格子
    mygrid1->enableYMin(true);
    mygrid2->enableYMin(true);
    mygrid3->enableYMin(true);
    //设置大格子的线形
    mygrid1->setMajorPen(QPen(Qt::white, 0, Qt::DotLine));
    mygrid2->setMajorPen(QPen(Qt::white, 0, Qt::DotLine));
    mygrid3->setMajorPen(QPen(Qt::white, 0, Qt::DotLine));
    //设置小格子的线形
    mygrid1->setMinorPen(QPen(Qt::gray, 0 , Qt::DotLine));
    mygrid1->attach(ui->ECGWave1QwtPlot);
    mygrid2->setMinorPen(QPen(Qt::gray, 0 , Qt::DotLine));
    mygrid2->attach(ui->ECGWave2QwtPlot);
    mygrid3->setMinorPen(QPen(Qt::gray, 0 , Qt::DotLine));
    mygrid3->attach(ui->ECGWave3QwtPlot);

    //平滑3条曲线
    ECGWave1Plot->attach(ui->ECGWave1QwtPlot);
    ECGWave1Plot->setPen(QPen(Qt::red));//曲线的颜色
    ECGWave1Plot->setCurveAttribute(QwtPlotCurve::Fitted, true); //使曲线更加平滑

    ECGWave2Plot->attach(ui->ECGWave2QwtPlot);
    ECGWave2Plot->setPen(QPen(Qt::yellow));
    ECGWave2Plot->setCurveAttribute(QwtPlotCurve::Fitted, true); //使曲线更加平滑

    ECGWave3Plot->attach(ui->ECGWave3QwtPlot);
    ECGWave3Plot->setPen(QPen(Qt::green));
    ECGWave3Plot->setCurveAttribute(QwtPlotCurve::Fitted, true); //使曲线更加平滑

    connect(&UpdateTimer,SIGNAL(timeout()),this,SLOT(UpdateDateSlot()));


    ui->PausePushBt->setEnabled(false);

}


//用于更新ydata,实际情况就是read数据
void MyECG::UpdateDateSlot()
{
    static QTime dataTime(QTime::currentTime());
    long int eltime = dataTime.elapsed();
    static int lastpointtime = 0;
    static  int temp1=0;
    static  int temp2=0;
    static  int temp3=0;
    int size = (eltime - lastpointtime);
    bool ok;

 //有数据传入
    if(size>0)
    {
         ECGWave1Date.erase(ECGWave1Date.begin(),ECGWave1Date.begin()+size);//擦除多余的数据
         ECGWave2Date.erase(ECGWave2Date.begin(),ECGWave2Date.begin()+size);//擦除多余的数据
         ECGWave3Date.erase(ECGWave3Date.begin(),ECGWave3Date.begin()+size);//擦除多余的数据

         for(int i=1;i<size+1;i++)
         {
            temp1=lastpointtime+i;
            temp1=temp1%(ECGWave1DateArry.length());

            temp2=lastpointtime+i;
            temp2=temp3%(ECGWave2DateArry.length());

            temp3=lastpointtime+i;
            temp3=temp3%(ECGWave3DateArry.length());

            ECGWave1Date.append(ECGWave1DateArry.at(temp1));
            ECGWave2Date.append(ECGWave2DateArry.at(temp1));
            ECGWave3Date.append(ECGWave3DateArry.at(temp1));
         }
            lastpointtime = eltime;
    }

        showTemp();
        ui->TempLabel_1->setText(QString::number(TempDate));

        ui->ECGWave1QwtPlot->setAxisAutoScale(QwtPlot::yLeft,&ok);
        ECGWave1Plot->setSamples(xAixs1Data,ECGWave1Date);
        ECGWave1Plot->attach(ui->ECGWave1QwtPlot);
        ui->ECGWave1QwtPlot->replot();

        ui->ECGWave2QwtPlot->setAxisAutoScale(QwtPlot::yLeft,&ok);
        ECGWave2Plot->setSamples(xAixs2Data,ECGWave2Date);
        ECGWave2Plot->attach(ui->ECGWave2QwtPlot);
        ui->ECGWave2QwtPlot->replot();

        ui->ECGWave3QwtPlot->setAxisAutoScale(QwtPlot::yLeft,&ok);
        ECGWave3Plot->setSamples(xAixs3Data,ECGWave3Date);
        ECGWave3Plot->attach(ui->ECGWave3QwtPlot);
        ui->ECGWave3QwtPlot->replot();
}


void MyECG::showTemp()
{
   double wucha=qrand()%2;
   TempDate=30-wucha;
}

void MyECG::openfile()
{
    QString lineStr1;
//    QFile ECGFile1("C:/Users/WFY/Desktop/ECGDate/ECG_1.txt");
    QFile ECGFile1(PATH1);
    QTextStream in1(&ECGFile1);
    if(ECGFile1.open(QIODevice::ReadOnly))
    {

        while(!in1.atEnd())
        {
           lineStr1=in1.readLine();
           StrToHex(lineStr1,FileDate1);
           xAixs1Data.append(FileDate1[0]);
           ECGWave1DateArry.append(FileDate1[1]);
        }

     ECGFile1.close();
    }

     QString lineStr2;
//     QFile ECGFile2("E:/my-qt-example/MyECG/MyECG/My_ECG _V1.6/ECGDate/ECG2.txt");
     QFile ECGFile2(PATH2);
     QTextStream in2(&ECGFile2);
     if(ECGFile2.open(QIODevice::ReadOnly))
     {

         while(!in2.atEnd())
         {
            lineStr2=in2.readLine();
            StrToHex(lineStr2,FileDate2);
            xAixs2Data.append(FileDate2[0]);
            ECGWave2DateArry.append(FileDate2[1]);
         }

      ECGFile2.close();
     }

      QString lineStr3;
//      QFile ECGFile3("E:/my-qt-example/MyECG/MyECG/My_ECG _V1.6/ECGDate/ECG3.txt");
      QFile ECGFile3(PATH3);
      QTextStream in3(&ECGFile3);
      if(ECGFile3.open(QIODevice::ReadOnly))
      {

          while(!in3.atEnd())
          {
              lineStr3=in3.readLine();
              StrToHex(lineStr3,FileDate3);
              xAixs3Data.append(FileDate3[0]);
              ECGWave3DateArry.append(FileDate3[1]);
          }

          ECGFile3.close();
      }
}


//画心电波形函数
void MyECG::PlotECGWave()
{

//    int i=0;
//    ECGDate1=sin(PI*i)*1000;
//    ECGDate2=cos(PI*i)*1000;
//    ECGDate3=ECGDate1+ECGDate1;

//    if(ECGWave1Date.size()<250)
//    {

//        ECGWave1Date.push_front((double)ECGDate1);
//        ECGWave2Date.push_front((double)ECGDate2);
//        ECGWave3Date.push_front((double)ECGDate3);
//        xAixsData.append(azhux);
//        azhux += 0.04; //每接收到一组新的数据，老数据右移0.04个单位
//    }
//    else
//    {
//        ECGWave1Date.push_front((double)ECGDate1);
//        ECGWave1Date.pop_back();
//        ECGWave2Date.push_front((double)ECGDate2);
//        ECGWave2Date.pop_back();
//        ECGWave3Date.push_front((double)ECGDate3);
//        ECGWave3Date.pop_back();
//    }
//    ECGWave1Plot->setSamples(xAixs1Data,ECGWave1Date);
//    ui->ECGWave1QwtPlot->replot();
//    ECGWave2Plot->setSamples(xAixs2Data,ECGWave2Date);
//    ui->ECGWave2QwtPlot->replot();
//    ECGWave3Plot->setSamples(xAixs3Data,ECGWave3Date);
//    ui->ECGWave3QwtPlot->replot();

}



void MyECG::on_StartPushBt_clicked()
{

   openfile();
   UpdateTimer.start(800);
   ui->StartPushBt->setEnabled(false);
   ui->PausePushBt->setEnabled(true);


}

void MyECG::on_PausePushBt_clicked()
{
    UpdateTimer.stop();
    ui->StartPushBt->setEnabled(true);
    ui->PausePushBt->setEnabled(false);

}











//page2
void MyECG::ECGWavePlotInit1()
{
    for(int i=0;i<1279;i++)
    {
        ECGWaveDate.append(0);
    }

    //实例化3条曲线
    ECGWavePlot = new QwtPlotCurve();

    //设置画布的标题
    ui->ECGWaveQwtPlot->setTitle(tr("ECG Wave"));
    //设置画布的Y轴坐标名称
    ui->ECGWaveQwtPlot->setAxisTitle(QwtPlot::yLeft,"ECG Wave");
    //设置画布的X轴坐标名称
    ui->ECGWaveQwtPlot->setAxisTitle(QwtPlot::xBottom,"Time/s");
    //设置画布的Y轴刻度
    ui->ECGWaveQwtPlot->setAxisScale(QwtPlot::yLeft,-1,3,1);
    //设置画布的X轴刻度
    ui->ECGWaveQwtPlot->setAxisScale(QwtPlot::xBottom,0,3,1);
    //设置画布的背景为深蓝色（canvas让我的深蓝色背景的四个角有一定的弧度，没有它的话，则深蓝色背景是一个矩形）
    QwtPlotCanvas *canvas4 = new QwtPlotCanvas();
    canvas4->setBorderRadius( 10 );
    ui->ECGWaveQwtPlot->setCanvas(canvas4);
    //设置缩放
    QwtPlotZoomer *zoomer4=new QwtPlotZoomer(ui->ECGWaveQwtPlot->canvas());
    zoomer4->setRubberBandPen( QColor( Qt::blue ) );
    zoomer4->setTrackerPen( QColor( Qt::yellow ) );
    zoomer4->setMousePattern(QwtEventPattern::MouseSelect2,Qt::RightButton, Qt::ControlModifier );
    zoomer4->setMousePattern(QwtEventPattern::MouseSelect3,Qt::RightButton); //默认的滑轮及右键缩放功能  图形的整体缩放

    //鼠标滚轮放大缩小
    QwtPlotMagnifier *PM4 = new QwtPlotMagnifier( ui->ECGWaveQwtPlot->canvas());

//    //鼠标左键拖动波形
//    QwtPlotPanner *PQ1= new QwtPlotPanner( ui->ECGWaveQwtPlot->canvas());
    //设置波形图背景为半夜蓝
    ui->ECGWaveQwtPlot->setCanvasBackground( QColor( "MidnightBlue" ));
    //绘制图中的虚线
    QwtPlotGrid * mygrid4 = new QwtPlotGrid;
    // 绘制对应于X轴单位刻度的小格子
    mygrid4->enableXMin(true);
    // 绘制对应于Y轴单位刻度的小格子
    mygrid4->enableYMin(true);
    //设置大格子的线形
    mygrid4->setMajorPen(QPen(Qt::white, 0, Qt::DotLine));
    //设置小格子的线形
    mygrid4->setMinorPen(QPen(Qt::gray, 0 , Qt::DotLine));
    mygrid4->attach(ui->ECGWaveQwtPlot);
    //平滑3条曲线
    ECGWavePlot->attach(ui->ECGWaveQwtPlot);
    ECGWavePlot->setPen(QPen(Qt::red));//曲线的颜色
    ECGWavePlot->setCurveAttribute(QwtPlotCurve::Fitted, true); //使曲线更加平滑

    connect(&UpdateTimer1,SIGNAL(timeout()),this,SLOT(UpdateDateSlot1()));

    ui->PausePushBt_1->setEnabled(false);
    ui->StartPushBt_1->setEnabled(false);
}



//用于更新ydata,实际情况就是read数据
void MyECG::UpdateDateSlot1()
{
    bool ok;
    static QTime dataTime(QTime::currentTime());
    long int eltime = dataTime.elapsed();
    static int lastpointtime = 0;
    QTextStream cout(stdout,  QIODevice::WriteOnly);
    int size = (eltime - lastpointtime);
    static  int temp=0;

    if(lastpointtime>=2147483647)
    {
       lastpointtime=0;
    }

 //有数据传入
    if(size>0)
    {
         ECGWaveDate.erase(ECGWaveDate.begin(),ECGWaveDate.begin()+size);//擦除多余的数据

         for(int i=1;i<size+1;i++)
         {
             temp=lastpointtime+i;
             temp=temp%(ECGDateArry.length());
             ECGWaveDate.append(ECGDateArry.at(temp));
         }

         lastpointtime = eltime;
    }

        ui->ECGWaveQwtPlot->setAxisAutoScale(QwtPlot::yLeft,&ok);
        ECGWavePlot->setSamples(xAixsData1,ECGWaveDate);
        ECGWavePlot->attach(ui->ECGWaveQwtPlot);
        ui->ECGWaveQwtPlot->replot();

}


void MyECG::StrToHex(QString str,double *fliedate)
{

    QStringList strlist = str.split("\t",QString::SkipEmptyParts);
    QTextStream cout(stdout,  QIODevice::WriteOnly);
    for(int i=0;i<strlist.count();i++)
    {
       QString str1=strlist.at(i);
       fliedate[i]=(str1.toDouble(0));
    }
}

void MyECG::on_StartPushBt_1_clicked()
{

    UpdateTimer1.start(800);
    ui->StartPushBt_1->setEnabled(false);
    ui->PausePushBt_1->setEnabled(true);
}

void MyECG::on_PausePushBt_1_clicked()
{
    UpdateTimer1.stop();
    ui->StartPushBt_1->setEnabled(true);
    ui->PausePushBt_1->setEnabled(false);
}

void MyECG::on_OpenFilePushBt_2_clicked()
{
    static int num=0;
    QString s=QFileDialog::getOpenFileName(this,"Open ECG File","/","Text file(*.txt)");
    QString lineStr;
    ui->ECGFilePathLineEdit->setText(s);
    QFile ECGFile(s);
    QFile ECGFile8("C:/Users/WFY/Desktop/ECG.txt");
    QTextStream out(&ECGFile8);
    ECGFile8.open(QIODevice::ReadWrite|QIODevice::Text);
    QTextStream in(&ECGFile);
    if(ECGFile.open(QIODevice::ReadOnly))
    {
        ui->StartPushBt_1->setEnabled(true);
        while(!in.atEnd())
        {
            lineStr=in.readLine();
            StrToHex(lineStr,FileDate);
            xAixsData1.append(FileDate[0]);
            ECGDateArry.append(FileDate[1]);
            out<<FileDate[1]<<",";
            num++;
            if(num%10==0)
            {
                out<<endl;
            }
        }
        printf("num:%d\r\n",num);
     ECGFile.close();
    }
}

void MyECG::Max_Min(const QVector<double> ECGDateArry, double *max, double *min)
{
    *max=ECGDateArry.at(0);
    *min=ECGDateArry.at(0);
    for(int i=0;i<ECGDateArry.length();i++)
    {
        if(ECGDateArry.at(i)>*max)
        {
            *max=ECGDateArry.at(i);
        }
    }
    for(int i=0;i<ECGDateArry.length();i++)
    {
        if(ECGDateArry.at(i)<*min)
        {
            *min=ECGDateArry.at(i);
        }
    }
}







//page3
//创建用户
void MyECG::on_AddUserPushBt_clicked()
{
    AddUser *adduser=new AddUser;
    adduser->show();
}
//删除用户
void MyECG::on_DelateUserPushBt_clicked()
{
    DelateUser *delatuser=new DelateUser;
    delatuser->show();

}
//修改用户
void MyECG::on_ChangeUserPushBt_clicked()
{
    ModifyUser *modifyuser=new ModifyUser;
    modifyuser->show();
}
//查看用户
void MyECG::on_SeeUserPushBt_clicked()
{
    bool ok;
    QTextStream cout(stdout,  QIODevice::WriteOnly);
    QString text=QInputDialog::getText(this,tr("查看用户"),tr("请输入要查看的用户的ID号："),QLineEdit::Normal,IDLabel->text(),&ok);
    if(ok && !text.isEmpty())
    {
        cout<<"text is :"<<text<<endl;
        ShowUserInfo(text);
        ShowFileInfo(text);

    }

}

void MyECG::ShowUserInfo(QString UserID)
{

    QString FileRootDir="E:/my-qt-example/MyECG/MyECG/My_ECG _V1.3/User/";
    QString UserFilePath=FileRootDir+UserID+".txt";
    QFile UserInfoFile(UserFilePath);
    QTextStream in(&UserInfoFile);
    QTextStream cout(stdout,  QIODevice::WriteOnly);
    bool exit=UserInfoFile.exists();
    if(!exit)
    {
       QMessageBox::warning(this,tr("查看用户"),tr("您要查看的用户不存在，请确认用户ID是否输入正确！！！"));
    }
    else
    {
        ui->UserInfoTextBrowser->setText(tr("**********************User Info**********************\r\n"));
        if(UserInfoFile.open(QIODevice::ReadOnly))
        {

            while(!in.atEnd())
            {
               QString lineStr=in.readLine();
               lineStr.toStdString();
               ui->UserInfoTextBrowser->append(lineStr);
               cout<<"lineStr:"<<lineStr<<endl;
            }
            ui->UserInfoTextBrowser->append(tr("*************************END*************************\r\n"));

        }
        UserInfoFile.close();

    }
}

void MyECG::ShowFileInfo(QString UserID)
{
    QString FileRootDir="E:/my-qt-example/MyECG/MyECG/My_ECG _V1.3/User/";
    QString UserFilePath=FileRootDir+UserID+".txt";
    QFile UserInfoFile(UserFilePath);
    bool exit=UserInfoFile.exists();
    if(!exit)
    {
       QMessageBox::warning(this,tr("查看文件"),tr("您要查看的文件不存在，请确认用户ID是否输入正确！！！"));
    }
    else
    {
        QFileInfo info(UserFilePath);
        qint64 FileSize=info.size();
        QDateTime CreatTime=info.created();
        QDateTime LastModifiedTime=info.lastModified();
        QDateTime LastRead=info.lastRead();
        bool IsDir=info.isDir();
        bool IsFile=info.isFile();
        bool IsSymLink=info.isSymLink();
        bool IsHidden=info.isHidden();
        bool IsReadable=info.isReadable();
        bool IsWriteable=info.isWritable();
        bool IsExecuteable=info.isExecutable();
        ui->FileInfoTextBrowser->setText(tr("**********************File Info**********************\r\n"));
        ui->FileInfoTextBrowser->append(tr("文件名：")+UserFilePath+tr("\n"));
        ui->FileInfoTextBrowser->append(tr("文件大小：")+QString::number(FileSize)+tr(" 字节")+tr("\n"));
        ui->FileInfoTextBrowser->append(tr("创建时间：")+CreatTime.toString()+tr("\n"));
        ui->FileInfoTextBrowser->append(tr("最后修改时间：")+LastModifiedTime.toString()+tr("\n"));
        ui->FileInfoTextBrowser->append(tr("最后访问时间：")+LastRead.toString()+tr("\n"));
        QString str;
        QString str1;
        QString str2;
        QString str3;
        QString str4;
        QString str5;
        QString str6;
        if(IsDir)
        {
            str1="是一个目录，";
        }
        if(IsFile)
        {
            str1="是一个文件，";
            if(IsSymLink)
            {
                str2="拥有符号连接，";

            }
            else
            {
                str2="不拥有符号连接，";
            }
            if(IsHidden)
            {
                str3="本文件是一个影藏文件，";
            }
            else
            {
                str3="本文件不是一个影藏文件，";
            }
            if(IsReadable)
            {
                str4="本文件是一个可读文件，";
            }
            else
            {
                 str4="本文件不是一个可读文件，";
            }
            if(IsWriteable)
            {
                str5="本文件是一个可写文件，";
            }
            else
            {
                 str5="本文件不是一个可写文件，";
            }
            if(IsExecuteable)
            {
                str6="本文件是一个可执行文件.";
            }
            else
            {
                 str6="本文件不是一个可执行文件.";
            }

        }
        str=str1+str2+str3+str4+str5+str6;
        ui->FileInfoTextBrowser->append(tr("文件其他信息：")+str+tr("\n"));
        ui->FileInfoTextBrowser->append(tr("*************************END*************************\r\n"));
    }
}
