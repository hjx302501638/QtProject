#ifndef LABLELISTWIDGET_H
#define LABLELISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLabel>
#include <QHash>
#include <QString>

class LableListWidget : public QListWidget
{
    Q_OBJECT
    QLabel *m_pLabel;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void addItem(const QString& strText,const QString dir = "");
    QHash<QString,QString> itemHash;
    void mouseMoveEvent(QMouseEvent* event)override;
public:
    explicit LableListWidget(QWidget *parent = nullptr);
    ~LableListWidget();
signals:

};

#endif // LABLELISTWIDGET_H
