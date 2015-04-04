#include "sendmes.h"
#include "MainWindow.h"

SendMes::SendMes()
{
    mainlayout= new QVBoxLayout(this);
    hlayout = new QHBoxLayout();
    hlayout1 = new QHBoxLayout();

    //����༭��ֻ��Ϊ����
    QRegExp regx("[0-9]+$");
    validator = new QRegExpValidator(regx,&edit_num);
    edit_num.setValidator(validator);


    MyXml xml("../Test/install.xml");
    QDomNodeList node =xml.find();

    OwnPhoneNum=node.at(3).toElement().attributeNode("Num").value();

}
SendMes::~SendMes()
{

    delete validator;
    delete hlayout1;
    delete hlayout;
    delete mainlayout;

}
void SendMes::CreateMes()
{
   load.setText("����");
   back.setText("����");
   send.setText("����");

   hlayout->addWidget(&edit_num);
   hlayout->addWidget(&load);

   hlayout1->addWidget(&send);
   hlayout1->addWidget(&back);

   mainlayout->addLayout(hlayout);
   mainlayout->addWidget(&text);
   mainlayout->addLayout(hlayout1);

   connect(&load,SIGNAL(clicked()),this,SLOT(LoadNum()));
   connect(&back,SIGNAL(clicked()),this,SLOT(BackForm()));
   connect(&send,SIGNAL(clicked()),this,SLOT(SendMessage()));

   this->setLayout(mainlayout);

}
void SendMes::SetPhoneNum(QString num)
{
    edit_num.setText(num);

}
//******************��***********************
//���Ͷ���
void SendMes::SendMessage()
{

    //�������̫����������
    if(text.toPlainText().length()>512){

        QToolTip::showText(QCursor::pos(),"����̫��");
        return;
    }
    if(send.text().isEmpty() || text.toPlainText().isEmpty()){

        QToolTip::showText(QCursor::pos(),"�������Ϣ����Ϊ��");
        return ;
    }

    //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


    MainWindow::GetUdp()->send(text.toPlainText(),OwnPhoneNum);

    text.clear();
}

//������ϵ��
void SendMes::LoadNum()
{

    MainWindow::SetPreviousForm(this);

    //��ת���绰������
    QStackedWidget *stackw=MainWindow::GetStackedWidget();
    stackw->setCurrentWidget(stackw->widget(4));

}

void SendMes::BackForm()
{
    //��ת������
    QStackedWidget *stackw=MainWindow::GetStackedWidget();
    stackw->setCurrentWidget(stackw->widget(0));

}

//******************��***********************

