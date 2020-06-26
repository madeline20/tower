#ifndef MW1_H
#define MW1_H

#include <QMainWindow>
#include <QImage>
#include <QPainter>
#include<QKeyEvent>
#include<QTimer>
#include <QPushButton>

/*namespace Ui {
class MW1;
}*/

class MW1 : public QMainWindow//第一个界面，有总音量函数
{
    Q_OBJECT

public:
    explicit MW1(QWidget *parent = 0);
    ~MW1();
    void paintEvent(QPaintEvent *);
    void sound();
private:
    //Ui::MW1 *ui;

};

#endif // MW1_H
