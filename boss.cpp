#include "boss.h"
//#include "enemy2.h"
#include "enemy.h"
#include "waypoint.h"
#include "tower.h"
#include "utility.h"
#include "g1.h"
#include "audioplayer.h"
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QMatrix>
#include <QVector2D>
#include <QtMath>

static const int Health_Bar_Width = 100;

const QSize Boss::ms_fixedSize(100, 100);

    Boss::Boss(WayPoint *startWayPoint, g1 *game, const QPixmap &sprite/* = QPixmap(":/image/1.png")*/)
        :
         m_active(false)
        , m_maxHp(300)
        , m_currentHp(300)
        , m_walkingSpeed(7)
        , m_rotationSprite(0.0)
        , m_pos(startWayPoint->pos())
        , m_destinationWayPoint(startWayPoint->nextWayPoint())
        , m_game(game)
        , m_sprite(sprite)
        ,Enemy(startWayPoint, game, sprite/* = QPixmap(":/image/1.png")*/)
    {
    }
    Boss::~Boss()
    {
        m_attackedTowersList.clear();
        m_destinationWayPoint = NULL;
        m_game = NULL;
    }
    void Boss::move()
    {
        if (!m_active)
            return;

        if (collisionWithCircle(m_pos, 1, m_destinationWayPoint->pos(), 1))
        {
            // 敌人抵达了一个航点
            if (m_destinationWayPoint->nextWayPoint())
            {
                // 还有下一个航点
                m_pos = m_destinationWayPoint->pos();
                m_destinationWayPoint = m_destinationWayPoint->nextWayPoint();
            }
            else
            {
                // 表示进入基地
                m_game->getHpDamage(2);
                m_game->removedEnemy(this);
                return;
            }
        }

        // 还在前往航点的路上
        // 目标航点的坐标
        QPoint targetPoint = m_destinationWayPoint->pos();
        // 未来修改这个可以添加移动状态,加快,减慢,m_walkingSpeed是基准值

        // 向量标准化
        qreal movementSpeed = m_walkingSpeed;
        QVector2D normalized(targetPoint - m_pos);
        normalized.normalize();
        m_pos = m_pos + normalized.toPoint() * movementSpeed;

        // 确定敌人选择方向
        // 默认图片向左,需要修正180度转右
        m_rotationSprite = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) + 180;
    }


