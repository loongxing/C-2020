#ifndef PAUSE_H
#define PAUSE_H
#include<QDialog>
#include"ui_pause.h"
#include"config.h"
#include "gamecontrol.h"
#include <QPixmap>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QBitmap>

class gameControl;

namespace Ui {
class Pause;
}
class Pause:public QDialog
{
    Q_OBJECT;
public:
    explicit Pause(gameControl &control ,QWidget *parent=0);
    ~Pause();
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
private slots:
    void on_continue_2_clicked();
    void on_new_game_clicked();
//    void on_quit_clicked();

private:
    Ui::Pause *ui;
    QPixmap *pix;
    QPoint dragPosition;
    gameControl &controller;
};

#endif // PAUSE_H
