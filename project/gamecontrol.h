#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <QMainWindow>
#include <QObject>
#include <QGraphicsScene>
#include <QTimer>
#include <QKeyEvent>
#include <QFont>
#include <QSound>
#include <QMediaPlayer>
#include <QImage>
#include "background.h"
#include "myplane.h"
#include "myplanebullet.h"
#include "boss.h"
#include "bossball.h"
#include "circle.h"
#include "bulletrain.h"
#include "collision.h"
#include "rank.h"
#include "enemy.h"
#include "enemyball.h"
#include "wingman.h"
#include "wingmanbullet.h"
#include "lifeadd.h"
#include "bossballnew.h"
#include "laser.h"
#include "gameover.h"
#include"fan.h"
#include"equipment.h"

class background;
class myPlane;
class myPlaneBullet;
class boss;
class bossball;
class circle;
class bulletRain;
class collision;
class Rank;
class Enemy;
class EnemyBall;
class WingMan;
class WingmanBullet;
class lifeAdd;
class bossBallNew;
class laser;
class GameOver;
class fan;
class equipment;

class gameControl : public QObject
{
    Q_OBJECT

public:
    gameControl(QGraphicsScene *scene, QObject *parent = nullptr);
    ~gameControl();
    void startGame();
    void gameOver();
    void removeItem(QGraphicsItem &item);
    void myPlaneShoot(const QPointF &p, int speed);
    void addCircle();
    bool isInView(const QPointF &p);
    void startCollision(const QPointF &p);
    bool updataScore(int s);//更新分数
    QPointF getMyPlanePos();//得到飞机位置
    void shootStop();//boss子弹停止
    void shootWingBullet(const QPointF &p);//僚机子弹发射
    void updataSkilltext();
    void addWingPlane();
    void bossShootNew(int a);
    void addLife(QPointF);
    void handleBomb(QPointF);
    void appProgress();
    void addText(QPointF p,int s);
    void addLaser();
    void addFinalAttack(int s);
    void addEquipment(QPointF);
    void shootFan(int);
    void hanldeBossLife(int s);
    int getMyPlaneHurt();
//    QImage loadImage(QString url);
signals:
    void exitApp();
public slots:
    void addEnemy();
    void shootBall(QPointF pos);
    void removeCircle();
    void setCircle();
    void addSkillOne();
    void addBulletRain();
    void addSkillTwo();//僚机技能
    //void endCollision();
    void addBoss();//杰哥
    void shoot(int);
    void addLife();
    void disappearWingPlane();
    void addWaring(int alh);
protected:
    bool eventFilter(QObject *watched, QEvent *event);
    void handleKeyPressed(QKeyEvent *event);
    void handleKeyReleased(QKeyEvent *event);
private:
    QGraphicsScene *scene;
    background *bg;
    myPlane *myplane;
    QTimer Timer,bulletTimer,timerAddEnemy,bossBallShoot,addLifeTimer,circleTimer,addCircleTimer,addSkillTwoTimer,disappearWingPlaneTimer,addBossTimer;
    myPlaneBullet *bullet;
    boss *bos;
    bossBallNew *balNew;
    bossball *bal;
    circle *cir;
    bulletRain *BR;
    fan *Fan;//飞镖
    equipment *equip;//工具包
    GameOver GO;
    QList<collision*> collisions;
    QList<QGraphicsTextItem*> textList;
    QGraphicsTextItem *text,*skillText,*scoreText;
    QFont *font;
    Enemy *tempEnemy;//敌机
    EnemyBall *tempBall;//敌机子弹
    WingMan *wing1,*wing2;//僚机
    WingmanBullet *wingBullet;//僚机子弹
    lifeAdd *life;//血块
    laser *la;
    QSound *Sound;//音乐
    QMediaPlayer player;//音乐列表
    int score,waringCount,sum,finalAttack;//积分系统
    bool flag,bossBallShootBook,circleTimerBook,addCircleTimerBook,addSkillTwoTimerBook,disappearWingPlaneBook,addBossBook1,addBossBook2;
};
#endif // GAMECONTROL_H
