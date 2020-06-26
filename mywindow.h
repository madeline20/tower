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
#include"g1.h"
//namespace U {
//class MyWindow;
//}
class MyWindow : public QMainWindow//选择关卡界面
{
    Q_OBJECT
public:
    explicit MyWindow(QWidget *parent = 0);
    void set_tower();
    //~MyWindow();
    void paintEvent(QPaintEvent *);
private:
    QList<Tower*>tower_list;
    friend class g1;
   signals:
   // U::MyWindow*u;
void chooseback();
public slots:
};

#endif // MYWINDOW_H
