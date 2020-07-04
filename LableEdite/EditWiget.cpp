#include "EditWiget.h"



#include <QtWidgets>
#include <QMouseEvent>

#include <QPushButton>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QDrag>
#include <QLabel>
#include <QDebug>
#include <QHBoxLayout>
#include <QPalette>
#include <QStyle>
EditWiget::EditWiget(QWidget *parent) : QWidget(parent)
{
    setAcceptDrops(true);
    QPalette pal(this->palette());
    draFlag = false;

    pal.setColor(QPalette::Background, Qt::white); //设置背景白色
    this->setAutoFillBackground(true);
    this->setPalette(pal);

}


EditWiget:: ~EditWiget()
{

}


void EditWiget::dropEvent(QDropEvent *e)
{
    e->acceptProposedAction();
    qDebug()<<"dropEvent!"<<e->mimeData()->text();
    LableElement *pBtn = nullptr;
    LableElement *pBtnTemp = nullptr;
    if(m_hash.contains(e->mimeData()->text()))//如果当前界面中有这个元素则移动即可
    {
        QString str = e->mimeData()->text();
         if((str=="二维码")||(str=="条形码")||(str=="图片"))
         {
        qDebug()<<e->mimeData()->html();
        pBtn = m_hash.value(e->mimeData()->text());
        QPoint hotSpot;

        QByteArrayList hotSpotPos = e->mimeData()->data(QStringLiteral("application/x-hotspot")).split(' ');
        if (hotSpotPos.size() == 2) {
            hotSpot.setX(hotSpotPos.first().toInt());
            hotSpot.setY(hotSpotPos.last().toInt());
        }
        pBtn->move(e->pos()-hotSpot);
        pBtn->setStyleSheet("border:2px dotted #242424;");

        QHash<QString, LableElement*>::iterator i;
        for(i = m_hash.begin() ;i!=m_hash.end();++i)
        {
            if(i.value() != pBtn)
            {
                pBtnTemp = i.value();
                pBtnTemp->setStyleSheet("");
            }
        }
          pBtn->show();// 放到这个 位置调用要不然会出现野指针访问bug
     }else
         {
             draFlag = true;
         }
    }
    else
    {
        QString  str = e->mimeData()->text();
        if((str=="二维码")||(str=="条形码")||(str=="图片"))
        {
        pBtn = new LableElement(this);
        QImage Image ;

        Image.load(e->mimeData()->html());
        QPixmap pixmap = QPixmap::fromImage(Image);

        QPixmap fitpixmap = pixmap.scaled(50, 50, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
        //QPixmap fitpixmap = pixmap.scaled(with, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
        pBtn->setScaledContents(true);
        pBtn->setPixmap(fitpixmap);
        pBtn->setToolTip(e->mimeData()->text());
        pBtn->resize(50,50);
        m_hash.insert(e->mimeData()->text(),pBtn);
        pBtn->move(e->pos());
          pBtn->show();// 放到这个 位置调用要不然会出现野指针访问bug
        }else
        {

            draFlag = true;

        }

    }


}
void EditWiget::dragEnterEvent(QDragEnterEvent *e)
{
    qDebug()<<"target dragEnterEvent :"<<e->mimeData()->text();
    e->acceptProposedAction();
}
void EditWiget::dragMoveEvent(QDragMoveEvent *e)
{

    e->acceptProposedAction();
}

void EditWiget::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<event->pos();
    if(draFlag)
    {
        now_Pram.point.clear();
        now_Pram.Type = RECT;
        now_Pram.color  = Qt::GlobalColor::blue;
        apeedPiont(event->pos());
    }
    event->ignore();
}

void EditWiget::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug()<<event->pos();
    if(draFlag)
    {
        draFlag = false;
        m_drawList.append(now_Pram);
        update();
    }
    event->ignore();
}

void EditWiget::mouseMoveEvent(QMouseEvent *event)//鼠标移动
{
    qDebug()<<event->pos();
    if(draFlag)
    {
        apeedPiont(event->pos());
        update();
    }
    event->ignore();
}
void EditWiget::paintEvent(QPaintEvent *event)
{
     QPainter painter(this);

     for(int i = 0 ;i < m_drawList.count();i++)
     {
        draw(painter,m_drawList[i]);
     }
    draw(painter,now_Pram);

    event->ignore();
}
void EditWiget::draw(QPainter& painter,DrawPram& parm )
{

    if((parm.Type != NONE) && (parm.point.count() >= 2))
    {
        /*获得坐标  宽度高度*/
        int x = (parm.point[0].x() < parm.point[1].x()) ? parm.point[0].x() : parm.point[1].x();
        int y = (parm.point[0].y() < parm.point[1].y()) ? parm.point[0].y() : parm.point[1].y();
        int w = qAbs(parm.point[0].x() - parm.point[1].x()) + 1;
        int h = qAbs(parm.point[0].y() - parm.point[1].y()) + 1;
        painter.setPen(QPen(parm.color,2));//设置画笔颜色

        //painter.setBrush(QBrush(parm.color));//设置画刷颜色
        switch (parm.Type) {
        case LINE:painter.drawLine(parm.point[0],parm.point[1]);
            break;
        case RECT:painter.drawRect(x,y,w,h);
            break;
        case TEXT:
            break;
        default:
            break;
        }
    }
}


void EditWiget::apeedPiont(QPoint p)
{
    if(now_Pram.point.count() == 2)
    {
        now_Pram.point.removeLast();
        now_Pram.point.append(p);
    }else now_Pram.point.append(p);

}
