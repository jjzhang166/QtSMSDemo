#include "MainWindow.h"


int main(int argc,char *argv[])
{
    QApplication a(argc,argv);

    MainWindow wind;

    //�Ƚ�����ӽ�ջ
    wind.LoadForm();
    wind.FormWidget();

    wind.show();

    return a.exec();
}
