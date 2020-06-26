#ifndef TOWER_H
#define TOWER_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>

class QPainter;
class Enemy;
class g1;
class QTimer;

class Tower : QObject//两种塔之一，攻击塔
{
	Q_OBJECT
public:
    Tower(QPoint pos, g1 *game, const QPixmap &sprite = QPixmap(":/image/tower.png"));
	~Tower();

	void draw(QPainter *painter) const;
	void checkEnemyInRange();
	void targetKilled();
	void attackEnemy();
	void chooseEnemyForAttack(Enemy *enemy);
	void removeBullet();
	void damageEnemy();
    void lostSightOfEnemy();//此塔失去敌人视野
    QPoint getpos() const;
    void levelup1();//升级函数
    void levelup2();
    int level();
private slots:
	void shootWeapon();

private:
	bool			m_attacking;
	int				m_attackRange;	// 代表塔可以攻击到敌人的距离
	int				m_damage;		// 代表攻击敌人时造成的伤害
	int				m_fireRate;		// 代表再次攻击敌人的时间间隔
    qreal			m_rotationSprite;//旋转
    int            m_level;
	Enemy *			m_chooseEnemy;
    g1 *	m_game;
    QTimer *		m_fireRateTimer;//攻击间隔

	const QPoint	m_pos;
	const QPixmap	m_sprite;

	static const QSize ms_fixedSize;
};

#endif // TOWER_H
