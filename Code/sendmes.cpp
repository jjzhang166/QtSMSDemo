#include "sendmes.h"
#include "MainWindow.h"

SendMes::SendMes()
{
    mainlayout= new QVBoxLayout(this);
    hlayout = new QHBoxLayout();
    hlayout1 = new QHBoxLayout();

    //号码编辑框只能为数字
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
   load.setText("导入");
   back.setText("返回");
   send.setText("发送");

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
//******************槽***********************
//发送短信
void SendMes::SendMessage()
{

    //如果长度太长，不发送
    if(text.toPlainText().length()>512){

        QToolTip::showText(QCursor::pos(),"短信太长");
        return;
    }
    if(send.text().isEmpty() || text.toPlainText().isEmpty()){

        QToolTip::showText(QCursor::pos(),"号码或信息不能为空");
        return ;
    }

    //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


    MainWindow::GetUdp()->send(text.toPlainText(),OwnPhoneNum);

    text.clear();
}

//导入联系人
void SendMes::LoadNum()
{

    MainWindow::SetPreviousForm(this);

    //跳转到电话薄窗体
    QStackedWidget *stackw=MainWindow::GetStackedWidget();
    stackw->setCurrentWidget(stackw->widget(4));

}

void SendMes::BackForm()
{
    //跳转主界面
    QStackedWidget *stackw=MainWindow::GetStackedWidget();
    stackw->setCurrentWidget(stackw->widget(0));

}

//******************槽***********************

