#ifndef UDP_H
#define UDP_H

#include<QtNetwork/QUdpSocket>


class Udp:public QObject
{

Q_OBJECT
public:
    Udp();

    //�󶨶˿�1573
    void create();
    //����
    void send(QString text,QString Phone_num);

private slots:
    void recv();

private:
    QUdpSocket udp;

};

#endif // UDP_H
