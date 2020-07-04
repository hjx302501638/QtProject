#ifndef EDITWIGET_H
#define EDITWIGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QHash>
#include <QTextEdit>
#include "LableElement.h"
#include <QMouseEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QPaintDevice>
#include <QPoint>
#include <QList>

class EditWiget : public QWidget
{
    Q_OBJECT

private:
        enum DrawType
        {
            NONE,
            LINE,
            RECT,
            TEXT
        };

        struct DrawPram
        {
            DrawType Type;
            Qt::GlobalColor  color;
            QList<QPoint>  point;
        };
        QList<DrawPram> m_drawList;
        DrawPram        now_Pram;
        bool            draFlag;
        void draw(QPainter& painter,DrawPram& parm );
        void apeedPiont(QPoint p);
    /**
      *@brief 重写drop的4大操作, 即enter leave move drop
    */
    void dropEvent(QDropEvent *e)override;
    void dragEnterEvent(QDragEnterEvent *e)override;
    void dragMoveEvent(QDragMoveEvent *e)override;
    bool m_bInternalMove;
    QHash<QString,LableElement*> m_hash;

    /*重写鼠标事件*/
    void mousePressEvent(QMouseEvent *event);//按下
    void mouseReleaseEvent(QMouseEvent *event);//松开
    void mouseMoveEvent(QMouseEvent *event);//鼠标移动

    void paintEvent(QPaintEvent *event);

public:
    explicit EditWiget(QWidget *parent = nullptr);
    ~EditWiget();
signals:

};

#endif // EDITWIGET_H
