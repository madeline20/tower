/*#ifndef G2_H
#define G2_H
#include"tower.h"
#include<QList>
#include <QMainWindow>
#include <QImage>
#include <QPainter>
#include<QKeyEvent>
#include<QTimer>
#include <QPushButton>
#include "enemy2.h"
#include"g1.h"
#include"mywindow.h"
#include"slowingtower.h"
class g1;
class g2: public g1//第二关，尚未实现
{
    Q_OBJECT
public:
    explicit g2(QWidget *parent = 0);
    ~g2();
    void getHpDamage(int damage = 1);//减小玩家生命值
  //  void removedEnemy(Enemy *enemy);
    void removedBullet(Bullet *bullet);
    void addBullet(Bullet *bullet);
    void awardGold(int gold);//怪物死亡后，金币上升
    void drawWave(QPainter *painter);
    void drawHP(QPainter *painter);
    void drawPlayerGold(QPainter *painter);
     bool canBuyTower() const;
     void doGameOver();//游戏结束
     QList<Enemy2 *> enemyList() const;//返回怪物List
     void removedEnemy(Enemy2 *enemy);
public slots:
    void gameStart();
    void updateMap();
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);//鼠标点击事件
     friend class   mywindow;
private:
    void loadTowerPositions();
    void addWayPoints();
    bool loadWave();


private:
  //  bool                 m_hasStarted;
    int						m_waves;
    int						m_playerHp;
    int						m_playrGold;
    bool					m_gameEnded;
    bool					m_gameWin;
//	AudioPlayer *			m_audioPlayer;

    QList<TowerPosition>	m_towerPositionsList;
    QList<Tower *>			m_towersList;
    QList<SlowingTower *>			m_slowingtowersList;
    QList<WayPoint *>		m_wayPointsList;
    QList<Enemy2 *>			m_enemyList;
    QList<Bullet *>			m_bulletList;
signals:
    void chooseback();
};
#endif // G2_H*/

