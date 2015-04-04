#include "recvmes.h"
#include"MainWindow.h"
#include "mesxml.h"


RecvMes::RecvMes(QString filename):file(filename)
{

    mark=false;
    mainlayout= new QVBoxLayout(this);
    this->filename=filename;

    action_load=NULL;
}
RecvMes::~RecvMes()
{

    delete action_dele;
    delete action_reply;
    delete action_move;

    delete popmenu;
    delete mainlayout;

    if(action_load) delete action_load;
}
void RecvMes::createMes()
{
    create_menu();
    back.setText("返回");

    mainlayout->addWidget(&list);
    mainlayout->addWidget(&back);
/*
    list.setStyleSheet("QListWidget{font-size:15px}"
                       "QListWidget::item{color:#B452CD;border-bottom:2px solid #afafaf;border-color:#2292DD}"
                       "QListWidget{background-image:url(image/blue.png)}"

                       );*/

    update();

    //槽连接
    connect(&list,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(DetailMes()));
    connect(&back,SIGNAL(clicked()),this,SLOT(back_form()));


    this->setLayout(mainlayout);
}
void RecvMes::create_menu()
{

    QTextCodec *codec = QTextCodec::codecForName("gb2312");  //应为utf-8
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);

    popmenu= new QMenu(this);

    action_dele= new QAction("删除",this);
    action_reply= new QAction("回复",this);
    action_load = new QAction("导入",this);
    action_move=new QAction("移到垃圾箱",this);

    connect(action_dele,SIGNAL(triggered()),this,SLOT(dele()));
    connect(action_reply,SIGNAL(triggered()),this,SLOT(reply()));
    connect(action_move,SIGNAL(triggered()),this,SLOT(move()));
    connect(action_load,SIGNAL(triggered()),this,SLOT(load_mes()));

    popmenu->addAction(action_dele);
    popmenu->addAction(action_reply);
    popmenu->addAction(action_load);
    popmenu->addAction(action_move);

}
void RecvMes::contextMenuEvent(QContextMenuEvent * event)
{

    if(list.selectedItems().count() == 0)
    {
         return ;
    }
    popmenu->exec(QCursor::pos());

}

//*****************槽*****************

//导入信息
void RecvMes::load_mes()
{
    MesXML otherxml("../Test/TestSms.xml");
    MesXML xml("../Test/Mes.xml");
    MesXML blackxml("../Test/Rubbish.xml");

    QDomElement root=otherxml.GetRoot();
    QDomNodeList parentlist =root.childNodes();


    for(int i=0;i<parentlist.count();i++)
    {
        QDomNodeList childlist = parentlist.at(i).toElement().childNodes();

        if(xml.isblack_key())
        {

            blackxml.SetInfo(childlist.at(0).toElement().text(),
                             childlist.at(1).toElement().text());
            blackxml.addelement();
            blackxml.save();
        }
        else
        {
            xml.addelement();
            xml.save();
        }
    }
    update();
}
void RecvMes::update()
{
    if( !file.open(QFile::ReadOnly | QFile::Text) )
    {
        QMessageBox msgBox;
        msgBox.setText("open Mes false");
        msgBox.exec();
        return ;
    }

    dom.setContent(&file);
    root=dom.documentElement();

    domlist =root.childNodes();
    MyXml xml("../Test/Phone.xml");
    MyXml whitexml("../Test/BlackList.xml");

    QDomNodeList p_list=xml.find();
    QDomNodeList wp_list=whitexml.find();

    list.clear();
    for(int i=0;i<domlist.count();i++)
    {
        //匹配电话薄
        int j=0;
        for(;j<p_list.count();j++)
        {
            if(domlist.at(i).toElement().attributeNode("Number").value() ==
                    p_list.at(j).toElement().attributeNode("Num").value()
                    &&p_list.at(j).toElement().attributeNode("Name").value().length()>=1)
            {

                list.addItem("发件人: "+p_list.at(j).toElement().attributeNode("Name").value()+"\n");
                break;
            }
        }
        //匹配黑名单
        int m=0;
        for(;m<wp_list.count();m++)
        {
            //匹配电话薄
            if(domlist.at(i).toElement().attributeNode("Number").value() ==
                    wp_list.at(m).toElement().attributeNode("Num").value()
                    &&wp_list.at(m).toElement().attributeNode("Name").value().length()>=1)
            {

                list.addItem("发件人: "+wp_list.at(m).toElement().attributeNode("Name").value()+"\n");
                break;
            }
        }

        //如果电话薄里面没有显示电话号码
        if(j==p_list.count() && m==wp_list.count())
        {
             list.addItem("发件人: "+domlist.at(i).toElement().attributeNode("Number").value()+"\n");
        }
    }

    file.close();
}

//双击进入详细信息
void RecvMes::DetailMes()
{

    if(mark==true) return ;
    mark=true;

    //记录索引
    preindex=list.currentRow();
    childlist=domlist.at(list.currentRow()).childNodes();
    list.clear();
    for(int i=0;i<childlist.count();i++)
    {

        list.addItem("详情:\n"+childlist.at(i).toElement().text()+"\n");
    }

}
void RecvMes::back_form()
{
    if(mark==true){

        list.clear();
        update();
        mark=false;
    }
    else{

        QStackedWidget *stackw=MainWindow::GetStackedWidget();
        stackw->setCurrentWidget(MainWindow::GetPreviousForm());
    }
}

void RecvMes::dele()
{

    if( !file.open(QFile::WriteOnly | QIODevice::Truncate) )
    {
        QMessageBox msgBox;
        msgBox.setText("open Mes false");
        msgBox.exec();
        return ;
    }

    //如果是在发件人文件夹下 //删除此人所以的信息
    if(mark==false)
    {

        root.removeChild(domlist.at(list.currentRow()));

    }
    //否则删除此人某人莫条信息
    else
    {

        if(domlist.at(preindex).childNodes().count()==1) {

            root.removeChild(domlist.at(preindex));

            QTextStream out(&file);
            dom.save(out,4);
            file.close();

            back_form();
        }
        else{
            domlist.at(preindex).removeChild(childlist.at(list.currentRow()));
            QListWidgetItem *item=list.takeItem(list.currentRow());
            delete item;
        }
    }

    QTextStream out(&file);
    dom.save(out,4);

    file.close();

    if(mark==false)
    {
        update();
    }
}

//回复
void RecvMes::reply()
{

}
//黑白名单之间移动
void RecvMes::move()
{

    MesXML xml("../Test/rubbish.xml");

    if(mark == false)
    {

        QDomNodeList child =domlist.at(list.currentRow()).childNodes();

        for(int i=0;i<child.count();i++)
        {
            xml.SetInfo(domlist.at(list.currentRow()).toElement().attributeNode("Number").value(),
                child.at(i).toElement().text());
            xml.addelement();
            xml.save();
        }

        dele();

    }
    else
    {
       xml.SetInfo(domlist.at(preindex).toElement().attributeNode("Number").value(),
                   childlist.at(list.currentRow()).toElement().text());

       xml.addelement();
       xml.save();

       dele();
    }

}

//************************************
