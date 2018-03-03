#ifndef MYECG_H
#define MYECG_H

#include <QWidget>
#include <QMenuBar>
#include <QMainWindow>
#include <QVector>
#include "win_qextserialport.h"
#include <qwt_plot_curve.h>
#include <qwt_plot_magnifier.h>
#include "qwt_plot_grid.h"
#include "qwt_plot_canvas.h"
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include <qwt_scale_draw.h>
#include <qwt_legend.h>
#include <qwt_plot.h>
#include <math.h>
#include <QTime>
#include <QTimer>
#include <QLabel>


#ifdef  PATH1_1
#define PATH1 "C:/Users/WFY/Desktop/ECGDate/ECG_1.txt"
#endif
#ifdef  PATH1_2
#define PATH1 "C:/Users/WFY/Desktop/ECGDate/ECG_2.txt"
#endif
#ifdef  PATH1_3
#define PATH1 "C:/Users/WFY/Desktop/ECGDate/ECG_3.txt"
#endif
#ifdef  PATH1_4
#define PATH1 "C:/Users/WFY/Desktop/ECGDate/ECG_4.txt"
#endif
#ifdef  PATH1_5
#define PATH1 "C:/Users/WFY/Desktop/ECGDate/ECG_5.txt"
#endif
#ifdef  PATH1_6
#define PATH1 "C:/Users/WFY/Desktop/ECGDate/ECG_6.txt"
#endif




namespace Ui {
class MyECG;
}

class MyECG : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyECG(QWidget *parent = 0);
    ~MyECG();

    QLabel *IDLabel;

    Win_QextSerialPort* myCom;
 //分别定义心电，用户和退出主菜单。
    QMenu* ECGMenu;
    QMenu* UserMenu;
    QMenu* ExitMenu;
//动作Action定义
    QAction* LeadConnectAction;
    QAction* ECGWatchAction;
    QAction* ECGPlayBackAction;

    QAction* UserManageAction;
    QAction* ChangePassWdAction;

    QAction* ExitAction;
    QAction* AboutAuthorAction;

//定义的三个曲线
    QwtPlotCurve *ECGWave1Plot;
    QwtPlotCurve *ECGWave2Plot;
    QwtPlotCurve *ECGWave3Plot;

    QwtPlotCurve *ECGWavePlot;
//定义私有的槽函数。
 private slots:
    void on_LeadConnect_clicked();
    void on_ECGWatch_clicked();
    void on_ECGPlayBack_clicked();

    void on_UserManage_clicked();
    void on_ChangePassWd_clicked();

    void on_Exit_clicked();
    void on_AboutAuthor_clicked();


    void on_ThreeLeadPushBt_clicked();

    void on_FiveLeadPushBt_clicked();

    void on_ClearPushBt_clicked();

    void on_AddUserPushBt_clicked();

    void on_OpenComPushBt_clicked();

    void on_CloseComPushBt_clicked();


    void on_StartPushBt_clicked();

    void on_PausePushBt_clicked();


private:
    Ui::MyECG *ui;

//page1
    QTimer UpdateTimer;
    int ECG[10];//存心电文件的数据
//计算后回头存放于xAixsData中
    double azhux;
//这三个是Y轴数据
    QVector< double > ECGWave1DateArry;   //存放1通道数据
    QVector< double > ECGWave2DateArry; //存放2通道数据
    QVector< double > ECGWave3DateArry;  //存放3通道数据

    QVector< double > ECGWave1Date;   //存放1通道数据
    QVector< double > ECGWave2Date; //存放2通道数据
    QVector< double > ECGWave3Date;  //存放3通道数据

    double FileDate1[3];
    double FileDate2[3];
    double FileDate3[3];


//这个是X轴的数据
    QVector< double > xAixs1Data;
    QVector< double > xAixs2Data;
    QVector< double > xAixs3Data;//存放X轴数据

//用于存放接收到三个通道的的心电数据
    double ECGDate1,ECGDate2,ECGDate3;

//用于存放接收到的温度的数据
    double TempDate;

//自定义的功能函数
    void creatMenuBar();//创建主菜单函数
    void serialInit();//串口部分初始化
    void readMyCom();//读串口的数据

    void ECGWavePlotInit();//画心电波形的初始化函数
    void PlotECGWave();//画心电波形函数

    void openfile();
    void showTemp();


    void ShowUserInfo(QString UserID);
    void ShowFileInfo(QString UserID);




//page2
      QTimer UpdateTimer1;
      double FileDate[3];
      QVector< double > ECGDateArry;
      QVector< double > ECGWaveDate;   //存放通道数据
      QVector< double > xAixsData1; //存放X轴数据
      void ECGWavePlotInit1();//画心电波形的初始化函数
      void StrToHex(QString str, double *fliedate);
      void Max_Min(QVector< double > ECGDateArry,double* max,double* min);



private slots:
    void UpdateDateSlot();
    void UpdateDateSlot1();


    void on_StartPushBt_1_clicked();
    void on_PausePushBt_1_clicked();
    void on_OpenFilePushBt_2_clicked();
    void on_DelateUserPushBt_clicked();
    void on_ChangeUserPushBt_clicked();
    void on_SeeUserPushBt_clicked();
};

#endif // MYECG_H
