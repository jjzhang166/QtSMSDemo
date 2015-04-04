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

    //�ж���û�и��ڵ�
    bool isrootempty();
    //�жϻ����ļ��Ƿ����
    bool isexist(QString phonenum);

    //���´��ļ�
    void openfile();

    QDomElement& GetRoot();

    //��������ɾ���
    void addelement(QString Num,QString Name);
    void dele(int index);
    QDomNodeList& find();
    void modif(int index,QString Num,QString Name);

    void save();
private:

    QFile   file;

    QString filename;
    QDomDocument dom;

    //���ڵ�
    QDomElement  root;
    QDomNodeList list;

};

#endif // MYXML_H
