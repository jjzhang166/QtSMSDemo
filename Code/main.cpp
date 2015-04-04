#include "MainWindow.h"


int main(int argc,char *argv[])
{
    QApplication a(argc,argv);

    MainWindow wind;

    //先将窗体加进栈
    wind.LoadForm();
    wind.FormWidget();

    wind.show();

    return a.exec();
}
