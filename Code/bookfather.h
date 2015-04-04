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

    //加载联系人
    void LoadBook();

    //重写父类方法
    virtual void contextMenuEvent(QContextMenuEvent * event);

    //设置上一个窗体
    void SetPreviousForm(QWidget *pform);


    //添加联系人
    void AddLinkMan(QString num,QString name);
    void ModifMan(QString num,QString name);

    void update();
protected slots:
    void Back_form();
    void Add_Book();

    //右击菜单栏
    void Edit();
    void Dele();

//**************************************************8

protected:
    MyXml xml;

    //主布局
    QVBoxLayout *vlayout;
    QListWidget *list;

    //工具栏
    QToolBar *toolbar;
    QAction  *action_add;
    QAction  *action_back;

    //右击菜单栏
    QMenu* popMenu;

    QAction  *action_edit;
    QAction  *action_delete;
    QAction  *action_black;

};

#endif // BOOKFATHER_H
