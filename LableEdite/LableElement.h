#ifndef LABLEELEMENT_H
#define LABLEELEMENT_H

#include <QWidget>
#include <QLabel>

class LableElement : public QLabel
{
    Q_OBJECT
private:
    /**
      *@brief 重写drop的4大操作, 即enter leave move drop
    */
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent* event)override;

public:
    explicit LableElement(QWidget *parent = nullptr);
    ~LableElement();
signals:

};

#endif // LABLEELEMENT_H
