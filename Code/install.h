#ifndef INSTALL_H
#define INSTALL_H

#include<QtGui>

class Setting:public QWidget
{

Q_OBJECT
public:
    Setting();
    ~Setting();

    //���ɴ���
    void create();

private slots:

    void check_click_white();
    void check_click_black();
    //����������Ϣ
    void save_info();
    void back_form();
private:

    //������

    QHBoxLayout  *layout_name;
    QHBoxLayout  *layout_num;
    QHBoxLayout  *layout_button;
    QVBoxLayout  *mainlayout;


    QCheckBox  ckeckbox_filter;
    QCheckBox  checkbox_black;
    QCheckBox  checkbox_white;

    QLineEdit  phonenum;
    QLineEdit  name;

    QLabel      line_num;
    QLabel      line_name;

    QPushButton  save;
    QPushButton  back;
};

#endif // INSTALL_H
