#ifndef TOWER_H
#define TOWER_H

#include <QObject>
#include<QPoint>
#include<QPixmap>
class tower : public QObject
{
    Q_OBJECT
public:
    tower(QPoint pos,QString pixFilename );
    void draw(QPainter*painter);//在空白的界面绘图
private:
    QPoint _pos;
    QPixmap pixmap;
signals:

};

#endif // TOWER_H
