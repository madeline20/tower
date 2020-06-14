#include "myobject.h"

myobject::myobject(QPoint startPos,QPoint targePos,QString fileName) : QObject(0),pixmap(fileName)

{
   this->currentPos=startPos;
   this->startPos=startPos;
    this->targePos=targePos;
    speed=1.0;
}

void myobject::draw(QPainter *painter){
    painter->drawPixmap(currentPos,pixmap);

}
void myobject::move(){
    QPropertyAnimation*animation=new QPropertyAnimation(this,"currentPos");
    animation->setDuration(10000);
    animation->setStartValue(startPos);
    animation->setEndValue(targePos);
    animation->start();

}

QPoint myobject::getCurrentPos(){
    return this->currentPos;
}

void myobject::setCurrentPos(QPoint pos){
    this->currentPos=pos;
}
