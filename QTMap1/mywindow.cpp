#include "mywindow.h"

#include <QTime>
#include<QTimer>
#include <map>
#include <iostream>
#include <QPushButton>
#include<QPainter>
#include<QPixmap>
#include<QPaintEvent>
#include<QDebug>
#include"g1.h"
#include"g2.h"
#include"mybutton.h"
#include"mywindow.h"
using namespace std;
MyWindow::MyWindow(QWidget *parent) : QMainWindow(parent)
{
 this->setFixedSize(1200,700);
 MyButton*backbtn=new MyButton(":/back.jpg");//返回按钮
 backbtn->setParent(this);//设置父类
 backbtn->move(40,40);
 //这里要设置关卡，有几关创建几个新界面

 MyButton*onetn=new MyButton(":/1g.jpg");
 onetn->setParent(this);
 onetn->move(300,100);
 MyButton*twotn=new MyButton(":/2g.jpg");
 twotn->setParent(this);
 twotn->move(500,300);
 connect(backbtn,&MyButton::clicked,this,[=](){
  emit chooseback();
  });//没有这一句加载不出来两个按钮
 g1 *scene=new g1;//建一个新的界面，切换
 connect(onetn,&MyButton::clicked,this,[=](){
     this->hide();
     scene->show();
 });//[](){}()这是个表达式，能用类里面任何东西
 connect(scene,&g1::chooseback,this,[=](){
     scene->hide();//原界面隐藏
     this->show();
 });//第一关的切换


g2 *scene1=new g2;//建一个新的界面，切换
 connect(twotn,&MyButton::clicked,this,[=](){
     this->hide();
     scene1->show();
 });//[](){}()这是个表达式，能用类里面任何东西
 connect(scene1,&g2::chooseback,this,[=](){
     scene1->hide();//原界面隐藏
     this->show();
 });//第er关的切换
//这里出现过套娃问题！！！
 MyButton*btn1=new MyButton(":/button1.jpg");//返回按钮
 btn1->setParent(this);//设置父类
 btn1->move(100,100);
 MyButton*btn2=new MyButton(":/button2.jpg");//返回按钮
 btn2->setParent(this);//设置父类
 btn2->move(150,100);
connect(backbtn,&MyButton::clicked,this,[=](){
 emit chooseback();
 });

}


void MyWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pixmap(":/di2.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
}//选关背景
