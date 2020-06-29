#include "myplane.h"
#include "config.h"
#include <QPainter>

myPlane::myPlane(gameControl &control):
    controller(control)
{
    idx=3;
    setData(GI_type,GT_myplane);
    pix.load(QString(MYPLANE).arg(hero).arg(idx));
    pic.load(":/image/res/Fire.png");

    speedX = 0;
    speedY = 0;
    isFiring = 0;

    circleStatue = true;
    life = myPlaneFullLife;

    bulletRain = 3;
    tempCount = 0;
    flag = 0;
    wingPlane = 1;
    hurt = -1;
    book = 1;

    //血条渐变
    gradient = new QLinearGradient(QPoint(-50, -50), QPoint(50, 50));//渐变色
    gradient->setColorAt(0, Qt::red);
    gradient->setColorAt(0.2, Qt::yellow);
    gradient->setColorAt(0.7, Qt::blue);
    gradient->setColorAt(1, Qt::green);
}

QRectF myPlane::boundingRect() const
{
    //注意中心点是图片中央
    qreal w = pix.width()*0.6, h = pix.height()*0.6;
    return QRectF(-w/2, -h/2, w, h);
}

void myPlane::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);
    if(!pix.isNull()) {
        painter->save();//保存Qpainter的状态
        int w = pix.width(), h = pix.height();

        //飞机出现
        painter->scale(0.8,0.8);
        painter->drawPixmap(QPoint(-w/2, -h/2), pix);
        painter->drawPixmap(QPoint(-pic.width()/2,h-pic.height()),pic);

        //血条出现
        painter->setBrush(*gradient);//Brush画刷，用于填充颜色

        //血条成比例
        painter->drawRect(-w/2, -h/2 - 10, qMin(w*life/myPlaneFullLife, w), 5);
        //painter->drawRect(-w/2, -h/2 - 10, w , 5);
        painter->restore();//通常与save配套使用，用于恢复成保存的状态
    }

}

void myPlane::advance(int phase)
{
    if(!phase)  return;
    setPos(pos().x()+speedX,pos().y()+speedY);
    if(pos().x() < pix.width()/2) setPos(pix.width()/2, pos().y());
    if(pos().x() > VIEW_WIDTH-pix.width()/2) setPos(VIEW_WIDTH-pix.width()/2, pos().y());
    if(pos().y() < pix.height()/2) setPos(pos().x(), pix.height()/2);
    if(pos().y() > VIEW_HEIGHT-pix.height()/2) setPos(pos().x(), VIEW_HEIGHT-pix.height()/2);

    pix.load(QString(MYPLANE).arg(hero).arg(idx));

    if(isFiring){
        if(isFiring % 7 ==  1)  fire(BULLET_SPEED);//取余保证长按发射键不会高次数发射子弹
        isFiring++;
    }

    hurt = -1-grade/3;

    handleCollision();

    //设置血量警告
    if(life < 5){
        book=0;
        tempCount=(tempCount+1)%85;
        if(tempCount<=42){
            controller.addWaring(tempCount*3);
        }
        else{
            controller.addWaring((84-tempCount)*3);
        }
    }
    else if(life >= 5 && book==0){
        book=1;
        controller.addWaring(0);
    }
}

void myPlane::setSpeedX(int x)
{
    speedX = x;
    if(x>0){
        idx++;
        if(idx>5){
            idx=5;
        }
    }
    else if(x<0){
        idx--;
        if(idx<=0)  idx=1;
    }
    else if(x==0)    idx=3;
}

void myPlane::setSpeedY(int y)
{
    speedY = y;
}

void myPlane::setFireStatue(bool statue)
{
    if(isFiring ==0 && statue){
        isFiring = 1;
    }
    else if(isFiring > 0 && !statue){
        isFiring = 0;
    }
}

void myPlane::fire(int speed)
{
    int x=pos().x(),y=pos().y()-pix.height()/2;
    if(attackStyle == 1){
        controller.myPlaneShoot(QPointF(x,y),speed);
    }
    else if(attackStyle == 2){
        controller.myPlaneShoot(QPointF(x-20,y),speed+5);
        controller.myPlaneShoot(QPointF(x+20,y),speed+5);
    }
    else if(attackStyle == 3){
        controller.myPlaneShoot(QPointF(x,y),speed+10);
    }
}

void myPlane::handleCollision()
{
    QList<QGraphicsItem *> collisions = collidingItems();
    foreach(QGraphicsItem *item, collisions){
        if(item->data(GI_type) == GT_boss){
            //处理爆炸
            controller.startCollision(pos());
            //处理血量,处理血量要注意血量小于等于零的情况
            handleLife(-1);
            //后期可以加上命数
            return;
        }
        if(item->data(GI_type) == GT_enemy){
            controller.removeItem(*item);
            controller.startCollision(pos());
            handleLife(-1);
            return;
        }
        if(item->data(GI_type) == GT_bossBall){
            controller.removeItem(*item);
            controller.startCollision(pos());
            handleLife(-1);
            return;
        }
        if(item->data(GI_type) == GT_enemyBall){
            controller.removeItem(*item);
            controller.startCollision(pos());
            handleLife(-1);
            return;
        }
        if(item->data(GI_type) == GT_lifeAdder){
            controller.removeItem(*item);
            if(life<myPlaneFullLife){
                handleLife(1);
            }
            return;
        }
        if(item->data(GI_type) == GT_equipment){
            attackStyle+=1;
            if(attackStyle > 3) attackStyle=3;
            controller.removeItem(*item);
            return;
        }
    }
}

void myPlane::setCircleStatue(bool s)
{
    circleStatue = s;
}

bool myPlane::getCircleStatue()
{
    return circleStatue;
}

void myPlane::addBulletRain(int val)
{
    bulletRain+=val;
    if(bulletRain<0)    bulletRain=0;
    if(bulletRain>3)    bulletRain=3;
}

int myPlane::getBUlletRain()
{
    return bulletRain;
}

void myPlane::addWingPlane(int s)
{
    wingPlane += s;
    if(wingPlane<0) wingPlane=0;
    if(wingPlane>1) wingPlane=1;
}

int myPlane::getWingPlane()
{
    return wingPlane;
}

void myPlane::handleLife(int s)
{
    life += s;
    if(life<=0 && flag == 0){
        //处理游戏结束事件
        flag=1;
        controller.gameOver();
    }
    if(life>myPlaneFullLife){
        life = myPlaneFullLife;//防止血量溢出
    }
    controller.updataScore(0);
}

int myPlane::getLife()
{
    return life;
}

int myPlane::getHurt()
{
    return hurt;
}

