#include "collision.h"
#include "config.h"
#include <math.h>
#include <QPainter>
#include <QDebug>

collision::collision(gameControl &control):
    controller(control)
{
    for(int i=1;i<8;i++){
        QString str = QString(BOMB_PATH).arg(i);
        pixArr.push_back(QPixmap(str));
    }
    idx = 0;
    cnt=0;
    scale = 1.0;
}

QRectF collision::boundingRect() const//每次重绘图片就算这个图没变也会访问
{
    qreal w = pixArr[idx].width(), h = pixArr[idx].height();
    return QRectF(-w/2,-h/2,w,h);
}

void collision::advance(int phase)
{
    if(!phase)  return;
    if(cnt==3){
        cnt=0;
        idx++;
        if(idx>=6){
            controller.removeItem(*this);
        }
    }
    else{
        cnt++;
    }
}

void collision::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);Q_UNUSED(widget);
    if(!pixArr[idx].isNull()){
        painter->save();
        qreal w = pixArr[idx].width(), h = pixArr[idx].height();
        painter->scale(scale,scale);
        painter->drawPixmap(-w/2,-h/2,w,h,pixArr[idx]);
        painter->restore();
    }
}

void collision::setScale(double sc)
{
    scale = sc;
}

