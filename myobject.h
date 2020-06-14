#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <QObject>
#include<QPropertyAnimation>
#include<QPoint>
#include<QPixmap>
#include<QPainter>
class myobject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint currentPos READ getCurrentPos WRITE setCurrentPos)//读取和改写位置
public:
    myobject(QPoint startPos,QPoint targePos,QString fileName);
    void draw(QPainter*painter);
    void move();
    QPoint getCurrentPos();
    void setCurrentPos(QPoint pos);
private:
    QPoint startPos;
    QPoint targePos;
    QPoint currentPos;
    QPixmap pixmap;
    qreal speed;

signals:

};

#endif // MYOBJECT_H
