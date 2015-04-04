#include "udp.h"

#include<QtCore>
#include <QIODevice>

#include"mesxml.h"

Udp::Udp()
{

}
void Udp::create()
{

    udp.bind(QHostAddress::LocalHost,1573);
    connect(&udp,SIGNAL(readyRead()),this,SLOT(recv()));

}

void Udp::send(QString text,QString Phone_num)
{

    QDomDocument dom;
    QDomElement root=dom.createElement("Sms");

    QDomElement num = dom.createElement("Number");
    QDomElement con = dom.createElement("content");

    QDomText    text_num=dom.createTextNode(Phone_num);
    QDomText    text_cont=dom.createTextNode(text);

    num.appendChild(text_num);
    con.appendChild(text_cont);

    root.appendChild(num);
    root.appendChild(con);

    dom.appendChild(root);

    QByteArray arry=dom.toByteArray();
    udp.writeDatagram(arry.data(),arry.size(),QHostAddress::LocalHost,1573);

}

//*******************槽****************
void Udp::recv()
{
    char buffer[2048]={0};
    udp.readDatagram(buffer,2048,0,0);
    QMessageBox msgBox;
    QDomDocument dom;
    QByteArray arry;

    arry.append(buffer);
    dom.setContent(arry);

    QDomElement root=dom.documentElement();
    QDomNodeList list=root.childNodes();

    //如果不是XML字节流的形式不
    if(root.isNull()) return ;
    //****************判断加入垃圾箱还是加入短信箱*********************
    MesXML mes("../Test/Mes.xml");
    MesXML blackmes("../Test/rubbish.xml");

    mes.isrootempty();
    blackmes.isrootempty();

    mes.SetInfo(list.at(0).toElement().text(),list.at(1).toElement().text());
    //过滤
    if(mes.isblack_key())
    {

        blackmes.SetInfo(list.at(0).toElement().text(),list.at(1).toElement().text());
        blackmes.addelement();
        blackmes.save();

        msgBox.setWindowTitle("收到垃圾信息");

    }
    else
    {
        mes.SetInfo(list.at(0).toElement().text(),list.at(1).toElement().text());
        mes.addelement();
        mes.save();

        msgBox.setWindowTitle("短消息");

    }

    msgBox.setText(list.at(0).toElement().text()+"\n"+"信息详情：\n"+
                   list.at(1).toElement().text());
    msgBox.exec();
}

//******************槽*****************


