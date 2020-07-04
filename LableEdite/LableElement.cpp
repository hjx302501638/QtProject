#include "LableElement.h"
#include <QDrag>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDebug>
#include <QMimeData>
#include <QWindow>


LableElement::LableElement(QWidget *parent) : QLabel(parent)
{

}


LableElement::~LableElement()
{

}
void LableElement::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}
void LableElement::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();
}
void LableElement::dropEvent(QDropEvent *event)
{
    event->ignore();
}
void LableElement::mousePressEvent(QMouseEvent* event)
{
    if(Qt::LeftButton == event->button())
    {
        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData();
        mimeData->setText(this->toolTip());

        QPoint hotSpot = event->pos();
        qDebug()<<"toolTip"<<this->toolTip();
        qDebug()<<"tc log 015 : "<<hotSpot;

        mimeData->setData(QStringLiteral("application/x-hotspot"),
                          QByteArray::number(hotSpot.x()) + ' ' + QByteArray::number(hotSpot.y()));

        qreal dpr = window()->windowHandle()->devicePixelRatio();
        QPixmap pixmap(this->size() * dpr);
        pixmap.setDevicePixelRatio(dpr);
        this->render(&pixmap);

        drag->setPixmap(pixmap);
        drag->setMimeData(mimeData);
        drag->setHotSpot(hotSpot);

        this->hide();
        drag->exec(Qt::MoveAction);
    }
}
