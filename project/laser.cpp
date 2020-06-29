#include "laser.h"
#include "config.h"
#include <QPainter>

laser::laser(gameControl &control):
    controller(control)
{
    cnt=0;
    idx=0;
    cur=0;
    posx=0;
    scale = 0.2;
    count = 0;
    act=0;
    setData(GI_type,GT_laser);
    pix.load(":/image/res/sucai-laser3.png");
    pic.load(":/image/res/player4-4-1.png");
    gra.load(":/image/res/SuperKiller.png");
}

//矩形框存在问题，需要随激光束的变大而变大
QRectF laser::boundingRect() const
{
    qreal w = pix.width(), h = pix.height();
    if(cur <= VIEW_HEIGHT){
        return QRectF(VIEW_WIDTH/2-w*scale/2,VIEW_HEIGHT-cur,w*scale,5*h);
    }
    else{
        return QRectF(VIEW_WIDTH/2-w*scale/2,0,w*scale,5*h);
    }
}

void laser::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);Q_UNUSED(widget);
    if(!pix.isNull()){
        painter->save();
        qreal w = pix.width(), h = pix.height();
        if(idx <= 3 && idx !=0){
            painter->drawPixmap(VIEW_WIDTH/2-w/2*scale,VIEW_HEIGHT-cur,w*scale,h,pix);
            painter->drawPixmap(VIEW_WIDTH/2-w/2*scale,VIEW_HEIGHT-cur+h,w*scale,h,pix);
            painter->drawPixmap(VIEW_WIDTH/2-w/2*scale,VIEW_HEIGHT-cur+2*h,w*scale,h,pix);
            painter->drawPixmap(VIEW_WIDTH/2-w/2*scale,VIEW_HEIGHT-cur+3*h,w*scale,h,pix);
            painter->drawPixmap(VIEW_WIDTH/2-w/2*scale,VIEW_HEIGHT-cur+4*h,w*scale,h,pix);
        }
        else{
            painter->drawPixmap(VIEW_WIDTH/2-w/2*scale,VIEW_HEIGHT-cur,w*scale,h,pix);
            painter->drawPixmap(VIEW_WIDTH/2-w/2*scale,VIEW_HEIGHT-cur+h,w*scale,h,pix);
            painter->drawPixmap(VIEW_WIDTH/2-w/2*scale,VIEW_HEIGHT-cur+2*h,w*scale,h,pix);
        }
        painter->drawPixmap(VIEW_WIDTH/2-pic.width()/2*scale*3,VIEW_HEIGHT-cur-60,pic.width()*scale*3, pic.height(),pic);
        painter->drawPixmap(VIEW_WIDTH/2-gra.width()/2,VIEW_HEIGHT-posx,gra.width(),gra.height(),gra);
        painter->restore();
    }
}

void laser::advance(int phase)
{
    if(!phase)  return;
    if(idx == 0){
        if(cur == 0){
            posx+=10;
            if(posx >= 360)  idx++;
        }
        else    posx-=10;
        if(posx <=0 && cur>0)   controller.removeItem(*this);
    }
    else{
        cur+=20;
        if(scale<=1.0)  scale+=0.01;
    }
    if(cur >= pix.height()*5 && idx!=4){
        cur-=pix.height();
        if(idx == 1 &&cnt == 0)    idx++;
    }
    else if(cur >= pix.height()*3 && idx==4){
        cur-=pix.height();
    }
    if(idx==1 && cnt>=90 ){
        pix.load(":/image/res/sucai-laser3.png");
        scale -=0.1;
        if(scale <=0){
            scale = 0;
            idx=0;
        }
    }
    if(idx == 2){
        cnt++;
        if(cnt <=8){
            scale+=0.1;
        }
        else if(cnt > 8 && cnt<=28){
            if(cnt==9)    scale=1;
            scale+=0.1;
            pix.load(":/image/res/sucai-laser2.png");
            if(cnt == 28)   idx++;
        }
        else if(cnt >= 80){
            pix.load(":/image/res/sucai-laser2.png");
            scale -= 0.2;
            if(cnt == 90)   idx--;
        }
    }
    if(idx == 3){
        pix.load(":/image/res/sucai-laser1.png");
        cnt++;
        if(cnt <= 48){
            scale+=0.1;
            if(cnt == 48)   idx++;
        }
        else{
            if(cnt == 71)   scale = 4.1;
            else{
                scale-=0.2;
            }
            if(cnt >= 80)   idx--;
        }
    }
    if(idx == 4){
        pix.load(":/image/res/SuperLaser.png");
        scale =1.0;
        cnt++;
        if(cnt >= 70)   idx--;
    }

    handleCollision();
}

void laser::handleCollision()
{
    QList<QGraphicsItem *> collisions = collidingItems();
    foreach(QGraphicsItem *item, collisions){
        auto t = item->data(GI_type);
        if(t== GT_enemyBall || t==GT_bossBall){
            controller.removeItem(*item);
            controller.startCollision(item->pos());
            return;
        }
        if(t == GT_enemy){
            controller.removeItem(*item);
            controller.startCollision(item->pos());
            int s = 100+qrand()%20;
            controller.updataScore(s);
            controller.addText(item->pos(),s);
            return;
        }
        //记得处理伤害
        //分数显示
        //积分累加
        if(t == GT_boss){
            act++;
            if(act == 7){
                act=0;
                controller.hanldeBossLife(-3);
            }
            return;
        }
    }
}

