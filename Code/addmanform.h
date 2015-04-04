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
    //返回上一层窗体
     void Back_form();
     void Button_save();

private:

    //设置号码编辑框只能为数字
    QValidator *validator;

    //布局
    QHBoxLayout *hlayout1;
    QHBoxLayout *hlayout2;
    QHBoxLayout *hlayout3;

    //主布局
    QVBoxLayout *vlayout;

    QLineEdit Phonenum;
    QLineEdit Name;

    QLabel    labelnum;
    QLabel    labelname;

    QPushButton save;
    QPushButton back;
};



#endif // ADDMANFORM_H
