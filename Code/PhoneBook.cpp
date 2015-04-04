#include"PhoneBook.h"

#include"MainWindow.h"

PhoneBook::PhoneBook():BookFather("../Test/Phone.xml")
{


}
PhoneBook::~PhoneBook()
{

}

void PhoneBook::CreateMenu()
{

    popMenu = new QMenu(this);

    action_edit = new QAction("�༭",this);
    action_delete = new QAction("ɾ��",this);
    action_black = new QAction("�Ӻ�����",this);

    connect(action_edit,SIGNAL(triggered()),this,SLOT(Edit()));
    connect(action_delete,SIGNAL(triggered()),this,SLOT(Dele()));
    connect(action_black,SIGNAL(triggered()),this,SLOT(move()));

    popMenu->addAction(action_edit);
    popMenu->addAction(action_delete);
    popMenu->addAction(action_black);

    connect(list,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(transmit()));

}

//*******************��**************************

//˫���Ļ������ض��ű༭����
void PhoneBook::transmit()
{
    QStackedWidget *stackw=MainWindow::GetStackedWidget();

    if(MainWindow::GetPreviousForm() == stackw->widget(1))
    {

        SendMes *m = (SendMes *)stackw->widget(1);

        QStringList l=list->item(list->currentRow())->text().split("\n");
        m->SetPhoneNum(l.at(1));
        stackw->setCurrentWidget(stackw->widget(1));
    }

}

//�ۺ���
void PhoneBook::move()
{
    xml.dele(list->currentRow());
    xml.save();

    MyXml  black("../Test/BlackList.xml");
    QStringList strlist = list->currentItem()->text().split("\n");

    black.addelement(strlist.at(1),strlist.at(0));

    QListWidgetItem *item = list->takeItem(list->currentRow());
    delete item;

    black.save();
    LoadBook();
}

