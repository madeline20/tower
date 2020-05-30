#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>
#include"tower.h"
#include<QList>
#include <QMainWindow>
#include <QImage>
#include <QPainter>
#include<QKeyEvent>
#include<QTimer>
#include <QPushButton>
//namespace U {
//class MyWindow;
//}
class MyWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MyWindow(QWidget *parent = 0);
    void set_tower();
    //~MyWindow();
    void paintEvent(QPaintEvent *);
private:
    QList<tower*>tower_list;
   signals:
   // U::MyWindow*u;
void chooseback();//Òª¹µÍ¨mywindowºÍmw1
public slots:
};

#endif // MYWINDOW_H
