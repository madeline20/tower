#include "mybutton.h"
#include<QPixmap>
MyButton::MyButton(QString pix) : QPushButton(0)
{
QPixmap pixmap(pix);//��Ϊ��֪����ť�ж��
this->setFixedSize(pixmap.width(),pixmap.height());
this->setStyleSheet("QPushButton{border:Opx}");//�趨һ����ʽ
this->setIcon(pixmap);
this->setIconSize(QSize(pixmap.width(),pixmap.height()));//��һ��ͼƬ
}
