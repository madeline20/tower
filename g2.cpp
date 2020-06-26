/*#include "g1.h"
#include "mybutton.h"
#include "waypoint.h"
#include "enemy2.h"
#include"g2.h"
#include "bullet.h"
//#include "audioplayer.h"
#include "slowingtower.h"
#include <QPainter>
#include <QMouseEvent>
#include <QtGlobal>
#include <QMessageBox>
#include <QTimer>
#include<QObject>
#include <QtDebug>

static const int TowerCost = 500;

g2::g2(QWidget *parent)
    : g1(parent)
    ,m_playerHp(4)
    ,m_playrGold(2000)
    ,m_waves(0)
     ,m_gameEnded(false)
     ,m_gameWin(false)
{
    this->setFixedSize(1440,1080);

    g2::loadTowerPositions();
    g2::addWayPoints();
    MyButton *backbtn=new MyButton(":/image/back.jpg");//返回按钮
    backbtn->setParent(this);//设置父类
    backbtn->move(40,40);
    connect(backbtn,&MyButton::clicked,this,[=](){
    emit chooseback();
 });
    //m_audioPlayer = new AudioPlayer(this);
//	m_audioPlayer->startBGM();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(10);
}

g2::~g2()
{
    //delete ui;
}
void g2::paintEvent(QPaintEvent *)
{
    if (m_gameEnded || m_gameWin)
    {
        QString text = m_gameEnded ? "YOU LOST!!!" : "YOU WIN!!!";
        QPainter painter(this);
        painter.setPen(QPen(Qt::red));
        painter.drawText(rect(), Qt::AlignCenter, text);
        return;
    }

    QPixmap cachePix(":/image/guan2.jpg");
    QPainter cachePainter(&cachePix);

    foreach (const TowerPosition &towerPos, m_towerPositionsList)
        towerPos.draw(&cachePainter);

    foreach (const Tower *tower, m_towersList)
        tower->draw(&cachePainter);

    foreach (const SlowingTower *tower, m_slowingtowersList)
        tower->draw(&cachePainter);

    foreach (const WayPoint *wayPoint, m_wayPointsList)
        wayPoint->draw(&cachePainter);

    foreach (const Enemy2 *enemy, m_enemyList)
        enemy->draw(&cachePainter);

    foreach (const Bullet *bullet, m_bulletList)
        bullet->draw(&cachePainter);

    g2::drawWave(&cachePainter);
    g2::drawHP(&cachePainter);
    g2::drawPlayerGold(&cachePainter);

    QPainter painter(this);
    painter.drawPixmap(0, 0, cachePix);
}
void g2::drawWave(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    painter->drawText(QRect(400, 5, 100, 25), QString("WAVE : %1").arg(m_waves + 1));
}

void g2::drawHP(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    painter->drawText(QRect(30, 5, 100, 25), QString("HP : %1").arg(m_playerHp));
}

void g2::drawPlayerGold(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    painter->drawText(QRect(200, 5, 200, 25), QString("GOLD : %1").arg(m_playrGold));
}
void g2::loadTowerPositions()
{
    QPoint pos[] =
    {
        QPoint(200, 270),
        QPoint(310, 270),
        QPoint(200, 390),
        QPoint(310, 390),
        QPoint(700, 270),
        QPoint(850, 270),
        QPoint(1000, 270),
        QPoint(1150, 270),
        QPoint(700, 390),
        QPoint(700, 50),
        QPoint(850, 50),
        QPoint(1000, 50),
        QPoint(420, 50),
        QPoint(200, 620),
        QPoint(310, 620),
        QPoint(200, 740),
        QPoint(310, 740),
        QPoint(700, 620),
        QPoint(850, 620),
        QPoint(1000, 620),
        QPoint(1150, 620),
        QPoint(700, 740),
        QPoint(700, 930),
        QPoint(850, 930),
        QPoint(1000, 930),
        QPoint(420, 930)
    };
    int len	= sizeof(pos) / sizeof(pos[0]);
    for (int i = 0; i < len; ++i)
      m_towerPositionsList.push_back(pos[i]);
}
void g2::addWayPoints()
{
    /*WayPoint *wayPoint1 = new WayPoint(QPoint(1600, 400));
    m_wayPointsList.push_back(wayPoint1);

    WayPoint *wayPoint2 = new WayPoint(QPoint(1250, 400));
    m_wayPointsList.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);

    WayPoint *wayPoint3 = new WayPoint(QPoint(1250, 650));
    m_wayPointsList.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint4 = new WayPoint(QPoint(800, 650));
    m_wayPointsList.push_back(wayPoint4);
    //wayPoint4->setNextWayPoint(wayPoint3);

    WayPoint *wayPoint5 = new WayPoint(QPoint(800, 300));
    m_wayPointsList.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    WayPoint *wayPoint6 = new WayPoint(QPoint(250, 300));
    m_wayPointsList.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);

    WayPoint *wayPoint7 = new WayPoint(QPoint(250, 700));
    m_wayPointsList.push_back(wayPoint7);
    wayPoint7->setNextWayPoint(wayPoint6);

    WayPoint *wayPoint8 = new WayPoint(QPoint(0, 700));
    m_wayPointsList.push_back(wayPoint8);
    wayPoint8->setNextWayPoint(wayPoint7);

}
void g2::gameStart()
{
    g2::loadWave();
    //m_hasStarted=true;
}
bool g2::loadWave()
{
    WayPoint *startWayPoint = m_wayPointsList.back();
    int enemyStartInterval1[] = { 1000, 3000,5000, 7000};
    int enemyStartInterval2[] = { 1000, 2000,3000, 4000,5000, 5500, 6000,7200,8400};
    int enemyStartInterval3[] = { 1000};
    int enemyStartInterval4[] = { 1000,2000,3000};
    QPixmap pixmap1(":/image/1.png");
    QPixmap pixmap3(":/image/3.png");
    if (m_waves >= 6)
        return false;
    else {
   if( m_waves==0){
    for (int i = 0; i <4; ++i)
    {
        Enemy2 *enemy = new Enemy2(startWayPoint,this);
        m_enemyList.push_back(enemy);
        QTimer::singleShot(enemyStartInterval1[i], enemy, SLOT(doActivate()));
    }}
   else if( m_waves==1){
    for (int i = 0; i <4; ++i)
    {
        Enemy2 *enemy = new Enemy2(startWayPoint,this,pixmap1,(qreal)5,70);
        m_enemyList.push_back(enemy);
        QTimer::singleShot(enemyStartInterval1[i], enemy, SLOT(doActivate()));
    }}
    else if( m_waves==2){
    for (int i = 0; i < 9; ++i)
    {
        Enemy2 *enemy = new Enemy2(startWayPoint, this);
        m_enemyList.push_back(enemy);
        QTimer::singleShot(enemyStartInterval2[i], enemy, SLOT(doActivate()));
    }}
   else if( m_waves==3){
       for (int i = 0; i < 9; ++i)
       {
           Enemy2 *enemy = new Enemy2(startWayPoint, this,pixmap1,(qreal)5,70);
           m_enemyList.push_back(enemy);
           QTimer::singleShot(enemyStartInterval2[i], enemy, SLOT(doActivate()));
       }}
   else if( m_waves==4){
       for (int i = 0; i <1; ++i)
       {
           Enemy2 *enemy = new Enemy2(startWayPoint, this,pixmap3,5,300);
           m_enemyList.push_back(enemy);
           QTimer::singleShot(enemyStartInterval3[i], enemy, SLOT(doActivate()));
       }}
   else if( m_waves==5){
       for (int i = 0; i < 3; ++i)
       {
          Enemy2 *enemy = new Enemy2(startWayPoint, this,pixmap3,5,300);
           m_enemyList.push_back(enemy);
           QTimer::singleShot(enemyStartInterval4[i], enemy, SLOT(doActivate()));
       }}
    return true;}
}
void g2::updateMap()
{
    foreach (Enemy2 *enemy, m_enemyList)
        enemy->move();
    foreach (Tower *tower, m_towersList)
        tower->checkEnemyInRange();
    update();
}
void g2::mousePressEvent(QMouseEvent *event)//鼠标点击事件
{
    QPoint pressPos = event->pos();//即鼠标点击的点
    auto it = m_towerPositionsList.begin();//这个list里边保存建塔点
    while (it != m_towerPositionsList.end())
    {
        if (canBuyTower() && it->containPoint(pressPos) && !it->hasTower())//三个条件，可以买塔，建塔点里包含鼠标点击的点，建塔没有塔
        {
            //m_audioPlayer->playSound(TowerPlaceSound);
            m_playrGold -= TowerCost;
            it->setHasTower();
         if(event->button()==Qt::LeftButton){//左键点击，建其中一种塔
            Tower *tower = new Tower(it->centerPos(), this);
            m_towersList.push_back(tower);
            update();
            break;}
         else{//右键点击，建另一种塔
             SlowingTower*tower=new SlowingTower(it->centerPos(), this);
              m_slowingtowersList.push_back(tower);
              update();
              break;
         }
        }
       else if ( it->containPoint(pressPos) && it->hasTower())//两个条件，建塔点含有鼠标点击的点，建塔点里有塔
        {
            if(event->button() == Qt::RightButton){//右键拆塔
            foreach (Tower *tower, m_towersList) {
                if(it->containPoint(tower->getpos())) {
                    it->setHasnotTower();
                    m_towersList.removeOne(tower);
                    m_playrGold += tower->level()*TowerCost/2;
                    delete(tower);
                }}
            foreach (SlowingTower *tower, m_slowingtowersList) {
                    if(it->containPoint(tower-> getpos())) {
                        it->setHasnotTower();
                        m_slowingtowersList.removeOne(tower);
                          m_playrGold += tower->level()*TowerCost/2;
                        delete(tower);
                    }
                break;
            }
            }//拆塔操作结束
//此处要实现左键升级塔操作
     if(event->button() == Qt::LeftButton){
         foreach (Tower *tower, m_towersList) {
             if(it->containPoint(tower->getpos())&&m_playrGold>=TowerCost&&tower->level()<=2) {
                 if(tower-> level()==1)
                     tower->levelup1();
                 else if(tower->level()==2)
                         tower->levelup2();
                 m_playrGold-=TowerCost;
             }}
         foreach (SlowingTower *tower, m_slowingtowersList) {
             if(it->containPoint(tower->getpos())&&m_playrGold>=TowerCost&&tower->level()<=2) {
                 if(tower-> level()==1)
                     tower->levelup1();
                 else if(tower->level()==2)
                         tower->levelup2();
                 m_playrGold-=TowerCost;
             }}
     }
            update();
            break;
        }

        ++it;
    }
}
bool g2::canBuyTower() const
{
    if (m_playrGold >= TowerCost)
        return true;
    return false;
}
void g2::doGameOver()
{
    if (!m_gameEnded)
    {
        m_gameEnded = true;
        // 此处应该切换场景到结束场景
        // 暂时以打印替代,见paintEvent处理
    }
}

void g2::awardGold(int gold)
{
    m_playrGold += gold;
    update();
}

/*AudioPlayer *g2::audioPlayer() const
{
    return m_audioPlayer;
}

void g2::getHpDamage(int damage/* = 1)
{
//	m_audioPlayer->playSound(LifeLoseSound);
    m_playerHp -= damage;
    if (m_playerHp <= 0)
        doGameOver();
}

void g2::removedEnemy(Enemy2 *enemy)
{
    Q_ASSERT(enemy);

    m_enemyList.removeOne(enemy);

    delete enemy;

    if (m_enemyList.empty())
    {
        ++m_waves;
        if (!loadWave())
        {
            m_gameWin = true;
            // 游戏胜利转到游戏胜利场景
            // 这里暂时以打印处理
        }
    }
}

void g2::removedBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.removeOne(bullet);
    delete bullet;
}

void g2::addBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.push_back(bullet);
}
QList<Enemy2 *> g2::enemyList() const
{
    return m_enemyList;
}*/
