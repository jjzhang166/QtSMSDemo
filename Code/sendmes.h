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

    //本机号码
    QString OwnPhoneNum;
    //布局
    QVBoxLayout *mainlayout;
    QHBoxLayout *hlayout;
    QHBoxLayout *hlayout1;

    QPushButton back;
    QPushButton send;
    QPushButton load;

    QLineEdit edit_num;
    QTextEdit text;

    //设置号码编辑框只能为数字
    QValidator *validator;
};

#endif // SENDMES_H
