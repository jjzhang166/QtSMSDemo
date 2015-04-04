#include "bookfather.h"

#include "MainWindow.h"
#include "addmanform.h"
#include "sendmes.h"

BookFather::BookFather(QString filename):xml(filename)
{
    //实例化
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
//加载联系人名单
void BookFather::LoadBook()
{
    int i=0;

    QDomNodeList Domlist=xml.find();

    //清除所以的内部item
    list->clear();

    while(i<Domlist.count())
    {
        QString str=Domlist.at(i).toElement().attributeNode("Name").value()+"\n"+
                    Domlist.at(i).toElement().attributeNode("Num").value();
        list->addItem(str);
        ++i;
    }

}

//生成窗体
void BookFather::CreatePhoneBook()
{

    list->setSortingEnabled(false);
    LoadBook();

    //槽
    connect(action_back,SIGNAL(triggered()),this,SLOT(Back_form()));
    connect(action_add,SIGNAL(triggered()),SLOT(Add_Book()));


    //添加action到工具栏
    toolbar->addAction(action_add);
    toolbar->addAction(action_back);

    vlayout->addWidget(toolbar);
    vlayout->addWidget(list);


    this->setLayout(vlayout);
}
//修改联系人
void BookFather::ModifMan(QString num,QString name)
{

    QDomNodeList Domlist=xml.find();
    QMessageBox msgBox;

    //检测黑名单和白名单是否存在此人
    if(xml.isexist(num))
    {
        msgBox.setText("黑或者白名单已存在");
        msgBox.exec();
        return ;
    }
    for(int i=0;i<Domlist.count();i++)
    {

        if(Domlist.at(i).toElement().attributeNode("Num").value()==num){

            msgBox.setText("号码已存在");
            msgBox.exec();
            return ;
        }
    }

    xml.modif(list->currentRow(),num,name);
    //重新加载名单
    LoadBook();

    xml.save();
}
//增加联系人
void BookFather::AddLinkMan(QString num,QString name)
{
    QMessageBox msgBox;
    QDomNodeList Domlist=xml.find();

    if(xml.isexist(num))
    {

        msgBox.setText("黑或白名单已存在");
        msgBox.exec();
        return ;
    }

    for(int i=0;i<Domlist.count();i++)
    {

        if(Domlist.at(i).toElement().attributeNode("Num").value()==num){

            msgBox.setText("号码已存在");
            msgBox.exec();
            return ;
        }
    }
    xml.addelement(num,name);

    msgBox.setText("添加成功");
    msgBox.exec();

    LoadBook();

    xml.save();
}
void BookFather::Dele()
{
    //删除
    xml.dele(list->currentRow());

    QListWidgetItem *item = list->takeItem(list->currentRow());
    delete item;

    LoadBook();

    xml.save();
}
//*******************槽**************************

//返回窗体
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
//添加联系人,跳转到添加联系人窗口
void BookFather::Add_Book()
{

    MainWindow::SetPreviousForm(this);
    QStackedWidget *stackw=MainWindow::GetStackedWidget();

    stackw->setCurrentWidget(stackw->widget(7));
}
//右击菜单栏
void BookFather::contextMenuEvent(QContextMenuEvent * event)
{

   if(list->selectedItems().count() == 0)
        return ;

   popMenu->exec(QCursor::pos());

}


//编辑联系人
void BookFather::Edit()
{

    MainWindow::SetPreviousForm(this);
    QStackedWidget *stackw=MainWindow::GetStackedWidget();

    stackw->setCurrentWidget(stackw->widget(7));

    AddManForm *add=(AddManForm *)stackw->widget(7);

    QStringList strlist = list->currentItem()->text().split("\n");

    add->SwitchButton(strlist.at(0),strlist.at(1));
}
//更新
void BookFather::update()
{

    xml.openfile();
    LoadBook();
}
