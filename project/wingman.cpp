#include "wingman.h"
#include "gamecontrol.h"
#include <QPainter>




WingMan::WingMan(gameControl &control)
    :controller(control)
{
    cnt=0;
    pixMap.load(WINGPLANE_PIX);

}

QRectF WingMan::boundingRect() const
{
    qreal w = pixMap.width(), h = pixMap.height();
    return QRectF(-w/2, -h/2, w, h);
}

void WingMan::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);
    painter->save();
    int w = pixMap.width(), h = pixMap.height();
    painter->drawPixmap(QPoint(w/2,h/2), pixMap);
    update();
    painter->restore();
}

void WingMan::advance(int phace)
{
    if(!phace) return;
    if(++cnt == 15) {
        controller.shootWingBullet(controller.getMyPlanePos()+pos());//100/68是myplane数据、10是微调
        cnt = 0;
    }
}
