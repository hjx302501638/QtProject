#include "LabelEdit.h"
#include <QGridLayout>

LabelEdit::LabelEdit(QWidget *parent)
    : QWidget(parent)
{

    layoutUi();
}
void LabelEdit::layoutUi()
{
    m_lableList = new LableListWidget(this);
    m_editWiget = new EditWiget(this);
    QGridLayout * layout  = new QGridLayout();
    m_lableList->setMaximumWidth(150);
    layout->addWidget(m_lableList,0,0,1,1);
    layout->addWidget(m_editWiget,0,1,1,4);
    this->setLayout(layout);
}
LabelEdit::~LabelEdit()
{
}

