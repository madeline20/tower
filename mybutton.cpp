#include "mybutton.h"
#include<QPixmap>
#include<QAction>
MyButton::MyButton(QString pix) : QPushButton(0)
{
QPixmap pixmap(pix);//因为不知道按钮有多大
/*this->setFixedSize(pixmap.width(),pixmap.height());
this->setStyleSheet("QPushButton{border:Opx}");//设定一个样式
this->setIcon(pixmap);
this->setIconSize(QSize(pixmap.width(),pixmap.height()));//传一个图片*/
this->setFixedSize(100,100);
this->setStyleSheet("QPushButton{border:0px;}");
this->setIcon(pixmap);
this->setIconSize(QSize(100,100));
}
