#ifndef RUBBISHMES_H
#define RUBBISHMES_H

#include "recvmes.h"

class RubbishMes:public RecvMes
{

Q_OBJECT

public:
    RubbishMes();

    void create_menu();

private slots:
    void move();

};

#endif // RUBBISHMES_H
