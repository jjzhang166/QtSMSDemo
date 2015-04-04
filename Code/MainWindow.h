#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include"PhoneBook.h"
#include "addmanform.h"
#include "sendmes.h"
#include "udp.h"
#include "rubbishmes.h"
#include "recvmes.h"
#include "install.h"
#include "blacklist.h"


class MainWindow:public QWidget
{

Q_OBJECT

public:

    MainWindow();
    ~MainWindow();

    void closeEvent(QCloseEvent *);

    //装载窗体
    void LoadForm();
    void FormWidget();

    //设置上一个窗体
    static void SetPreviousForm(QWidget*);
    static QWidget* GetPreviousForm();

    //返回QStackedWidget指针，
    static QStackedWidget* GetStackedWidget();
    static Udp* GetUdp();

private slots:
    //切换窗体（界面）函数
    void SwitchForm();

    //此槽函数用来刷新所有的窗体，以及显示窗口标题
    void Update(int index);
private:
    //所有的窗体（就是不同的功能界面）
    PhoneBook  phonebook; //1
    AddManForm manform;   //2
    SendMes    sendmes;    //3
    BlackList  blacklist;
    Setting    set;
    RecvMes    recvmes;
    RubbishMes rubbishmes;


    static QWidget   *previous;

    //程序运行的时候启动UDP
    static Udp       udp;
private:
    //布局,组件等

    QListWidget    *listwidget;
    static QStackedWidget *stackedwidget;
    QHBoxLayout    *mainLayout;

};



#endif

