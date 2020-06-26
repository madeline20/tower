#ifndef BOSS_H
#define BOSS_H
#include"enemy.h"
#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>
class Boss : public Enemy
{
public:
  Boss(WayPoint *startWayPoint, g1 *game, const QPixmap &sprite = QPixmap(":/image/1.png"));
  ~Boss();
  void move();
private:
    bool			m_active;
    int				m_maxHp;
    int				m_currentHp;
    qreal			m_walkingSpeed;
    qreal			m_rotationSprite;

    QPoint			m_pos;
    WayPoint *		m_destinationWayPoint;
    g1 *	m_game;
    QList<Tower *>	m_attackedTowersList;

    const QPixmap	m_sprite;
    static const QSize ms_fixedSize;
};

#endif // BOSS_H
