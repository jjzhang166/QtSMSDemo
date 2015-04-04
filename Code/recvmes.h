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
    //菜单的槽
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



    //根节点孩子的孩子
    QDomNodeList childlist;

    //根节点的孩子
    QDomNodeList domlist;
    QDomDocument dom;
    //根节点
    QDomElement root;

    //布局
    QVBoxLayout  *mainlayout;

    QString     filename;


    QFile       file;
    QPushButton back;
    QListWidget list;


    //标记
    bool mark;
    //右击菜单栏
    QMenu       *popmenu;

    QAction     *action_dele;
    QAction     *action_reply;
    QAction     *action_move;

    QAction     *action_load;
};

#endif // RECVMES_H
