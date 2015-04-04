#include "rubbishmes.h"
#include"myxml.h"
#include "mesxml.h"

RubbishMes::RubbishMes():RecvMes("../Test/rubbish.xml")
{


}

void RubbishMes::create_menu()
{
    QTextCodec *codec = QTextCodec::codecForName("gb2312");  //ӦΪutf-8
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);

    popmenu= new QMenu(this);

    action_dele= new QAction("ɾ��",this);
    action_reply= new QAction("�ظ�",this);
    action_move=new QAction("�Ƶ��ռ���",this);

    connect(action_dele,SIGNAL(triggered()),this,SLOT(dele()));
    connect(action_reply,SIGNAL(triggered()),this,SLOT(reply()));
    connect(action_move,SIGNAL(triggered()),this,SLOT(move()));

    popmenu->addAction(action_dele);
    popmenu->addAction(action_reply);
    popmenu->addAction(action_move);

}

//************************��*************************************

void RubbishMes::move()
{

    MesXML xml("../Test/Mes.xml");

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


