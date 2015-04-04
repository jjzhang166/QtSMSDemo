#ifndef INSTALL_H
#define INSTALL_H

#include<QtGui>

class Setting:public QWidget
{

Q_OBJECT
public:
    Setting();
    ~Setting();

    //生成窗体
    void create();

private slots:

    void check_click_white();
    void check_click_black();
    //保存设置信息
    void save_info();
    void back_form();
private:

    //主布局

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
