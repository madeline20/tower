#ifndef G2_H
#define G2_H
#include <QMainWindow>

#include"tower.h"
 #include<QList>
#include <QMainWindow>
#include <QImage>
#include <QPainter>
#include<QKeyEvent>
#include<QTimer>
#include <QPushButton>
#include"myobject.h"
class g2: public QMainWindow
{
    Q_OBJECT
public:
    explicit g2(QWidget *parent = 0);
    void set_tower();
    //~MyWindow();
    void paintEvent(QPaintEvent *);
    void addmyobject();//添加塔
    void updatescene();//更新界面
private:
    QList<tower*>tower_list;
    QList<myobject*> object_list;
signals:
      void chooseback();
   // U::MyWindow*u;
//要沟通mywindow和mw1
public slots:

};
#endif // G2_H

