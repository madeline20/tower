#include "slowingtower.h"
#include "g1.h"
#include "utility.h"
#include <QPainter>
#include <QColor>
#include <QTimer>
#include <QVector2D>
#include <QtMath>
#include "enemy.h"
const QSize SlowingTower::ms_fixedSize(100, 100);
SlowingTower::SlowingTower(QPoint pos, g1 *game, const QPixmap &sprite/* = QPixmap(":/image/tower.png"*/) :
        m_attackRange(420)
      ,  m_pos(pos)
      , m_sprite(sprite)
      ,m_game(game)
      ,m_slowingrate(0.55)
      ,m_level(1)
    {
    this-> m_Timer = new QTimer(this);
    connect(m_Timer, SIGNAL(timeout()), this, SLOT(chooseEnemyforAttack));
    m_Timer->start(10);
    }
SlowingTower::~SlowingTower()
{
    delete m_Timer;
    m_Timer = NULL;
}
void SlowingTower::draw(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::blue);
    // 绘制攻击范围

    painter->drawEllipse(m_pos, m_attackRange, m_attackRange);

    // 绘制偏转坐标,由中心+偏移=左上
    static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);
    // 绘制炮塔并选择炮塔
    painter->translate(m_pos);
    painter->drawPixmap(offsetPoint, m_sprite);
    painter->restore();
}
void SlowingTower::chooseEnemyforAttack(){
    QList<Enemy *> enemyList = m_game->enemyList();
    foreach (Enemy *enemy, enemyList)
    {
        if (collisionWithCircle(m_pos, m_attackRange, enemy->pos(), 1))
        {
            if(m_slowingrate>enemy->m_slowedrate)
            enemy->getSlowed(m_slowingrate);

        }
        else if(!collisionWithCircle(m_pos, m_attackRange, enemy->pos(), 1)){
            for(int i=0;i<m_chosenEnemyList.size();i++){
                if(m_chosenEnemyList.at(i)==enemy){
                    m_chosenEnemyList.removeOne(enemy);
                    enemy->m_slowedrate=0;
                }
            }
        }
    }
}
QPoint SlowingTower::getpos() const{
    return  m_pos;
}
void SlowingTower::levelup1(){
    m_level++;
    m_attackRange=480;
    m_slowingrate=0.7;
}
void SlowingTower::levelup2(){
    m_level++;
    m_slowingrate=0.85;
    m_attackRange=520;
}
int SlowingTower::level(){
    return m_level;
}
