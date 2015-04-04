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
    back.setText("����");

    mainlayout->addWidget(&list);
    mainlayout->addWidget(&back);
/*
    list.setStyleSheet("QListWidget{font-size:15px}"
                       "QListWidget::item{color:#B452CD;border-bottom:2px solid #afafaf;border-color:#2292DD}"
                       "QListWidget{background-image:url(image/blue.png)}"

                       );*/

    update();

    //������
    connect(&list,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(DetailMes()));
    connect(&back,SIGNAL(clicked()),this,SLOT(back_form()));


    this->setLayout(mainlayout);
}
void RecvMes::create_menu()
{

    QTextCodec *codec = QTextCodec::codecForName("gb2312");  //ӦΪutf-8
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);

    popmenu= new QMenu(this);

    action_dele= new QAction("ɾ��",this);
    action_reply= new QAction("�ظ�",this);
    action_load = new QAction("����",this);
    action_move=new QAction("�Ƶ�������",this);

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

//*****************��*****************

//������Ϣ
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
        //ƥ��绰��
        int j=0;
        for(;j<p_list.count();j++)
        {
            if(domlist.at(i).toElement().attributeNode("Number").value() ==
                    p_list.at(j).toElement().attributeNode("Num").value()
                    &&p_list.at(j).toElement().attributeNode("Name").value().length()>=1)
            {

                list.addItem("������: "+p_list.at(j).toElement().attributeNode("Name").value()+"\n");
                break;
            }
        }
        //ƥ�������
        int m=0;
        for(;m<wp_list.count();m++)
        {
            //ƥ��绰��
            if(domlist.at(i).toElement().attributeNode("Number").value() ==
                    wp_list.at(m).toElement().attributeNode("Num").value()
                    &&wp_list.at(m).toElement().attributeNode("Name").value().length()>=1)
            {

                list.addItem("������: "+wp_list.at(m).toElement().attributeNode("Name").value()+"\n");
                break;
            }
        }

        //����绰������û����ʾ�绰����
        if(j==p_list.count() && m==wp_list.count())
        {
             list.addItem("������: "+domlist.at(i).toElement().attributeNode("Number").value()+"\n");
        }
    }

    file.close();
}

//˫��������ϸ��Ϣ
void RecvMes::DetailMes()
{

    if(mark==true) return ;
    mark=true;

    //��¼����
    preindex=list.currentRow();
    childlist=domlist.at(list.currentRow()).childNodes();
    list.clear();
    for(int i=0;i<childlist.count();i++)
    {

        list.addItem("����:\n"+childlist.at(i).toElement().text()+"\n");
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

    //������ڷ������ļ����� //ɾ���������Ե���Ϣ
    if(mark==false)
    {

        root.removeChild(domlist.at(list.currentRow()));

    }
    //����ɾ������ĳ��Ī����Ϣ
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

//�ظ�
void RecvMes::reply()
{

}
//�ڰ�����֮���ƶ�
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
