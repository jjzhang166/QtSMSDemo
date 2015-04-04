#ifndef MYXML_H
#define MYXML_H


#include<QtCore>
#include<QtXml/QDomElement>
#include<QtXml/QDomDocument>

#include <QIODevice>


class MyXml
{

public:
    MyXml(QString filename);
    ~MyXml();

    //判断有没有根节点
    bool isrootempty();
    //判断互斥文件是否存在
    bool isexist(QString phonenum);

    //重新打开文件
    void openfile();

    QDomElement& GetRoot();

    //以下是增删查改
    void addelement(QString Num,QString Name);
    void dele(int index);
    QDomNodeList& find();
    void modif(int index,QString Num,QString Name);

    void save();
private:

    QFile   file;

    QString filename;
    QDomDocument dom;

    //根节点
    QDomElement  root;
    QDomNodeList list;

};

#endif // MYXML_H
