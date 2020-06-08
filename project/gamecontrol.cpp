#include "gamecontrol.h"
#include "config.h"
#include <QKeyEvent>
#include <QSound>


gameControl::gameControl(QGraphicsScene *scene, QObject *parent)
    : QObject(parent),
      scene(scene)
{
    Timer.start(1000/33);
    timerApperEnemy.start(500);
    scene->installEventFilter(this);
    startGame();
}

gameControl::~gameControl()
{
}

void gameControl::startGame()
{
    //设置地图
    bg = new background(*this);
    scene->addItem(bg);

    //设置我的飞机
    myplane = new myPlane(*this);
    myplane->setPos(VIEW_WIDTH/2, 400);
    scene->addItem(myplane);

    //设置Boss
    bos = new boss(*this);
    //bos->setPos(VIEW_WIDTH/2,200);
    scene->addItem(bos);

    bal = new bossball(*this, *bos);
    scene->addItem(bal);

    connect(&Timer,SIGNAL(timeout()),scene,SLOT(advance()));
    connect(&timerApperEnemy,SIGNAL(timeout()),this,SLOT(addEnemy()));

}
void gameControl::addEnemy()
{
    int x = qrand() % 300 - 150 + VIEW_WIDTH/2, y = 1;
    Enemy *tempEnemy = new Enemy(*this);
    tempEnemy->setPos(x, y);
    scene->addItem(tempEnemy);
}

void gameControl::removeItem(QGraphicsItem &item)
{
    scene->removeItem(&item);
}

void gameControl::myPlaneShoot(const QPointF &p, int speed)
{
    bullet = new myPlaneBullet(*this);
    bullet->setPos(p);
    bullet->setSpeed(speed);
    scene->addItem(bullet);

    QSound *sound = new QSound(SOUND_SHOOT, this);
    sound->setLoops(1);
    sound->play();
    //QSound::play(SOUND_SHOOT);
}

bool gameControl::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::KeyPress) {
        handleKeyPressed((QKeyEvent *)event);
        return true;
    }
    if(event->type() == QEvent::KeyRelease) {
        handleKeyReleased((QKeyEvent *)event);
        return true;
    }
    return QObject::eventFilter(watched, event);//既不是按压也不是释放就一直等待
}

void gameControl::handleKeyPressed(QKeyEvent *event)
{
    if(!event->isAutoRepeat())
    {
        int key = event->key();
        if(key == Qt::Key_D)   myplane->setSpeedX(10);//右
        if(key == Qt::Key_A)   myplane->setSpeedX(-10);//左
        if(key == Qt::Key_W)   myplane->setSpeedY(-10);//上
        if(key == Qt::Key_S)   myplane->setSpeedY(10);//下
        if(key == Qt::Key_Space)    myplane->setFireStatue(true);
    }
}

void gameControl::handleKeyReleased(QKeyEvent *event)
{
    if(!event->isAutoRepeat())
    {
        int key = event->key();
        //释放保持不动
        if(key == Qt::Key_D)   myplane->setSpeedX(0);
        if(key == Qt::Key_A)   myplane->setSpeedX(0);
        if(key == Qt::Key_W)   myplane->setSpeedY(0);
        if(key == Qt::Key_S)   myplane->setSpeedY(0);
        if(key == Qt::Key_Space)    myplane->setFireStatue(false);
    }
}
/*在按下一个键不放后，会发生：

    1.触发keypressevent()，此时isautorepeat()返回false；

    2.set isautorepeat(),使其返回值为true;//指set一系列函数

    3.触发keyreleaseevent()，此时isautorepeat()返回true；

重复触发keypressevent（），keyreleaseevent（），isautorepeat（）都返回ture；

若放开这个键，则发生：

    4.触发keypressevent()，此时isautorepeat()返回true；

    5. set isautorepeat(),使其返回值为false;

    6. 触发keyreleaseevent()，此时isautorepeat()返回false；

停止。*/
