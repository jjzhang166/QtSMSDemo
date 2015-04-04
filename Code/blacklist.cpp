#include "blacklist.h"

BlackList::BlackList():BookFather("../Test/BlackList.xml")
{


}
BlackList::~BlackList()
{

}
void BlackList::CreateMenu()
{

    popMenu = new QMenu(this);

    action_edit = new QAction("±à¼­",this);
    action_delete = new QAction("É¾³ý",this);
    action_black = new QAction("¼Ó°×Ãûµ¥",this);

    connect(action_edit,SIGNAL(triggered()),this,SLOT(Edit()));
    connect(action_delete,SIGNAL(triggered()),this,SLOT(Dele()));
    connect(action_black,SIGNAL(triggered()),this,SLOT(move()));

    popMenu->addAction(action_edit);
    popMenu->addAction(action_delete);
    popMenu->addAction(action_black);

}

void BlackList::move()
{

    xml.dele(list->currentRow());

    xml.save();
    MyXml  white("../Test/Phone.xml");

    QStringList strlist = list->currentItem()->text().split("\n");

    white.addelement(strlist.at(1),strlist.at(0));

    white.save();

    QListWidgetItem *item = list->takeItem(list->currentRow());
    delete item;

    LoadBook();

}

