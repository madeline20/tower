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
 //����Ҫ���ùؿ����м��ش��������½���
 MyButton*settower=new MyButton(":/1.png");//������ͼƬ
 settower->setParent(this);//���ø���
 settower->move(500,500);//�ƶ�λ��
 connect(settower,&MyButton::clicked,this,&g1::set_tower);//���ĸ���ϵ
 connect(backbtn,&MyButton::clicked,this,[=](){
 emit chooseback();
 });

}


void g1::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pixmap(":/tu1.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
}//ѡ�ر���
void g1::set_tower(){
   tower*a_newtower=new tower(QPoint(100,100),":/1.png");
   tower_list.push_back(a_newtower);//ͼƬ�Ž�ȥ
    update();
}
