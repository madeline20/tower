#ifndef BULLET_H
#define BULLET_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>
#include<QMainWindow>
class QPainter;
class Enemy;
class g1;
class g2;
class QMainWindow;
class Bullet : QObject//子弹类
{
	Q_OBJECT
	Q_PROPERTY(QPoint m_currentPos READ currentPos WRITE setCurrentPos)

public:
    Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target,
           g1*game, const QPixmap &sprite = QPixmap(":/image/bullet.png"));
	void draw(QPainter *painter) const;
	void move();
	void setCurrentPos(QPoint pos);
	QPoint currentPos() const;

private slots:
    void hitTarget();

private:
	const QPoint	m_startPos;
	const QPoint	m_targetPos;
	const QPixmap	m_sprite;
	QPoint			m_currentPos;
	Enemy *			m_target;
    g1*	m_game;
    g2*  m_game1;
	int				m_damage;

	static const QSize ms_fixedSize;
};

#endif // BULLET_H
