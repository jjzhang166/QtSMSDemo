#ifndef UDP_H
#define UDP_H

#include<QtNetwork/QUdpSocket>


class Udp:public QObject
{

Q_OBJECT
public:
    Udp();

    //°ó¶¨¶Ë¿Ú1573
    void create();
    //·¢ËÍ
    void send(QString text,QString Phone_num);

private slots:
    void recv();

private:
    QUdpSocket udp;

};

#endif // UDP_H
