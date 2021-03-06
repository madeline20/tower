#ifndef G1_H
#define G1_H

#include <QMainWindow>
#include <QList>
#include "towerposition.h"
#include "tower.h"
#include"mywindow.h"
#include"slowingtower.h"
/*namespace Ui {
class g1;
}*/

class WayPoint;
class Enemy;
class Bullet;
//class AudioPlayer;
class mywindow;
class g1 : public QMainWindow//第一关，已经基本实现，塔的升级尚未实现，第一关几乎无胜利可能性
{
	Q_OBJECT
	
public:
    explicit g1(QWidget *parent = 0);
    ~g1();

    void getHpDamage(int damage = 1);//减小玩家生命值
	void removedEnemy(Enemy *enemy);
	void removedBullet(Bullet *bullet);
	void addBullet(Bullet *bullet);
    void awardGold(int gold);//怪物死亡后，金币上升

    //AudioPlayer* audioPlayer() const;
    QList<Enemy *> enemyList() const;//返回怪物List

protected:
	void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);//鼠标点击事件
   friend class   mywindow;
public slots:
   void gameStart();
private slots:
	void updateMap();


private:
	void loadTowerPositions();
	void addWayPoints();
	bool loadWave();
	bool canBuyTower() const;
	void drawWave(QPainter *painter);
	void drawHP(QPainter *painter);
	void drawPlayerGold(QPainter *painter);
	void doGameOver();
    //void preLoadWavesInfo();

private:
    //Ui::     g1 *		   ui;
	int						m_waves;
	int						m_playerHp;
	int						m_playrGold;
	bool					m_gameEnded;
	bool					m_gameWin;
//	AudioPlayer *			m_audioPlayer;
    //QList<QVariant>			m_wavesInfo;
	QList<TowerPosition>	m_towerPositionsList;
	QList<Tower *>			m_towersList;
    QList<SlowingTower *>			m_slowingtowersList;
	QList<WayPoint *>		m_wayPointsList;
	QList<Enemy *>			m_enemyList;
	QList<Bullet *>			m_bulletList;

signals:
    void chooseback();
};

#endif // G1_H
