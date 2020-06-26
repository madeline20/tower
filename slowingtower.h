#ifndef SLOWINGTOWER_H
#define SLOWINGTOWER_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>

class QPainter;
class Enemy;
class g1;
class QTimer;

class SlowingTower:QObject//两种塔之一，减速塔
{
public:
    SlowingTower(QPoint pos, g1 *game, const QPixmap &sprite = QPixmap(":/image/snow.png"));
    ~SlowingTower();
    void  draw(QPainter *painter) const;
    QPoint getpos() const;
    void levelup1();//升级函数
    void levelup2();
    int level();
public slots:
    void chooseEnemyforAttack();
private:
    int				m_attackRange;	// 代表塔可以攻击到敌人的距离
    qreal        m_slowingrate;//减速比率
    static const QSize ms_fixedSize;
    const QPoint	m_pos;
    g1 *	m_game;
    const QPixmap	m_sprite;
    QTimer *		m_Timer;
   QList <Enemy*> m_chosenEnemyList;
    int               m_level;
};

#endif // SLOWINGTOWER_H
