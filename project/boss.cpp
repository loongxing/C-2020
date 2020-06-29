#include"boss.h"
#include "config.h"
#include <QPainter>
#include <QDebug>
#include <QRectF>
#include <QImageReader>
#include <QString>
#include <QPixmap>
#include<QTimer>

boss::boss(gameControl &control):
    controller(control)
{
    setData(GI_type, GT_boss);
    Blood=20+difficulty*(15+level);
    cut=difficulty*(level+5);
    BLOOD=Blood;//方便改血量
    firstBoss=true;

    if(level>=7){
        pix.load(QString(BOSS_PIX).arg(qrand()%6+1));
    }
    else
        pix.load(QString(BOSS_PIX).arg(level));
    gradient = new QLinearGradient(QPoint(-50, -50), QPoint(50, 50));
    gradient->setColorAt(1, Qt::red);

    boss_x=VIEW_WIDTH/2-pix.width()/2;
    boss_y=-pix.height();
    addBos.setInterval(BOSS_RATE);
    QEventLoop::connect(&addBos,SIGNAL(timeout()),&controller,SLOT(addBoss()));//新boss再生
}

QRectF boss::boundingRect() const
{
    return QRectF(boss_x,boss_y,pix.width(),pix.height());
}

void boss::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);
    painter->save();
    painter->drawPixmap(boss_x,boss_y,pix);
    update();
    painter->setBrush(*gradient);//Brush画刷，用于填充颜色
    painter->drawRect(boss_x,boss_y+pix.height(), pix.width()*Blood/BLOOD , 8);
    painter->restore();
}

void boss::advance(int phase)
{
    if(!phase)  return;
//    pix.load(QString(BOSS_PIX).arg(level));
    if(boss_y<=0)
        boss_y+=2;
    srand((unsigned)time(0));
    boss_x+=rand()%5;
    boss_x-=rand()%5;
    if(boss_x>=VIEW_WIDTH-pix.width())
        boss_x=VIEW_WIDTH-pix.width();
    if(boss_x<=0)
        boss_x=0;    

    if(++cut==50)
    {
        if(level<=2)                        //前2个boss只会第一种
            for(int i=0;i<5;i++)
                controller.shoot(-40+20*i);         //第一种扫射
        else if(level<=4)                   //前4个boss会第一、二种
        {
            if(rand()%2==0)
                for(int i=0;i<8;i++)
                    controller.bossShootNew(-110+45*i);     //第二种炸裂
            else if(rand()%2==1)
                for(int i=0;i<5;i++)
                    controller.shoot(-40+20*i);
        }
        else if(rand()%3==0)
            for(int i=0;i<8;i++)
                controller.bossShootNew(-110+45*i);
        else if(rand()%3==1)
            for(int i=0;i<5;i++)
                controller.shoot(-40+20*i);
        else if(rand()%3==2)
            for(int i=0;i<5;i++)
                controller.shootFan(-40+20*i);          //第三种：反射子弹

        cut=difficulty*(level+5);
    }
    handleCollisions();
}


void boss::handleCollisions()
{
    if(Blood <= 0){
        bossDie();
        return;
    }
    QList<QGraphicsItem *> collisions = collidingItems();
    foreach(QGraphicsItem *item, collisions){
        if(item->data(GI_type) == GT_myplaneBall && item->boundingRect() != QRectF(-15,-15,30,30)){
            controller.removeItem(*item);
            controller.startCollision(item->pos());
            Blood+=controller.getMyPlaneHurt();
        }
        if(item->data(GI_type) == GT_myplaneBall && item->boundingRect() == QRectF(-15,-15,30,30)){
            controller.handleBomb(item->pos());
            controller.removeItem(*item);
            Blood+=controller.getMyPlaneHurt();
        }
        if(item->data(GI_type) == GT_wingManBullet){
            controller.removeItem(*item);
            controller.startCollision(item->pos());
            Blood--;
        }
    }
}

void boss::bossAddStop()
{
    addBos.stop();
}

void boss::NewBoss()
{
    Blood=60;
    BLOOD=Blood;
    cut=0;
    firstBoss=true;

    QString str=QString(BOSS_PIX).arg(level);
    pix.load(str);

    boss_x=VIEW_WIDTH/2-pix.width()/2;
    boss_y=-pix.height();

}

void boss::bossStart()
{
    addBos.start();
}

void boss::bossStart(int s)
{
    addBos.start(s);
}

bool boss::bossIsActive()
{
    return addBos.isActive();
}

void boss::bossDie()
{
    level = level + 1;//关卡加一
    if(gameStyle == 1 &&level >= 7){
        controller.gameOver();
    }
    addBos.start();
    addBos.setSingleShot(true);
    controller.removeItem(*this);//老boss清除
    //qDebug()<<"666";
    int s = 1000+qrand()%200;
    controller.updataScore(s);//死亡加分
    controller.addText(pos(),s);//分数显示
    //多次爆炸
    controller.startCollision(QPointF(boss_x+pix.width()/2+10,boss_y+pix.height()/2-62));
    controller.startCollision(QPointF(boss_x+pix.width()/2+20,boss_y+pix.height()/2-15));
    controller.startCollision(QPointF(boss_x+pix.width()/2+50,boss_y+pix.height()/2+11));
    controller.startCollision(QPointF(boss_x+pix.width()/2-14,boss_y+pix.height()/2+53));
    controller.startCollision(QPointF(boss_x+pix.width()/2-64,boss_y+pix.height()/2+14));
    if(level == 2||level == 4|| level == 6) controller.addEquipment(QPoint(boss_x+pix.width()/2,boss_y+pix.height()));
}

void boss::bossLifeChange(int s)
{
    Blood+=s;
}
