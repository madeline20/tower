#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include"slowingtower.h"
class WayPoint;
class QPainter;
class g1;
class Tower;
class SlowingTower;
class Enemy : public QObject//怪物，通过设置移速及血量，共实现了三种
{
	Q_OBJECT
public:
    Enemy(WayPoint *startWayPoint, g1 *game, const QPixmap &sprite = QPixmap(":/image/2.png"), qreal speed=3, int Hp=85);

	~Enemy();

	void draw(QPainter *painter) const;
    void move();//移动函数
    void getDamage(int damage);//减小玩家生命值
    void getRemoved();//消除函数
    void getAttacked(Tower *attacker);//受到攻击
    void gotLostSight(Tower *attacker);//离开塔的攻击范围
    QPoint pos() const;//返回位置
    bool getenterBase();//是否进入基地
    void getSlowed(qreal slowingrate);//减速
    friend class SlowingTower;
public slots:
    void doActivate();//激活

private:
	bool			m_active;
	int				m_maxHp;
	int				m_currentHp;
	qreal			m_walkingSpeed;
	qreal			m_rotationSprite;
    qreal        m_slowedrate;
	QPoint			m_pos;
	WayPoint *		m_destinationWayPoint;
    g1 *	m_game;

	QList<Tower *>	m_attackedTowersList;
    bool m_enterBase;
	const QPixmap	m_sprite;
    static const QSize ms_fixedSize;//静态常量，固定大小，便于修改
};

#endif // ENEMY_H
