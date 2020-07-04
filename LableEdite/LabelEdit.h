#ifndef LABELEDIT_H
#define LABELEDIT_H

#include "LableListWidget.h"
#include "LableElement.h"
#include "EditWiget.h"
#include <QGridLayout>


class LabelEdit : public QWidget
{
    Q_OBJECT
private:
    LableListWidget* m_lableList;
    EditWiget      * m_editWiget;
    void layoutUi();

public:
    LabelEdit(QWidget *parent = nullptr);
    ~LabelEdit();
};
#endif // LABELEDIT_H
