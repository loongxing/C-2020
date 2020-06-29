#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QDialog>
#include"config.h"
#include <QComboBox>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QBitmap>
#include"ui_logindlg.h"
#include <QPixmap>
#include "help.h"

class help;

namespace Ui {
class LogInDlg;
}

class LogInDlg : public QDialog
{
    Q_OBJECT

public:
    explicit LogInDlg(QWidget *parent = 0);
    ~LogInDlg();

    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

private slots:
    void on_Start_clicked();

    void on_Ours_clicked();

    void on_Help_clicked();

    void on_rank_clicked();

private:
    QPoint dragPosition;
    QPixmap *pix;
    Ui::logindlg *ui;
    void saveBackGroundType();
    void saveBackGroundLoop();
    void saveLoadMode();
    void saveDifficulty();
    void savePlayerName();
    void savePlaneType();


};

#endif // LOGINDLG_H
