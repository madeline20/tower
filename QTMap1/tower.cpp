#include "tower.h"
#include<QPoint>
#include<QPixmap>
#include<QPainter>
tower::tower(QPoint pos,QString pixFilename ) : QObject(0),pixmap(pixFilename)
{
_pos =pos;
}
void tower::draw(QPainter*painter){
    painter->drawPixmap(_pos,pixmap);//»­·ÀÓùËş
}
