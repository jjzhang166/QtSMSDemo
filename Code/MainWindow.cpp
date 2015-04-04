#include "MainWindow.h"


MainWindow::MainWindow():recvmes("../Test/Mes.xml")
{

    QTextCodec *codec = QTextCodec::codecForName("gb2312");  //ӦΪutf-8
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);

    listwidget = new QListWidget();

    mainLayout = new QHBoxLayout(this);
    stackedwidget = new QStackedWidget(this);

    //��������
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

//�л�����
void MainWindow::SwitchForm()
{

    SetPreviousForm(listwidget);
    stackedwidget->setCurrentWidget( stackedwidget->widget(listwidget->currentRow() +1));

}

//���ɴ�����������
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
    this->setWindowTitle("����");

    listwidget->addItem("������");
    listwidget->addItem("�ռ���");
    listwidget->addItem("������");
    listwidget->addItem("�绰��");
    listwidget->addItem("������");
    listwidget->addItem("����");

    //
    listwidget->setStyleSheet("QListWidget{font-size:28:px}");

    //�����еĴ�����ӵ�ջ����
    stackedwidget->addWidget(listwidget);  //0
    stackedwidget->addWidget(&sendmes);    //1
    stackedwidget->addWidget(&recvmes);    //2
    stackedwidget->addWidget(&rubbishmes); //3
    stackedwidget->addWidget(&phonebook);  //4
    stackedwidget->addWidget(&blacklist);  //5
    stackedwidget->addWidget(&set);    //6

    stackedwidget->addWidget(&manform);    //7


    //�����ˢ�����õ�
    connect(stackedwidget,SIGNAL(currentChanged(int)),this,SLOT(Update(int)));
    //�����л����ڲ�
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

//���ȡ�������ӣ���Ϊ�رմ��ڵ�ʱ������Update(int index)
void MainWindow::closeEvent(QCloseEvent *)
{

    disconnect(stackedwidget,SIGNAL(currentChanged(int)),this,SLOT(Update(int)));

}
void MainWindow::Update(int index){


    switch(index)
    {
        case 0:

            this->setWindowTitle("����");
            break;
        case 1:

            this->setWindowTitle("������");
            break;
        case 2:
            this->setWindowTitle("�ռ���");
            recvmes.update();
            break;
        case 3:
            this->setWindowTitle("������");
            rubbishmes.update();
            break;
        case 4:

            phonebook.update();
            this->setWindowTitle("�绰��");
            break;
        case 5:

            blacklist.update();
            this->setWindowTitle("������");
            break;
        case 6:
            this->setWindowTitle("����");
            break;
        case 7: break;
    }

}






