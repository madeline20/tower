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
        class g2 : public QMainWindow
        {
            Q_OBJECT
        public:
            explicit g2(QWidget *parent = 0);
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

#endif // G2_H
