#ifndef SENDMES_H
#define SENDMES_H


#include<QtGui>
#include<QtNetwork/QUdpSocket>

class SendMes:public QWidget
{

Q_OBJECT

public:
    SendMes();
    ~SendMes();

    void CreateMes();
    void SetPhoneNum(QString num);
private slots:

    void SendMessage();
    void LoadNum();
    void BackForm();
private:

    //��������
    QString OwnPhoneNum;
    //����
    QVBoxLayout *mainlayout;
    QHBoxLayout *hlayout;
    QHBoxLayout *hlayout1;

    QPushButton back;
    QPushButton send;
    QPushButton load;

    QLineEdit edit_num;
    QTextEdit text;

    //���ú���༭��ֻ��Ϊ����
    QValidator *validator;
};

#endif // SENDMES_H
