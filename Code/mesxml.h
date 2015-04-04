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

    //判断是否存在根节点，如果不存在创建根节点
    bool isrootempty();
    //判断是否加入黑名单
    bool isblack_key();


    //增加节点信息
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
