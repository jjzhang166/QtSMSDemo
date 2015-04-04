#include "MainWindow.h"


MainWindow::MainWindow():recvmes("../Test/Mes.xml")
{

    QTextCodec *codec = QTextCodec::codecForName("gb2312");  //应为utf-8
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);

    listwidget = new QListWidget();

    mainLayout = new QHBoxLayout(this);
    stackedwidget = new QStackedWidget(this);

    //设置主题
    this->setStyleSheet("QWidget{background-image:url(../Test/image/blue.png)}");

    this->resize(240,320);
}
QStackedWidget *MainWindow::stackedwidget=NULL;
QWidget *MainWindow::previous=NULL;
Udp     MainWindow::udp;

MainWindow::~MainWindow()
{

    delete listwidget;
    delete mainLayout;

}

//切换窗口
void MainWindow::SwitchForm()
{

    SetPreviousForm(listwidget);
    stackedwidget->setCurrentWidget( stackedwidget->widget(listwidget->currentRow() +1));

}

//生成窗体里面的组件
void MainWindow::FormWidget()
{

    blacklist.CreateMenu();
    blacklist.CreatePhoneBook();

    phonebook.CreateMenu();
    phonebook.CreatePhoneBook();


    manform.CreateForm();
    sendmes.CreateMes();
    recvmes.createMes();

    rubbishmes.createMes();

    udp.create();

    set.create();
}
void MainWindow::LoadForm()
{
    this->setWindowTitle("短信");

    listwidget->addItem("发件箱");
    listwidget->addItem("收件箱");
    listwidget->addItem("垃圾箱");
    listwidget->addItem("电话薄");
    listwidget->addItem("黑名单");
    listwidget->addItem("设置");

    //
    listwidget->setStyleSheet("QListWidget{font-size:28:px}");

    //将所有的窗体添加到栈里面
    stackedwidget->addWidget(listwidget);  //0
    stackedwidget->addWidget(&sendmes);    //1
    stackedwidget->addWidget(&recvmes);    //2
    stackedwidget->addWidget(&rubbishmes); //3
    stackedwidget->addWidget(&phonebook);  //4
    stackedwidget->addWidget(&blacklist);  //5
    stackedwidget->addWidget(&set);    //6

    stackedwidget->addWidget(&manform);    //7


    //用组件刷新所用的
    connect(stackedwidget,SIGNAL(currentChanged(int)),this,SLOT(Update(int)));
    //连接切换窗口槽
    connect(listwidget,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(SwitchForm()));

    mainLayout->addWidget(stackedwidget);

    this->setLayout(mainLayout);

}
QStackedWidget * MainWindow::GetStackedWidget()
{

    if(stackedwidget)
        return stackedwidget;
    else
        return NULL;
}
QWidget* MainWindow::GetPreviousForm()
{
    return previous;
}
void MainWindow::SetPreviousForm(QWidget *pre)
{
    previous=pre;

}

Udp* MainWindow::GetUdp()
{

    return &udp;
}

//最后取消槽连接，因为关闭窗口的时候会调用Update(int index)
void MainWindow::closeEvent(QCloseEvent *)
{

    disconnect(stackedwidget,SIGNAL(currentChanged(int)),this,SLOT(Update(int)));

}
void MainWindow::Update(int index){


    switch(index)
    {
        case 0:

            this->setWindowTitle("短信");
            break;
        case 1:

            this->setWindowTitle("发件箱");
            break;
        case 2:
            this->setWindowTitle("收件箱");
            recvmes.update();
            break;
        case 3:
            this->setWindowTitle("垃圾箱");
            rubbishmes.update();
            break;
        case 4:

            phonebook.update();
            this->setWindowTitle("电话薄");
            break;
        case 5:

            blacklist.update();
            this->setWindowTitle("黑名单");
            break;
        case 6:
            this->setWindowTitle("设置");
            break;
        case 7: break;
    }

}






