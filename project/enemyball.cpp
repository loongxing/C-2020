#include "enemyball.h"
#include "gamecontrol.h"
#include <QPainter>
#include <cmath>

EnemyBall::EnemyBall(gameControl &controller):
    controller(controller)
{
    setData(GI_type, GT_enemyBall);
    pixMap.load(ENEMY_BALL);
    dirx = qrand() % 6 - 3;
}

QRectF EnemyBall::boundingRect() const
{
    int w = pixMap.width(), h = pixMap.height();
    return QRectF(-w/2, -h/2, w, h);
}

void EnemyBall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);
    if(!pixMap.isNull()) {
        painter->save();
        int w = pixMap.width(), h = pixMap.height();
        painter->drawPixmap(QPoint(-w/2, -h/2), pixMap);
        painter->restore();
    }
}

void EnemyBall::advance(int phace)
{
    if(!phace) return;
    moveBy(vector.x() * 10, vector.y() * 10);
    if(!controller.isInView(pos())) controller.removeItem(*this);
}

void EnemyBall::setDir()
{
    vector = controller.getMyPlanePos() - pos();
    vector /= hypot(vector.x(), vector.y());
}
