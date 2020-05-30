#include "mw1.h"
#include "ui_mw1.h"
#include <QTime>
#include<QTimer>
#include <map>
#include <iostream>
#include <QPushButton>
#include<QPainter>
#include<QPixmap>
#include<QPaintEvent>
#include<QDebug>

#include"mybutton.h"
#include"mywindow.h"
using namespace std;

MW1::MW1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MW1)
{
    ui->setupUi(this);
    this->setFixedSize(700,1000);
   MyButton*btn=new MyButton(":/play.jpg");
   btn->setParent(this);
   btn->move(400,600);
   MyWindow *scene=new MyWindow;//��һ���µĽ��棬�л�
   connect(btn,&MyButton::clicked,this,[=](){
       this->hide();
       scene->show();
   });//[](){}()���Ǹ����ʽ�������������κζ���
   connect(scene,&MyWindow::chooseback,this,[=](){
       scene->hide();//ԭ��������
       this->show();
   });
}

MW1::~MW1()
{
    delete ui;
}

void MW1::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pixmap(":/yourname.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
}



