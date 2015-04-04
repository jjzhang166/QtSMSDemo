#ifndef ADDMANFORM_H
#define ADDMANFORM_H

#include<QtGui>

class AddManForm:public QWidget
{

Q_OBJECT

public:
    AddManForm();
    ~AddManForm();

    void CreateForm();

    void SwitchButton(QString name,QString num);

private slots:
    //������һ�㴰��
     void Back_form();
     void Button_save();

private:

    //���ú���༭��ֻ��Ϊ����
    QValidator *validator;

    //����
    QHBoxLayout *hlayout1;
    QHBoxLayout *hlayout2;
    QHBoxLayout *hlayout3;

    //������
    QVBoxLayout *vlayout;

    QLineEdit Phonenum;
    QLineEdit Name;

    QLabel    labelnum;
    QLabel    labelname;

    QPushButton save;
    QPushButton back;
};



#endif // ADDMANFORM_H
