#ifndef MESXML_H
#define MESXML_H

#include<QtGui/QMessageBox>
#include<QtXml/QDomElement>
#include<QtXml/QDomDocument>
#include<QtCore>

class MesXML
{
public:
    MesXML();
    MesXML(QString filename);

    void save();

    QDomElement& GetRoot();

    //�ж��Ƿ���ڸ��ڵ㣬��������ڴ������ڵ�
    bool isrootempty();
    //�ж��Ƿ���������
    bool isblack_key();


    //���ӽڵ���Ϣ
    void addelement();
    void deleelement();

    void SetInfo(QString num,QString text);
private:

    QDomElement root;
    QDomDocument dom;

    QFile   file;
    QString filename;

    QString Phonenum;
    QString info;
};

#endif // MESXML_H
