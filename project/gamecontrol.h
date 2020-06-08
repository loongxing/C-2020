#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <QMainWindow>
#include <QObject>
#include <QGraphicsScene>
#include <QTimer>
#include <QKeyEvent>
#include "background.h"
#include "myplane.h"
#include "myplanebullet.h"
#include "boss.h"
#include"enemy.h"
#include "bossball.h"
#include<QPointF>

class background;
class myPlane;
class myPlaneBullet;
class boss;
class bossball;

class gameControl : public QObject
{
    Q_OBJECT

public:
    gameControl(QGraphicsScene *scene, QObject *parent = nullptr);
    ~gameControl();
    void startGame();
    void removeItem(QGraphicsItem &item);
    void myPlaneShoot(const QPointF &p, int speed);
signals:
    void exitApp();
protected:
    bool eventFilter(QObject *watched, QEvent *event);
    void handleKeyPressed(QKeyEvent *event);
    void handleKeyReleased(QKeyEvent *event);
public slots:
    void addEnemy();
private:
    QGraphicsScene *scene;
    background *bg;
    myPlane *myplane;
    QTimer Timer,timerApperEnemy;
    myPlaneBullet *bullet;
    boss *bos;
    bossball *bal;
};
#endif // GAMECONTROL_H
