#ifndef BOOKFATHER_H
#define BOOKFATHER_H

#include"myxml.h"
#include<QtGui>

class BookFather:public QWidget
{
Q_OBJECT
public:

    BookFather(QString filename);
    ~BookFather();

    void CreatePhoneBook();

    //������ϵ��
    void LoadBook();

    //��д���෽��
    virtual void contextMenuEvent(QContextMenuEvent * event);

    //������һ������
    void SetPreviousForm(QWidget *pform);


    //�����ϵ��
    void AddLinkMan(QString num,QString name);
    void ModifMan(QString num,QString name);

    void update();
protected slots:
    void Back_form();
    void Add_Book();

    //�һ��˵���
    void Edit();
    void Dele();

//**************************************************8

protected:
    MyXml xml;

    //������
    QVBoxLayout *vlayout;
    QListWidget *list;

    //������
    QToolBar *toolbar;
    QAction  *action_add;
    QAction  *action_back;

    //�һ��˵���
    QMenu* popMenu;

    QAction  *action_edit;
    QAction  *action_delete;
    QAction  *action_black;

};

#endif // BOOKFATHER_H
