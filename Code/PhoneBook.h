#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include"bookfather.h"


class PhoneBook:public BookFather
{

Q_OBJECT

public:

    PhoneBook();
    ~PhoneBook();
    //创建右击菜单
    void CreateMenu();

private slots:
    //黑白名单移动
    void move();
    //传递信息
    void transmit();

};

#endif

