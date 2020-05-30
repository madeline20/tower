#include "g1.h"
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
g1::g1(QWidget *parent) : QMainWindow(parent)
{
 this->setFixedSize(1200,700);
 MyButton*backbtn=new MyButton(":/back.jpg");//返回按钮
 backbtn->setParent(this);//设置父类
 backbtn->move(40,40);
 //这里要设置关卡，有几关创建几个新界面
 MyButton*settower=new MyButton(":/1.png");//设塔的图片
 settower->setParent(this);//设置父类
 settower->move(500,500);//移动位置
 connect(settower,&MyButton::clicked,this,&g1::set_tower);//跟哪个联系
 connect(backbtn,&MyButton::clicked,this,[=](){
 emit chooseback();
 });

}


void g1::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pixmap(":/tu1.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
}//选关背景
void g1::set_tower(){
   tower*a_newtower=new tower(QPoint(100,100),":/1.png");
   tower_list.push_back(a_newtower);//图片放进去
    update();
}
