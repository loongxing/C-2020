#include "bulletrain.h"
#include "config.h"
#include <QPainter>
#include <QPointF>

bulletRain::bulletRain(gameControl &control, int num):
    number(num),
    controller(control)
{
    setData(GI_type, GT_myplaneBall);
    pix.load(BULLETRIAN);
    speed = 15;
}

QRectF bulletRain::boundingRect() const
{
    qreal w = pix.width(), h = pix.height();
    return QRectF(-w/2,-h/2,w,h);
}

void bulletRain::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);Q_UNUSED(widget);
    if(!pix.isNull()){
        painter->save();
        painter->rotate(PEI/8*(number<=7? number:15-number));
        qreal w = pix.width(), h = pix.height();
        painter->drawPixmap(QPointF(-w/2,-h/2),pix);
        painter->restore();
    }
}

void bulletRain::advance(int phase)
{
    if(!phase) return;
    moveBy(speed*cos(PEI+PEI/15*number),speed*sin(PEI+PEI/15*number));
    if(!controller.isInView(pos())){
        controller.removeItem(*this);
    }
}

void bulletRain::setSpeed(int s)
{
    speed = s;
}

