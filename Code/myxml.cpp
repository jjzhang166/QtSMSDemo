#include "myxml.h"

#include <QtCore/QIODevice>
#include <QMessageBox>

MyXml::MyXml(QString filename):file(filename)
{

    this->filename=filename;

    if( !file.open(QFile::ReadOnly | QFile::Text) )
    {
        QMessageBox msgBox;
        msgBox.setText("init open "+filename+" false");
        msgBox.exec();
        return;
    }

    dom.setContent(&this->file);
    root=dom.documentElement();

    file.close();
}

MyXml::~MyXml()
{

    file.close();
}

void MyXml::openfile()
{
    if( !file.open(QFile::ReadOnly | QFile::Text) )
    {
        QMessageBox msgBox;
        msgBox.setText("open "+filename+" false");
        msgBox.exec();
        return;
    }

    dom.setContent(&this->file);
    root=dom.documentElement();

    file.close();
}
//�����ӽڵ��б�
QDomNodeList& MyXml::find()
{

    list=root.childNodes();
    return list;

}
//���ظ��ڵ�
QDomElement&  MyXml::GetRoot()
{
    return root;
}

//����
void MyXml::save()
{
    QFile swap(filename);
    if( !swap.open(QFile::WriteOnly | QIODevice::Truncate) )
    {
        QMessageBox msgBox;
        msgBox.setText("open "+filename+" false");
        msgBox.exec();
        return;
    }

    dom.appendChild(root);

    QTextStream out(&swap);
    dom.save(out,4);

    swap.close();

}

void MyXml::dele(int index)
{

    root.removeChild(list.at(index));

}

void MyXml::modif(int index,QString Num,QString Name)
{

    find();
    QDomElement e=dom.createElement("Man");
        e.setAttribute("Num",Num);
        e.setAttribute("Name",Name);

    root.replaceChild(e,list.at(index));
}

void MyXml::addelement(QString Num,QString Name)
{
    isrootempty();
    QDomElement firstchid=root.firstChildElement();

    QDomElement newchild=dom.createElement("Man");
        newchild.setAttribute("Num",Num);
        newchild.setAttribute("Name",Name);

    root.insertBefore(newchild,firstchid);

}
//�жϸ��ڵ��Ƿ�Ϊ�գ����Ϊ���򴴽�
bool MyXml::isrootempty()
{

    if(root.isNull())
    {
         root = dom.createElement("PhoneBook");
         dom.appendChild(root);

         root=dom.documentElement();
         return true;
    }

    return false;
}
//����������Ƿ����
bool MyXml::isexist(QString phonenum)
{

    QString str;
    if(filename == "../Test/BlackList.xml") str="../Test/Phone.xml";
    else str="../Test/BlackList.xml";

    QFile swap(str);
    if( !swap.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox msgBox;
        msgBox.setText("open false");
        msgBox.exec();

    }
    QDomDocument doc;
    QDomElement  r;

    doc.setContent(&swap);
    r=doc.documentElement();

    QDomNodeList nodelist =r.childNodes();


    for(int i=0;i<nodelist.count();i++)
    {

        if(nodelist.at(i).toElement().attributeNode("Num").value() == phonenum)
            return true;

    }
    swap.close();

    return false;
}
