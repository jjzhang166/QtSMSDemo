#ifndef BLACKLIST_H
#define BLACKLIST_H

#include"bookfather.h"

class BlackList:public BookFather
{
Q_OBJECT
public:
    BlackList();
    ~BlackList();

    void CreateMenu();

private slots:
    void move();

};

#endif // BLACKLIST_H
