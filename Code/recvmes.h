#ifndef RECVMES_H
#define RECVMES_H

#include<QtXml/QDomElement>
#include<QtXml/QDomDocument>
#include <QIODevice>

#include<QtGui>

#include"mesxml.h"
class RecvMes:public QWidget
{

Q_OBJECT
public:
    RecvMes(QString filename);
    ~RecvMes();
    void createMes();

    void contextMenuEvent(QContextMenuEvent * event);
    virtual void create_menu();

protected slots:

    virtual void move();
    //�˵��Ĳ�
    void dele();
    void reply();

public slots:
    void update();
private slots:

    virtual void DetailMes();
    void back_form();
    void load_mes();
protected:

    int  preindex;



    //���ڵ㺢�ӵĺ���
    QDomNodeList childlist;

    //���ڵ�ĺ���
    QDomNodeList domlist;
    QDomDocument dom;
    //���ڵ�
    QDomElement root;

    //����
    QVBoxLayout  *mainlayout;

    QString     filename;


    QFile       file;
    QPushButton back;
    QListWidget list;


    //���
    bool mark;
    //�һ��˵���
    QMenu       *popmenu;

    QAction     *action_dele;
    QAction     *action_reply;
    QAction     *action_move;

    QAction     *action_load;
};

#endif // RECVMES_H
