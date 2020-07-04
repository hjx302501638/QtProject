#include "LableListWidget.h"
#include <QEvent>
#include <QtWidgets>
#include <QDrag>
#include <QDebug>
#include <QMouseEvent>
#include <QMimeData>

LableListWidget::LableListWidget(QWidget *parent) : QListWidget(parent)
{

    m_pLabel = new QLabel(this);
    m_pLabel->setStyleSheet("border:2px solid blue;background:transparent");
    m_pLabel->hide();
    m_pLabel->setFixedSize(50,50);
    /*使能 控件拖拽功能*/
    this->setDropIndicatorShown(true);
    this->setDragEnabled(true);//是否支持拖拽自己的项目
    this->setAcceptDrops(true);//是否为此小部件增加拖拽事件
    addItem("二维码" ,":/Imge/Imge/Icon/QRCode.png");
    addItem("条形码",":/Imge/Imge/Icon/barCode.png");
    addItem("线",":/Imge/Imge/Icon/Line .png");
    addItem("框",":/Imge/Imge/Icon/frame.png");
    addItem("文本",":/Imge/Imge/Icon/Text.png");
    addItem("图片",":/Imge/Imge/Icon/picture.png");
}

void LableListWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasText()) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}
void LableListWidget::dragMoveEvent(QDragMoveEvent *event)
{
  event->accept();
}
void LableListWidget::dropEvent(QDropEvent *event)
{
  event->accept();
}

void LableListWidget::addItem(const QString& strText,const QString dir)
{
    QListWidgetItem *item = new QListWidgetItem(this);
    item->setText(strText);
    item->setIcon(QIcon(dir));
    item->setToolTip(strText);
    itemHash.insert(strText,dir);
}

void LableListWidget::mouseMoveEvent(QMouseEvent* event)
{
    QListWidgetItem *item = currentItem();

    m_pLabel->setText(item->text());


    QImage Image;
    Image.load(itemHash.value(item->text()));
    QPixmap pix = QPixmap::fromImage(Image);
    QPixmap fitpixmap = pix.scaled(50, 50, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
    //QPixmap fitpixmap = pixmap.scaled(with, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
    m_pLabel->setScaledContents(true);
    m_pLabel->setPixmap(fitpixmap);

    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData();
    mimeData->setText(item->text());
    mimeData->setHtml(itemHash.value(item->text()));
//    qreal dpr = window()->windowHandle()->devicePixelRatio();
//    QPixmap pixmap(m_pLabel->size() * dpr);
//    pixmap.setDevicePixelRatio(dpr);
//    m_pLabel->render(&pixmap);


    drag->setPixmap(fitpixmap);
    drag->setMimeData(mimeData);
    drag->setHotSpot(QPoint(fitpixmap.width()/fitpixmap.width(), fitpixmap.height()/2));

    Qt::DropAction resultAction = drag->exec(Qt::MoveAction);
    if(resultAction == Qt::MoveAction)
    {
        // 确认移动操作
    }
    event->accept();
}
LableListWidget::~LableListWidget()
{

}
