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
 MyButton*backbtn=new MyButton(":/back.jpg");//���ذ�ť
 backbtn->setParent(this);//���ø���
 backbtn->move(40,40);

 MyButton*settower=new MyButton(":/an1.jpg");//������ͼƬ
 settower->setParent(this);//���ø���
 settower->move(1100,0);//�ƶ�λ��
 connect(settower,&MyButton::clicked,this,&g1::set_tower);//���ĸ���ϵ

 MyButton*setobject=new MyButton(":/an.jpg");//��ֵ�ͼƬ
setobject->setParent(this);//���ø���
 setobject->move(1000,0);//�ƶ�λ��
 connect(setobject,&MyButton::clicked,this,&g1::addmyobject);//���°�ť���Է���

 connect(backbtn,&MyButton::clicked,this,[=](){
 emit chooseback();
 });
 QTimer*timer=new QTimer(this);
 connect(timer,&QTimer::timeout,this,&g1::updatescene);
   timer->start(10);//�����೤ʱ����һ��ˢ��
}


void g1::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pixmap(":/tu1.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
    foreach (tower *tower1, tower_list) {
        tower1->draw(&painter);}
    foreach(myobject*object,object_list){
        object->draw(&painter);
    }
}//ѡ�ر���
void g1::set_tower(){
   tower*a_newtower=new tower(QPoint(700,300),":/2.png");
   tower_list.push_back(a_newtower);//ͼƬ�Ž�ȥ
    update();
}
void g1::addmyobject(){
    myobject*object=new myobject(QPoint(400,0),QPoint(500,1000),":/guai1.png");
    object_list.push_back(object);
    object->move();
    update();
}

void g1::updatescene(){
    update();
}
