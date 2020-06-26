#include "mw1.h"
//#include "ui_mw1.h"
#include <QTime>
#include<QTimer>
#include <map>
#include <iostream>
#include <QPushButton>
#include<QPainter>
#include<QPixmap>
#include<QPaintEvent>
#include<QDebug>
#include<QMediaPlayer>
#include"mybutton.h"
#include"mywindow.h"
#include<QMediaPlaylist>
using namespace std;

MW1::MW1(QWidget *parent) :
    QMainWindow(parent)
    //ui(new Ui::MW1)

 {//ui->setupUi(this);
  this->setFixedSize(700,1000);
   MyButton*btn=new MyButton(":/image/play.jpg");
   btn->setParent(this);
   btn->move(400,600);
   MyWindow *scene=new MyWindow;
   connect(btn,&MyButton::clicked,this,[=](){
       this->hide();
       scene->show();
   });
   connect(scene,&MyWindow::chooseback,this,[=](){
       scene->hide();
       this->show();
   });
   MyButton*music=new MyButton(":/image/sound.jpg");
   music->setParent(this);
   music->move(0,0);
   connect(music,&MyButton::clicked,this,&MW1::sound);
}

MW1::~MW1()
{
   // delete ui;
}

void MW1::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pixmap(":/image/yourname.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
}

void MW1::sound(){
           QMediaPlaylist* playlist=new QMediaPlaylist;
            playlist->addMedia(QUrl("qrc:/image/bgm1.mp3"));
            playlist->addMedia(QUrl("qrc:/image/bgm2.mp3"));
            playlist->setCurrentIndex(1);
            playlist->setPlaybackMode(QMediaPlaylist::Loop);
            QMediaPlayer* player = new QMediaPlayer;
            player->setPlaylist(playlist);
            player->play();

}

