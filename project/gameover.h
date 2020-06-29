#ifndef GAMEOVER_H
#define GAMEOVER_H
#include<QDialog>
#include"ui_GameOver.h"
#include"config.h"
#include <QPixmap>
#include <QComboBox>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QBitmap>
namespace Ui {
class GameOver;
}

class GameOver:public QDialog
{
Q_OBJECT;
public:
    explicit GameOver(QWidget *parent=0);
    ~GameOver();
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
private slots:

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::GameOver *ui;
    QPoint dragPosition;
    QPixmap *pix;
     int score;
};

#endif // GAMEOVER_H
