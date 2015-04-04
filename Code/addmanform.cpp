#include "addmanform.h"

#include"MainWindow.h"

AddManForm::AddManForm()
{
   Phonenum.setMaxLength(11);

   QRegExp regx("[0-9]+$");
   validator = new QRegExpValidator(regx,&Phonenum);
   Phonenum.setValidator(validator);

}
AddManForm::~AddManForm()
{
    delete hlayout1;
    delete hlayout2;
    delete hlayout3;
    delete vlayout;

    delete validator;
}

//�����������
void AddManForm::CreateForm()
{
   labelnum.setText("����");;
   labelname.setText("����");;

   save.setText("����");
   back.setText("����");

   vlayout = new QVBoxLayout;
   hlayout1 = new QHBoxLayout;
   hlayout2 = new QHBoxLayout;
   hlayout3 = new QHBoxLayout;

   hlayout1-> addWidget(&labelnum);
   hlayout1-> addWidget(&Phonenum);

   hlayout2-> addWidget(&labelname);
   hlayout2-> addWidget(&Name);

   hlayout3-> addWidget(&save);
   hlayout3-> addWidget(&back);

   vlayout-> addLayout(hlayout1);
   vlayout-> addLayout(hlayout2);
   vlayout-> addLayout(hlayout3);

   connect(&back,SIGNAL(released()),this,SLOT(Back_form()));
   connect(&save,SIGNAL(released()),this,SLOT(Button_save()));

   this->setLayout(vlayout);
}
void AddManForm::Back_form()
{

    Phonenum.clear();
    Name.clear();

    save.setText("����");
    QStackedWidget *stackw=MainWindow::GetStackedWidget();
    stackw->setCurrentWidget(MainWindow::GetPreviousForm());

}
void AddManForm::Button_save()
{
    QMessageBox msgBox;
    BookFather *preform=(BookFather *)MainWindow::GetPreviousForm();

    if(save.text() =="����"){
        if(Phonenum.text().isEmpty())
        {

            msgBox.setText("�绰���벻��Ϊ��");
            msgBox.exec();
        }

        preform->AddLinkMan(Phonenum.text(),Name.text());

        Phonenum.clear();
        Name.clear();
    }
    else if(save.text() =="����")
    {
        if(Phonenum.text().isEmpty())
        {

            msgBox.setText("�绰���벻��Ϊ��");
            msgBox.exec();
        }

        preform->ModifMan(Phonenum.text(),Name.text());
        Phonenum.clear();
        Name.clear();
    }
}

//������Ϣ�õĲ�
void AddManForm::SwitchButton(QString name,QString num)
{
    save.setText("����");

    Phonenum.setText(num);
    Name.setText(name);

}
