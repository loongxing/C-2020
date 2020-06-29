#ifndef VIEW_H
#define VIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QIcon>
#include <QGraphicsScene>
#include "gamecontrol.h"

class view : public QGraphicsView
{
    Q_OBJECT
public:
    explicit view(QWidget *parent = nullptr);
private:
    QIcon *Icon;
    QGraphicsScene *scene;
    gameControl *control;

signals:

};

#endif // VIEW_H
