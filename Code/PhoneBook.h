#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include"bookfather.h"


class PhoneBook:public BookFather
{

Q_OBJECT

public:

    PhoneBook();
    ~PhoneBook();
    //�����һ��˵�
    void CreateMenu();

private slots:
    //�ڰ������ƶ�
    void move();
    //������Ϣ
    void transmit();

};

#endif

