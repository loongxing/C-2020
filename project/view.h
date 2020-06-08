#ifndef VIEW_H
#define VIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QIcon>
#include <QSound>
#include <QGraphicsScene>
#include "gamecontrol.h"

class view : public QGraphicsView
{
    Q_OBJECT
public:
    explicit view(QWidget *parent = nullptr);
private:
    QIcon *Icon;
    QSound *Sound;
    QGraphicsScene *scene;
    gameControl *control;

signals:

};

#endif // VIEW_H
