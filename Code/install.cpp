#include "install.h"
#include"MainWindow.h"

Setting::Setting()
{
}
Setting::~Setting()
{

    delete layout_button;
    delete layout_num;
    delete layout_name;
    delete mainlayout;

}
//���ɴ���
void Setting::create()
{

    save.setText("����");
    back.setText("����");

    line_num.setText("���˺���");
    line_name.setText("��������");

    ckeckbox_filter.setText("���ù���");
    checkbox_black.setText("���ú�����");
    checkbox_white.setText("���ð�����");

    mainlayout = new QVBoxLayout();
    layout_num = new QHBoxLayout();
    layout_name = new QHBoxLayout();
    layout_button = new QHBoxLayout();

    layout_name->addWidget(&line_name);
    layout_name->addWidget(&name);

    layout_num->addWidget(&line_num);
    layout_num->addWidget(&phonenum);

    mainlayout->addLayout(layout_num);
    mainlayout->addLayout(layout_name);

    mainlayout->addWidget(&ckeckbox_filter);
    mainlayout->addWidget(&checkbox_black);
    mainlayout->addWidget(&checkbox_white);

    layout_button->addWidget(&save);
    layout_button->addWidget(&back);
    mainlayout->addLayout(layout_button);

    connect(&back,SIGNAL(clicked()),this,SLOT(back_form()));
    connect(&save,SIGNAL(clicked()),this,SLOT(save_info()));

    MyXml xml("../Test/install.xml");

    QDomNodeList node =xml.find();


    phonenum.setText(node.at(3).toElement().attributeNode("Num").value());
    name.setText(node.at(3).toElement().attributeNode("Name").value());

    if(node.at(2).toElement().attributeNode("Num").value() =="true")
    {
        ckeckbox_filter.setChecked(true);
    }

    if(node.at(1).toElement().attributeNode("Num").value() =="true")
    {
        checkbox_black.setChecked(true);
    }
    if(node.at(0).toElement().attributeNode("Num").value() =="true")
    {
        checkbox_white.setChecked(true);
    }

    connect(&checkbox_white,SIGNAL(clicked()),this,SLOT(check_click_white()));
    connect(&checkbox_black,SIGNAL(clicked()),this,SLOT(check_click_black()));

    this->setLayout(mainlayout);
}

//**************��******************************************
void Setting::back_form()
{

    QStackedWidget *stackw=MainWindow::GetStackedWidget();
    stackw->setCurrentWidget(stackw->widget(0));
}
//����������Ϣ
void Setting::save_info()
{

    QString filter_str="false";
    QString black_str="false";
    QString white_str="false";

    MyXml xml("../Test/install.xml");
    xml.isrootempty();

    if(ckeckbox_filter.checkState())
    {
        filter_str="true";
    }
    if(checkbox_black.checkState())
    {
        black_str="true";
    }
    if(checkbox_white.checkState())
    {
        white_str="true";
    }

    QDomElement  root =xml.GetRoot();
    if(root.firstChildElement().isNull())
    {
        xml.addelement(phonenum.text(),name.text());

        xml.addelement(filter_str,"filter");
        xml.addelement(black_str,"black");
        xml.addelement(white_str,"white");
    }

    else
    {

        xml.modif(0,white_str,"white");
        xml.modif(1,black_str,"black");
        xml.modif(2,filter_str,"filter");
        xml.modif(3,phonenum.text(),name.text());
    }

    xml.save();
}

void Setting::check_click_black()
{

    if(checkbox_white.checkState())
    {
        checkbox_black.setChecked(false);
    }
}
void Setting::check_click_white()
{
    if(checkbox_black.checkState())
    {
        checkbox_white.setChecked(false);
    }
}
