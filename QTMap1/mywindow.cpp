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
 MyButton*backbtn=new MyButton(":/back.jpg");//���ذ�ť
 backbtn->setParent(this);//���ø���
 backbtn->move(40,40);
 //����Ҫ���ùؿ����м��ش��������½���

 MyButton*onetn=new MyButton(":/1g.jpg");
 onetn->setParent(this);
 onetn->move(300,100);
 MyButton*twotn=new MyButton(":/2g.jpg");
 twotn->setParent(this);
 twotn->move(500,300);
 connect(backbtn,&MyButton::clicked,this,[=](){
  emit chooseback();
  });//û����һ����ز�����������ť
 g1 *scene=new g1;//��һ���µĽ��棬�л�
 connect(onetn,&MyButton::clicked,this,[=](){
     this->hide();
     scene->show();
 });//[](){}()���Ǹ����ʽ�������������κζ���
 connect(scene,&g1::chooseback,this,[=](){
     scene->hide();//ԭ��������
     this->show();
 });//��һ�ص��л�


g2 *scene1=new g2;//��һ���µĽ��棬�л�
 connect(twotn,&MyButton::clicked,this,[=](){
     this->hide();
     scene1->show();
 });//[](){}()���Ǹ����ʽ�������������κζ���
 connect(scene1,&g2::chooseback,this,[=](){
     scene1->hide();//ԭ��������
     this->show();
 });//��er�ص��л�
//������ֹ��������⣡����
 MyButton*btn1=new MyButton(":/button1.jpg");//���ذ�ť
 btn1->setParent(this);//���ø���
 btn1->move(100,100);
 MyButton*btn2=new MyButton(":/button2.jpg");//���ذ�ť
 btn2->setParent(this);//���ø���
 btn2->move(150,100);
connect(backbtn,&MyButton::clicked,this,[=](){
 emit chooseback();
 });

}


void MyWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pixmap(":/di2.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
}//ѡ�ر���
