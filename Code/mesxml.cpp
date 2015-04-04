#include "mesxml.h"

#include"myxml.h"

MesXML::MesXML()
{

}

MesXML::MesXML(QString filename):file(filename)
{
    this->filename=filename;

    if( !file.open(QFile::ReadOnly | QFile::Text) )
    {
        QMessageBox msgBox;
        msgBox.setText("open "+filename+" false");
        msgBox.exec();
    }

    dom.setContent(&file);
    root=dom.documentElement();

    file.close();
}

void MesXML::save()
{
    QFile swap(this->filename);

    if( !swap.open(QFile::WriteOnly | QIODevice::Truncate) )
    {
        QMessageBox msgBox;
        msgBox.setText("open "+filename+" false");
        msgBox.exec();
        return;
    }

    QTextStream out(&swap);
    dom.save(out,4);

    swap.close();
}

//判断是否存在根节点，如果不存在创建根节点
bool MesXML::isrootempty()
{
    if(root.isNull())
    {
         root = dom.createElement("Sms");
         dom.appendChild(root);

         root=dom.documentElement();
         return true;
    }

    return false;
}
QDomElement& MesXML::GetRoot()
{

    return root;
}

void MesXML::addelement()
{

    int i=0;
    QDomNodeList list =root.childNodes();


    //判断是否存在此人信息如果存在则插入此人号码中
    for(i=0;i<list.count();i++)
    {

        if(list.at(i).toElement().attributeNode("Number").value() == Phonenum)
        {
            QDomElement firstchild=list.at(i).firstChildElement();

            QDomElement newchild =dom.createElement("Content");
            QDomText    newchildtext=dom.createTextNode(info);

            newchild.appendChild(newchildtext);
            list.at(i).insertBefore(newchild,firstchild);

            break;
        }
    }

    //不存在的存在就在重新创建一个孩子节点
    if(i==list.count())
    {

        QDomElement e = dom.createElement("Man");

        QDomElement s =dom.createElement("Content");
        QDomText    t=dom.createTextNode(info);
        s.appendChild(t);

        e.setAttribute("Number",Phonenum);

        e.appendChild(s);

        root.appendChild(e);

    }

    dom.appendChild(root);

}

bool MesXML::isblack_key()
{

    //是否需要过滤
    MyXml xml("../Test/install.xml");
    QDomNodeList node =xml.find();

    //检测关键字
    if(node.at(2).toElement().attributeNode("Num").value() =="true"){


        QFile file("../Test/key.txt");

        if( !file.open(QFile::ReadOnly | QFile::Text) )
        {
            QMessageBox msgBox;
            msgBox.setText("open false");
            msgBox.exec();
        }

        QString str=file.readLine();
        QStringList strlist=str.split(",");

        for(int i=0;i<strlist.count();i++){

            if(info.contains(strlist.at(i)) )
            {
                file.close();
                return true;
            }
        }

        file.close();
    }

    //检测黑名单是否开启
    if(node.at(1).toElement().attributeNode("Num").value() =="true")
    {

        MyXml black_xml("../Test/blacklist.xml");
        QDomNodeList nodelist =black_xml.find();

        for(int j=0;j<nodelist.count();j++)
        {
            if(nodelist.at(j).toElement().attributeNode("Num").value() ==Phonenum)
            {

                return true;
            }
        }
    }
    //检测白名单是否开启
    if(node.at(0).toElement().attributeNode("Num").value() =="true")
    {
        MyXml white_xml("../Test/Phone.xml");
        QDomNodeList nodelist =white_xml.find();

        for(int j=0;j<nodelist.count();j++)
        {
            if(nodelist.at(j).toElement().attributeNode("Num").value() ==Phonenum)
            {

                return false;
            }
        }

        return true;
    }
    return false;
}
void MesXML::SetInfo(QString num, QString text)
{
    Phonenum=num;
    info=text;

}
