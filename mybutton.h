#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QWidget>
#include<QPushButton>
class MyButton : public QPushButton//按钮，界面跳转作用
{
    Q_OBJECT
public:
    explicit MyButton(QString pix);

signals:

public slots:
};

#endif // MYBUTTON_H
