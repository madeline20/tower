#include "g1.h"
#include "mybutton.h"
#include "waypoint.h"
#include "enemy.h"
#include "bullet.h"
#include "slowingtower.h"
#include <QPainter>
#include <QMouseEvent>
#include <QtGlobal>
#include <QMessageBox>
#include <QTimer>
#include <QXmlStreamReader>
#include <QtDebug>
#include<QMediaPlayer>
#include<Qmediaplaylist>
static const int TowerCost = 500;

g1::g1(int guanqia, QWidget *parent)
	: QMainWindow(parent)
    , m_waves(0)
    , m_playerHp(4)
    ,  m_playrGold(2000)
	, m_gameEnded(false)
	, m_gameWin(false)
    ,m_guanqia(guanqia)
    {
    //ui->setupUi(this);
    this->setFixedSize(1600,1200);
    loadTowerPositions();
    addWayPoints();
    MyButton *backbtn=new MyButton(":/image/back.jpg");//返回按钮
    backbtn->setParent(this);//设置父类
    backbtn->move(40,40);
    connect(backbtn,&MyButton::clicked,this,[=](){
    emit chooseback();
 });

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(10);

	// 设置300ms后游戏启动
    //QTimer::singleShot(300, this, SLOT(gameStart()));
}

g1::~g1()
{
    //delete ui;
}

void g1::loadTowerPositions()
{

    if(m_guanqia==1){
     QPoint pos[]=
    {
        QPoint(150, 50),
        QPoint(280, 110),
        QPoint(400, 180),

        QPoint(500, 20),
        QPoint(700, 100),
        QPoint(750, 250),
        QPoint(780, 380),
        QPoint(1400, 700),
        QPoint(500, 250),
        QPoint(520, 360),
        QPoint(550, 480),
        QPoint(600, 700),

        QPoint(800, 650),
        QPoint(1000, 850),
        QPoint(1150, 850),
        QPoint(1280, 850),
        QPoint(700, 800),
        QPoint(1400, 700),


        QPoint(900, 750)
    };
     int len	= sizeof(pos) / sizeof(pos[0]);
     for (int i = 0; i < len; ++i)
       m_towerPositionsList.push_back(pos[i]);
    }
    else if (m_guanqia==2){
         QPoint pos[] =
        {
            QPoint(50, 700),
            QPoint(50, 450),
            QPoint(250, 700),
            QPoint(250, 450),
            QPoint(450, 700),
            QPoint(600, 650),
            QPoint(760, 650),
            QPoint(900, 800),
            QPoint(1000, 700),
            QPoint(1150, 600),
            QPoint(1300, 640),
            QPoint(1400, 650),
            QPoint(1500, 650),
            QPoint(900, 550),
             QPoint(1300, 450),
             QPoint(1150, 450),
             QPoint(1450, 450),
             QPoint(450, 450)

        };
         int len	= sizeof(pos) / sizeof(pos[0]);
         for (int i = 0; i < len; ++i)
           m_towerPositionsList.push_back(pos[i]);
    }

}
void g1::paintEvent(QPaintEvent *)
{
    if (m_gameEnded || m_gameWin)
    {
        QString text = m_gameEnded ? "YOU LOST!!!" : "YOU WIN!!!";
        QPainter painter(this);
        painter.setPen(QPen(Qt::red));
        painter.drawText(rect(), Qt::AlignCenter, text);
        return;
    }
    if(m_guanqia==1){
    QPixmap cachePix(":/image/tu1.jpg");
    QPainter cachePainter(&cachePix);

    foreach (const TowerPosition &towerPos, m_towerPositionsList)
        towerPos.draw(&cachePainter);

    foreach (const Tower *tower, m_towersList)
        tower->draw(&cachePainter);

    foreach (const SlowingTower *tower, m_slowingtowersList)
        tower->draw(&cachePainter);

    foreach (const WayPoint *wayPoint, m_wayPointsList)
        wayPoint->draw(&cachePainter);

    foreach (const Enemy *enemy, m_enemyList)
        enemy->draw(&cachePainter);

    foreach (const Bullet *bullet, m_bulletList)
        bullet->draw(&cachePainter);

    drawWave(&cachePainter);
    drawHP(&cachePainter);
    drawPlayerGold(&cachePainter);

    QPainter painter(this);
    painter.drawPixmap(0, 0, cachePix);

    }
    else if(m_guanqia==2){
        QPixmap cachePix(":/image/tu2.jpg");
        QPainter cachePainter(&cachePix);

        foreach (const TowerPosition &towerPos, m_towerPositionsList)
            towerPos.draw(&cachePainter);

        foreach (const Tower *tower, m_towersList)
            tower->draw(&cachePainter);

        foreach (const SlowingTower *tower, m_slowingtowersList)
            tower->draw(&cachePainter);

        foreach (const WayPoint *wayPoint, m_wayPointsList)
            wayPoint->draw(&cachePainter);

        foreach (const Enemy *enemy, m_enemyList)
            enemy->draw(&cachePainter);

        foreach (const Bullet *bullet, m_bulletList)
            bullet->draw(&cachePainter);

        drawWave(&cachePainter);
        drawHP(&cachePainter);
        drawPlayerGold(&cachePainter);

        QPainter painter(this);
        painter.drawPixmap(0, 0, cachePix);

    }
}

void g1::mousePressEvent(QMouseEvent *event)//鼠标点击事件
{
    QPoint pressPos = event->pos();//即鼠标点击的点
    auto it = m_towerPositionsList.begin();//这个list里边保存建塔点
    while (it != m_towerPositionsList.end())
    {
        if (canBuyTower() && it->containPoint(pressPos) && !it->hasTower())//三个条件，可以买塔，建塔点里包含鼠标点击的点，建塔没有塔
        {
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

bool g1::canBuyTower() const
{
    if (m_playrGold >= TowerCost)
        return true;
    return false;
}

void g1::drawWave(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    painter->drawText(QRect(400, 5, 100, 25), QString("WAVE : %1").arg(m_waves + 1));
}

void g1::drawHP(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    painter->drawText(QRect(30, 5, 100, 25), QString("HP : %1").arg(m_playerHp));
}

void g1::drawPlayerGold(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    painter->drawText(QRect(200, 5, 200, 25), QString("GOLD : %1").arg(m_playrGold));
}

void g1::doGameOver()
{
    if (!m_gameEnded)
    {
        m_gameEnded = true;
        // 此处应该切换场景到结束场景
        // 暂时以打印替代,见paintEvent处理
    }
}

void g1::awardGold(int gold)
{
    m_playrGold += gold;
    update();
}

void g1::addWayPoints()
{
    if(m_guanqia==1){
    WayPoint *wayPoint1 = new WayPoint(QPoint(1600, 800));
    m_wayPointsList.push_back(wayPoint1);

    WayPoint *wayPoint2 = new WayPoint(QPoint(1550, 850));
    m_wayPointsList.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);

    WayPoint *wayPoint3 = new WayPoint(QPoint(1450, 950));
    m_wayPointsList.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint4 = new WayPoint(QPoint(1000, 950));
    m_wayPointsList.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);

    WayPoint *wayPoint5 = new WayPoint(QPoint(800, 850));
    m_wayPointsList.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    WayPoint *wayPoint6 = new WayPoint(QPoint(700, 600));
    m_wayPointsList.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);

    WayPoint *wayPoint7 = new WayPoint(QPoint(650, 200));
    m_wayPointsList.push_back(wayPoint7);
    wayPoint7->setNextWayPoint(wayPoint6);

    WayPoint *wayPoint8 = new WayPoint(QPoint(200, 0));
    m_wayPointsList.push_back(wayPoint8);
    wayPoint8->setNextWayPoint(wayPoint7);}
    else if(m_guanqia==2){
        WayPoint *wayPoint1 = new WayPoint(QPoint(1600, 600));
        m_wayPointsList.push_back(wayPoint1);

        WayPoint *wayPoint2 = new WayPoint(QPoint(1400, 580));
        m_wayPointsList.push_back(wayPoint2);
        wayPoint2->setNextWayPoint(wayPoint1);

        WayPoint *wayPoint3 = new WayPoint(QPoint(1200, 560));
        m_wayPointsList.push_back(wayPoint3);
        wayPoint3->setNextWayPoint(wayPoint2);

        WayPoint *wayPoint4 = new WayPoint(QPoint(900, 700));
        m_wayPointsList.push_back(wayPoint4);
        wayPoint4->setNextWayPoint(wayPoint3);

        WayPoint *wayPoint5 = new WayPoint(QPoint(800, 850));
        m_wayPointsList.push_back(wayPoint5);
        wayPoint5->setNextWayPoint(wayPoint4);

        WayPoint *wayPoint6 = new WayPoint(QPoint(700, 900));
        m_wayPointsList.push_back(wayPoint6);
        wayPoint6->setNextWayPoint(wayPoint5);

        WayPoint *wayPoint7 = new WayPoint(QPoint(500, 600));
        m_wayPointsList.push_back(wayPoint7);
        wayPoint7->setNextWayPoint(wayPoint6);

        WayPoint *wayPoint8 = new WayPoint(QPoint(0, 600));
        m_wayPointsList.push_back(wayPoint8);
        wayPoint8->setNextWayPoint(wayPoint7);//以上是第一条路线



    }
    }



void g1::getHpDamage(int damage/* = 1*/)
{
//	m_audioPlayer->playSound(LifeLoseSound);
    m_playerHp -= damage;
    if (m_playerHp <= 0)
        doGameOver();
}

void g1::removedEnemy(Enemy *enemy)
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

void g1::removedBullet(Bullet *bullet)
{
	Q_ASSERT(bullet);

	m_bulletList.removeOne(bullet);
	delete bullet;
}

void g1::addBullet(Bullet *bullet)
{
	Q_ASSERT(bullet);

	m_bulletList.push_back(bullet);
}

void g1::updateMap()
{
	foreach (Enemy *enemy, m_enemyList)
		enemy->move();
	foreach (Tower *tower, m_towersList)
		tower->checkEnemyInRange();
	update();
}
/*bool g1::compare2Roads(){
    int towers1=0,towers2=0;//分别表示第一条路，第二条路的塔的数量
    for(int i=0;i<=12;i++){
        if(m_towerPositionsList.at(i).hasTower()){
            towers1++;
        }
    }
    for(int i=13;i<=25;i++){
        if(m_towerPositionsList.at(i).hasTower()){
            towers2++;
        }
    }
    if(towers1<=towers2)
        return true;//第一条路塔数小于第二条
    else
        return false;//第一条路塔数比第二条路多
}*/

bool g1::loadWave()
{
    int enemyStartInterval1[] = { 1000, 3000,5000, 7000};
    int enemyStartInterval2[] = { 1000, 2000,3000, 4000,5000, 5500, 6000,7200,8400};
    int enemyStartInterval3[] = { 1000};
    int enemyStartInterval4[] = { 1000,2000,3000};
    QPixmap pixmap1(":/image/1.png");
    QPixmap pixmap3(":/image/3.png");
    if(m_guanqia==1){
    WayPoint *startWayPoint = m_wayPointsList.back();
    if (m_waves >= 6)
        return false;
    else {
   if( m_waves==0){
    for (int i = 0; i <4; ++i)
    {
        Enemy *enemy = new Enemy(startWayPoint,this);
        m_enemyList.push_back(enemy);
        QTimer::singleShot(enemyStartInterval1[i], enemy, SLOT(doActivate()));
    }}
   else if( m_waves==1){
    for (int i = 0; i <4; ++i)
    {
        Enemy *enemy = new Enemy(startWayPoint,this,pixmap1,(qreal)5,60);
        m_enemyList.push_back(enemy);
        QTimer::singleShot(enemyStartInterval1[i], enemy, SLOT(doActivate()));
    }}
    else if( m_waves==2){
    for (int i = 0; i < 9; ++i)
    {
        Enemy *enemy = new Enemy(startWayPoint, this);
        m_enemyList.push_back(enemy);
        QTimer::singleShot(enemyStartInterval2[i], enemy, SLOT(doActivate()));
    }}
   else if( m_waves==3){
       for (int i = 0; i < 9; ++i)
       {
           Enemy *enemy = new Enemy(startWayPoint, this,pixmap1,(qreal)5,60);
           m_enemyList.push_back(enemy);
           QTimer::singleShot(enemyStartInterval2[i], enemy, SLOT(doActivate()));
       }}
   else if( m_waves==4){
       for (int i = 0; i <1; ++i)
       {
           Enemy *enemy = new Enemy(startWayPoint, this,pixmap3,5,260);
           m_enemyList.push_back(enemy);
           QTimer::singleShot(enemyStartInterval3[i], enemy, SLOT(doActivate()));
       }}
   else if( m_waves==5){
       for (int i = 0; i < 3; ++i)
       {
          Enemy *enemy = new Enemy(startWayPoint, this,pixmap3,5,260);
           m_enemyList.push_back(enemy);
           QTimer::singleShot(enemyStartInterval4[i], enemy, SLOT(doActivate()));
       }}
    return true;}}//以上为第一关的设计
    else if(m_guanqia==2){
    WayPoint *startWayPoint = m_wayPointsList.back();
    if (m_waves >= 6)
        return false;
    else {
   if( m_waves==0){
    for (int i = 0; i <4; ++i)
    {
        Enemy *enemy = new Enemy(startWayPoint,this);
        m_enemyList.push_back(enemy);
        QTimer::singleShot(enemyStartInterval1[i], enemy, SLOT(doActivate()));
    }}
   else if( m_waves==1){
    for (int i = 0; i <4; ++i)
    {
        Enemy *enemy = new Enemy(startWayPoint,this,pixmap1,(qreal)5,60);
        m_enemyList.push_back(enemy);
        QTimer::singleShot(enemyStartInterval1[i], enemy, SLOT(doActivate()));
    }}
    else if( m_waves==2){
    for (int i = 0; i < 9; ++i)
    {
        Enemy *enemy = new Enemy(startWayPoint, this);
        m_enemyList.push_back(enemy);
        QTimer::singleShot(enemyStartInterval2[i], enemy, SLOT(doActivate()));
    }}
   else if( m_waves==3){
       for (int i = 0; i < 9; ++i)
       {
           Enemy *enemy = new Enemy(startWayPoint, this,pixmap1,(qreal)5,60);
           m_enemyList.push_back(enemy);
           QTimer::singleShot(enemyStartInterval2[i], enemy, SLOT(doActivate()));
       }}
   else if( m_waves==4){
       for (int i = 0; i <1; ++i)
       {
           Enemy *enemy = new Enemy(startWayPoint, this,pixmap3,5,260);
           m_enemyList.push_back(enemy);
           QTimer::singleShot(enemyStartInterval3[i], enemy, SLOT(doActivate()));
       }}
   else if( m_waves==5){
       for (int i = 0; i < 3; ++i)
       {
          Enemy *enemy = new Enemy(startWayPoint, this,pixmap3,5,260);
           m_enemyList.push_back(enemy);
           QTimer::singleShot(enemyStartInterval4[i], enemy, SLOT(doActivate()));
       }}
    return true;}}//以上为第一关的设计
}



QList<Enemy *> g1::enemyList() const
{
	return m_enemyList;
}

void g1::gameStart()
{
	loadWave();
    //m_hasStarted=true;
}

