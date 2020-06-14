#ifndef G1_H
#define G1_H
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
class g1 : public QMainWindow
{
    Q_OBJECT
public:
    explicit g1(QWidget *parent = 0);
    void set_tower();
    //~MyWindow();
    void paintEvent(QPaintEvent *);
    void addmyobject();
    void updatescene();
private:
    QList<tower*>tower_list;
    QList<myobject*> object_list;
signals:
      void chooseback();
   // U::MyWindow*u;
//Òª¹µÍ¨mywindowºÍmw1
public slots:

};
#endif // G1_H
