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

    //װ�ش���
    void LoadForm();
    void FormWidget();

    //������һ������
    static void SetPreviousForm(QWidget*);
    static QWidget* GetPreviousForm();

    //����QStackedWidgetָ�룬
    static QStackedWidget* GetStackedWidget();
    static Udp* GetUdp();

private slots:
    //�л����壨���棩����
    void SwitchForm();

    //�˲ۺ�������ˢ�����еĴ��壬�Լ���ʾ���ڱ���
    void Update(int index);
private:
    //���еĴ��壨���ǲ�ͬ�Ĺ��ܽ��棩
    PhoneBook  phonebook; //1
    AddManForm manform;   //2
    SendMes    sendmes;    //3
    BlackList  blacklist;
    Setting    set;
    RecvMes    recvmes;
    RubbishMes rubbishmes;


    static QWidget   *previous;

    //�������е�ʱ������UDP
    static Udp       udp;
private:
    //����,�����

    QListWidget    *listwidget;
    static QStackedWidget *stackedwidget;
    QHBoxLayout    *mainLayout;

};



#endif

