#include "g2.h"
#include <QTime>
#include<QTimer>
#include <map>
#include <iostream>
#include <QPushButton>
#include<QPainter>
#include<QPixmap>
#include<QPaintEvent>
#include<QDebug>
#include<QList>
#include"mybutton.h"
#include"mywindow.h"
using namespace std;
g2::g2(QWidget *parent) : QMainWindow(parent)
{
 this->setFixedSize(1200,700);
 MyButton*backbtn=new MyButton(":/back.jpg");//返回按钮
 backbtn->setParent(this);//设置父类
 backbtn->move(40,40);
 connect(backbtn,&MyButton::clicked,this,[=](){
 emit chooseback();
 });

 MyButton*settower=new MyButton(":/an1.jpg");//设塔的图片
 settower->setParent(this);//设置父类
 settower->move(1100,0);//移动位置
 connect(settower,&MyButton::clicked,this,&g2::set_tower);//跟哪个联系

 MyButton*setobject=new MyButton(":/an.jpg");//设怪的图片
setobject->setParent(this);//设置父类
 setobject->move(1000,0);//移动位置
 connect(setobject,&MyButton::clicked,this,&g2::addmyobject);//按下按钮可以发怪


 QTimer*timer=new QTimer(this);
 connect(timer,&QTimer::timeout,this,&g2::updatescene);
   timer->start(10);//经过多长时间算一次刷新
}

void g2::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pixmap(":/tu2.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
    foreach (tower *tower1, tower_list) {
        tower1->draw(&painter);}
    foreach(myobject*object,object_list){
        object->draw(&painter);
    }
}//选关背景
void g2::set_tower(){
   tower*a_newtower=new tower(QPoint(500,500),":/1.png");
   tower_list.push_back(a_newtower);//图片放进去
    update();
}
void g2::addmyobject(){
    myobject*object=new myobject(QPoint(0,400),QPoint(1200,300),":/guai2.png");
    object_list.push_back(object);
    object->move();
    update();
}

void g2::updatescene(){
    update();
}
