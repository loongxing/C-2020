#include "lifeadd.h"
#include "gamecontrol.h"
#include <QPainter>


lifeAdd::lifeAdd(gameControl &control):
    controller(control)
{
    setData(GI_type,GT_lifeAdder);
    pixMap.load(":/image/res/LifeAdder.png");
}

QRectF lifeAdd::boundingRect() const
{
    int w = pixMap.width(), h = pixMap.height();
    return QRectF(-w/2, -h/2, w, h);
}

void lifeAdd::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);
    if(!pixMap.isNull()) {
        painter->save();
        int w = pixMap.width(), h = pixMap.height();
        painter->drawPixmap(QPoint(-w/2, -h/2), pixMap);
        //qDebug()<<"-w/2 -h/2"<<-w/2<<-h/2;
        painter->restore();
    }
}

void lifeAdd::advance(int phace)
{
    if(!phace) return;
    moveBy(0, 12);
    if(!controller.isInView(pos())){
        controller.removeItem(*this);
    }
}
