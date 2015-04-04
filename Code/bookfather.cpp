#include "bookfather.h"

#include "MainWindow.h"
#include "addmanform.h"
#include "sendmes.h"

BookFather::BookFather(QString filename):xml(filename)
{
    //ʵ����
    toolbar = new QToolBar(this);

    action_back =new QAction(QIcon("../Test/image/return.jpg")," ",this);
    action_add = new QAction(QIcon("../Test/image/add.jpg")," ",this);
    vlayout = new QVBoxLayout(this);
    list= new QListWidget;

}
BookFather::~BookFather()
{

    delete list;
    delete toolbar;
    delete action_add;
    delete action_back;

    delete  popMenu;

    delete action_edit;
    delete action_delete;
    delete action_black;

    delete   vlayout;

}
//������ϵ������
void BookFather::LoadBook()
{
    int i=0;

    QDomNodeList Domlist=xml.find();

    //������Ե��ڲ�item
    list->clear();

    while(i<Domlist.count())
    {
        QString str=Domlist.at(i).toElement().attributeNode("Name").value()+"\n"+
                    Domlist.at(i).toElement().attributeNode("Num").value();
        list->addItem(str);
        ++i;
    }

}

//���ɴ���
void BookFather::CreatePhoneBook()
{

    list->setSortingEnabled(false);
    LoadBook();

    //��
    connect(action_back,SIGNAL(triggered()),this,SLOT(Back_form()));
    connect(action_add,SIGNAL(triggered()),SLOT(Add_Book()));


    //���action��������
    toolbar->addAction(action_add);
    toolbar->addAction(action_back);

    vlayout->addWidget(toolbar);
    vlayout->addWidget(list);


    this->setLayout(vlayout);
}
//�޸���ϵ��
void BookFather::ModifMan(QString num,QString name)
{

    QDomNodeList Domlist=xml.find();
    QMessageBox msgBox;

    //���������Ͱ������Ƿ���ڴ���
    if(xml.isexist(num))
    {
        msgBox.setText("�ڻ��߰������Ѵ���");
        msgBox.exec();
        return ;
    }
    for(int i=0;i<Domlist.count();i++)
    {

        if(Domlist.at(i).toElement().attributeNode("Num").value()==num){

            msgBox.setText("�����Ѵ���");
            msgBox.exec();
            return ;
        }
    }

    xml.modif(list->currentRow(),num,name);
    //���¼�������
    LoadBook();

    xml.save();
}
//������ϵ��
void BookFather::AddLinkMan(QString num,QString name)
{
    QMessageBox msgBox;
    QDomNodeList Domlist=xml.find();

    if(xml.isexist(num))
    {

        msgBox.setText("�ڻ�������Ѵ���");
        msgBox.exec();
        return ;
    }

    for(int i=0;i<Domlist.count();i++)
    {

        if(Domlist.at(i).toElement().attributeNode("Num").value()==num){

            msgBox.setText("�����Ѵ���");
            msgBox.exec();
            return ;
        }
    }
    xml.addelement(num,name);

    msgBox.setText("��ӳɹ�");
    msgBox.exec();

    LoadBook();

    xml.save();
}
void BookFather::Dele()
{
    //ɾ��
    xml.dele(list->currentRow());

    QListWidgetItem *item = list->takeItem(list->currentRow());
    delete item;

    LoadBook();

    xml.save();
}
//*******************��**************************

//���ش���
void BookFather::Back_form()
{
    QStackedWidget *stackw=MainWindow::GetStackedWidget();

    if(MainWindow::GetPreviousForm() == stackw->widget(1))
    {


        stackw->setCurrentWidget(MainWindow::GetPreviousForm());

    }else{


        stackw->setCurrentWidget(stackw->widget(0));
    }

}
//�����ϵ��,��ת�������ϵ�˴���
void BookFather::Add_Book()
{

    MainWindow::SetPreviousForm(this);
    QStackedWidget *stackw=MainWindow::GetStackedWidget();

    stackw->setCurrentWidget(stackw->widget(7));
}
//�һ��˵���
void BookFather::contextMenuEvent(QContextMenuEvent * event)
{

   if(list->selectedItems().count() == 0)
        return ;

   popMenu->exec(QCursor::pos());

}


//�༭��ϵ��
void BookFather::Edit()
{

    MainWindow::SetPreviousForm(this);
    QStackedWidget *stackw=MainWindow::GetStackedWidget();

    stackw->setCurrentWidget(stackw->widget(7));

    AddManForm *add=(AddManForm *)stackw->widget(7);

    QStringList strlist = list->currentItem()->text().split("\n");

    add->SwitchButton(strlist.at(0),strlist.at(1));
}
//����
void BookFather::update()
{

    xml.openfile();
    LoadBook();
}
