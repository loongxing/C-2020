#include "gamecontrol.h"
#include "config.h"
#include <QKeyEvent>
#include <QSound>
#include <QDebug>
#include <QDateTime>
#include <QMessageBox>
#include <QMediaPlaylist>
#include <QMediaPlayerControl>
#include <QProcess>
#include <QDir>

gameControl::gameControl(QGraphicsScene *scene, QObject *parent)
    : QObject(parent),
      scene(scene)
{
    //游戏配置
    attackStyle = 1;
    level = 1;
    grade = 1;
    if(gameStyle == 3){
        myPlaneFullLife = 1e7+10;
    }
    else{
        myPlaneFullLife = 20*(4-difficulty);
    }

    //定时器启动
    bos = new boss(*this);
    Timer.start(GAME_RATE);//游戏刷新频率的计时器
    bulletTimer.start(BULLET_TIMER);//技能恢复的计时器
    timerAddEnemy.start(ENEMY_TIMER/(difficulty+2));//敌机的出现频率
    addLifeTimer.start(LIFE_TIMER);//血块掉落
    circleTimer.setInterval(CIRCLE_KEEP);
    addCircleTimer.setInterval(CIRCLE_RECODE);
    disappearWingPlaneTimer.setInterval(DISAPPEARWINGMAN);
    addSkillTwoTimer.setInterval(ADDSKILLTWO_TIMER);

    scene->installEventFilter(this);
    startGame();
}

gameControl::~gameControl()
{
}

void gameControl::startGame()
{
    waringCount = 0;
    flag = true;
    sum=0;
    bossBallShootBook = false;
    circleTimerBook = false;
    addCircleTimerBook = false;
    disappearWingPlaneBook = false;
    addSkillTwoTimerBook = false;
    addBossBook1=addBossBook2=false;
    finalAttack = 0;
    //设置音乐
    if(music == 1){
        player.setParent(this);
        QMediaPlaylist * list = new QMediaPlaylist(this);   //音乐列表
        list->addMedia(QUrl("qrc:/music/res/bg.wav"));
        list->setCurrentIndex(0);
        list->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);   //单曲循环
        player.setPlaylist(list);  //播放器得到列表
        player.play(); //播放
    }

    //设置地图
    bg = new background(*this);
    scene->addItem(bg);

    //设置我的飞机
    myplane = new myPlane(*this);
    myplane->setPos(VIEW_WIDTH/2, 400);
    scene->addItem(myplane);
    myplane->setZValue(1);

    //设置Boss
//    bos = new boss(*this);
    //bos->setPos(VIEW_WIDTH/2,200);
//    scene->addItem(bos);

    //设置boss子弹
//    bal = new bossball(*this, *bos);
//    scene->addItem(bal);
    addBossTimer.start(20000);
    addBossTimer.setSingleShot(true);
    connect(&addBossTimer,SIGNAL(timeout()),this,SLOT(addBoss()));

    //设置积分显示
    font = new QFont();    //初始化字体
    font->setBold(true);//字体粗体
    font->setPixelSize(20);//字体大小

    score = 0;
    text = new QGraphicsTextItem();
    text->setDefaultTextColor(Qt::yellow);//设置文本颜色
    text->setFont(*font);//设置字体
    text->setPos(10, 10);//设置位置
    scene->addItem(text);
    updataScore(0);//先把初始的分数显示出来

    skillText = new QGraphicsTextItem();
    skillText = new QGraphicsTextItem();
    skillText->setDefaultTextColor(Qt::yellow);//设置文本颜色
    skillText->setFont(*font);//设置字体
    skillText->setPos(10, VIEW_HEIGHT-30);//设置位置
    scene->addItem(skillText);
    updataSkilltext();

    connect(&Timer,SIGNAL(timeout()),scene,SLOT(advance()));
    connect(&bulletTimer,SIGNAL(timeout()),this,SLOT(addSkillOne()));
    connect(&timerAddEnemy,SIGNAL(timeout()),this,SLOT(addEnemy()));
    connect(&addLifeTimer,SIGNAL(timeout()),this,SLOT(addLife()));
    connect(&circleTimer,SIGNAL(timeout()),this,SLOT(removeCircle()));
    connect(&addCircleTimer,SIGNAL(timeout()),this,SLOT(setCircle()));
    connect(&disappearWingPlaneTimer,SIGNAL(timeout()),this,SLOT(disappearWingPlane()));
    connect(&addSkillTwoTimer,SIGNAL(timeout()),this,SLOT(addSkillTwo()));
}

void gameControl::gameOver()
{
    //取消关联定时器
    disconnect(&Timer,SIGNAL(timeout()),scene,SLOT(advance()));
    disconnect(&bulletTimer,SIGNAL(timeout()),this,SLOT(addSkillOne()));
    disconnect(&timerAddEnemy,SIGNAL(timeout()),this,SLOT(addEnemy()));
    disconnect(&addLifeTimer,SIGNAL(timeout()),this,SLOT(addLife()));
    disconnect(&circleTimer,SIGNAL(timeout()),this,SLOT(removeCircle()));
    disconnect(&addCircleTimer,SIGNAL(timeout()),this,SLOT(setCircle()));
    disconnect(&disappearWingPlaneTimer,SIGNAL(timeout()),this,SLOT(disappearWingPlane()));
    disconnect(&addSkillTwoTimer,SIGNAL(timeout()),this,SLOT(addSkillTwo()));
    disconnect(&addBossTimer,SIGNAL(timeout()),this,SLOT(addBoss()));

    //音乐暂停
    if(music == 1)   player.pause();

    //显示游戏结束页面
    if(gameStyle != 3){
        Rank rank;
        node q;
        q.name = playerName;
        q.score = QString::number(score);
        q.time = QDateTime::currentDateTime().toString("yyyy.MM.dd..hh:mm.ap");
        q.model = (gameStyle == 1?"冒险模式":"无尽模式");
        if(gameStyle == 1 && level == 7){
            QMessageBox::question(0, tr("分数"), tr("你成功了,你的得分是:%1,排名是:%2,模式:%3").arg(score).arg(rank.getRank(q)).arg(gameStyle == 1?"冒险模式":"无尽模式"), QMessageBox::Yes);//弹出信息提示框
        }
        else{
            QMessageBox::question(0, tr("分数"), tr("再接再厉,你的得分是:%1,排名是:%2,模式:%3").arg(score).arg(rank.getRank(q)).arg(gameStyle == 1?"冒险模式":"无尽模式"), QMessageBox::Yes);//弹出信息提示框
        }
        rank.add(q);
        emit exitApp();
        GO.show();
    }
}

void gameControl::removeItem(QGraphicsItem &item)
{
    if(item.scene())
        scene->removeItem(&item);
}

void gameControl::myPlaneShoot(const QPointF &p, int speed)
{
    bullet = new myPlaneBullet(*this);
    bullet->setPos(p);
    bullet->setSpeed(speed);
    scene->addItem(bullet);
    if(music == 1){
        QSound *sound = new QSound(SOUND_SHOOT, this);
        sound->setLoops(1);
        sound->play();
    }
}

void gameControl::addCircle()
{
    myplane->setCircleStatue(false);
    updataSkilltext();

    cir = new circle(*this);
    cir->setParentItem(myplane);
    //scene->addItem(cir);

    circleTimer.start();
    circleTimer.setSingleShot(true);

    addCircleTimer.start();
    addCircleTimer.setSingleShot(true);

}

bool gameControl::isInView(const QPointF &p)
{
    return (p.x()<VIEW_WIDTH+200 && p.x()>-200) && (p.y()<VIEW_HEIGHT+200 && p.y() >-200);
}

void gameControl::startCollision(const QPointF &p)
{
    collision* col = new collision(*this);
    col->setPos(p);
    scene->addItem(col);
    col->setZValue(2);
    if(music == 1){
        QSound *sound = new QSound(SOUND_BOMB, this);
        sound->setLoops(1);
        sound->play();
    }
}

bool gameControl::updataScore(int s)
{
    if(s>0) sum+=s;
    if(sum>20000){
        addFinalAttack(1);
        sum-=20000;
    }
    text->setZValue(1);
    score+=s;
    if(score>=0){
        grade = score/10000+1;
        text->setPlainText(tr("得分:%1  等级:%2  生命:%3 关卡:%4").arg(score).arg(grade).arg(myplane->getLife()).arg(level));
        return true;
    }
    else{
        score-=s;
        grade = score/10000+1;
        text->setPlainText(tr("得分:%1  等级:%2  生命:%3").arg(score).arg(grade).arg(myplane->getLife()));
        return false;
    }
}

QPointF gameControl::getMyPlanePos()
{
    return myplane->pos();
}

void gameControl::shootStop()
{
    bossBallShoot.stop();
}

void gameControl::shootWingBullet(const QPointF &p)
{
    wingBullet=new WingmanBullet(*this);
    wingBullet->setPos(p.x()+wing1->boundingRect().width(),p.y());
    scene->addItem(wingBullet);
}

void gameControl::updataSkilltext()
{
    skillText->setZValue(1);
    skillText->setPlainText(tr("护盾 X %1 火花 X %2 僚机 X %3").arg(myplane->getCircleStatue()? 1: 0).arg(myplane->getBUlletRain()).arg(myplane->getWingPlane()));
}

void gameControl::addWingPlane()
{
    wing1=new WingMan(*this);
    scene->addItem(wing1);
    wing1->setParentItem(myplane);

    wing2=new WingMan(*this);
    scene->addItem(wing2);
    wing2->setParentItem(myplane);
    wing2->setPos(QPointF(-wing1->boundingRect().width()*2.0,0));

    disappearWingPlaneTimer.start();
    disappearWingPlaneTimer.setSingleShot(true);
}

void gameControl::bossShootNew(int a)
{
    balNew=new bossBallNew(*this);
    balNew->setPos(QPointF(bos->boss_x+bos->pix.width()/2,bos->boss_y+bos->pix.height()));
    balNew->setAngle(a);
    scene->addItem(balNew);
}

void gameControl::disappearWingPlane()
{
    scene->removeItem(wing1);
    scene->removeItem(wing2);
    addSkillTwoTimer.start();
    addSkillTwoTimer.setSingleShot(true);
}

void gameControl::addWaring(int alh)
{
    if(alh==0){
        scene->setForegroundBrush(Qt::NoBrush);
    }
    else{
        QLinearGradient linearGrad(QPointF(0, 0), QPointF(VIEW_WIDTH, VIEW_HEIGHT));
        linearGrad.setColorAt(0, QColor(255, 0, 0, alh));
        linearGrad.setColorAt(0.6, QColor(0, 0, 0, 0));
        linearGrad.setColorAt(1,QColor(255,0,0,alh));
        QBrush brush(linearGrad);
        scene->setForegroundBrush(brush);
    }
}

void gameControl::addText(QPointF p,int s)
{
    font = new QFont();    //初始化字体
    font->setBold(true);//字体粗体
    font->setPixelSize(20);//字体大小

    scoreText = new QGraphicsTextItem();
    scoreText->setDefaultTextColor(Qt::yellow);//设置文本颜色
    scoreText->setFont(*font);//设置字体
    scoreText->setPos(p);//设置位置
    textList.push_back(scoreText);
    scene->addItem(scoreText);

    scoreText->setZValue(1);
    if(s == 1){
        scoreText->setPlainText(tr("终极大招收集中......"));
    }
    else if(s == 2){
        scoreText->setPlainText(tr("护盾技能正在冷却"));
    }
    else if(s == 3){
        scoreText->setPlainText(tr("弹幕雨技能正在冷却"));
    }
    else if(s == 4){
        scoreText->setPlainText(tr("僚机技能正在冷却"));
    }
    else{
        scoreText->setPlainText(tr("%1").arg(s));
    }
    QTimer::singleShot(500,this,[&](){
        scoreText = textList.takeFirst();
        scene->removeItem(scoreText);
    });
}

void gameControl::addLaser()
{
    la = new laser(*this);
    scene->addItem(la);
}

void gameControl::addFinalAttack(int s)
{
    finalAttack+=s;
}

void gameControl::addEquipment(QPointF pos)
{
    equip =new equipment(*this);
    equip->setPos(pos);
    scene->addItem(equip);
}

void gameControl::shootFan(int i)
{
    Fan= new fan(*this);
    Fan->setPos(QPointF(bos->boss_x+bos->pix.width()/2,bos->boss_y+bos->pix.height()));
    Fan->setAngle(i);
    scene->addItem(Fan);
}

void gameControl::hanldeBossLife(int s)
{
    bos->bossLifeChange(s);
}

int gameControl::getMyPlaneHurt()
{
    return myplane->getHurt();
}

void gameControl::addEnemy()
{
    int x = qrand() % 300 - 150 + VIEW_WIDTH/2, y = 1;
    tempEnemy = new Enemy(*this);
    tempEnemy->setPos(x, y);
    scene->addItem(tempEnemy);
}

void gameControl::shootBall(QPointF pos)
{
    tempBall = new EnemyBall(*this);
    tempBall->setPos(pos);
    tempBall->setDir();
    scene->addItem(tempBall);
}

void gameControl::addBulletRain()
{
    if(myplane->getBUlletRain()>0){
        if(music == 1){
            QSound *sound = new QSound(SOUND_SHOOT, this);
            sound->setLoops(1);
            sound->play();
        }
        for(int i=1;i<15;i++){
            BR = new bulletRain(*this,i);
            BR->setPos(myplane->pos());
            scene->addItem(BR);
        }
    }
}

void gameControl::addSkillTwo()
{
    myplane->addWingPlane(1);
}

void gameControl::addBoss()
{
    bos->NewBoss();
    scene->addItem(bos);
    bos->bossAddStop();
    shootStop();
}

void gameControl::shoot(int i)
{
    bal = new bossball(*this);
    bal->setPos(QPointF(bos->boss_x+bos->pix.width()/2,bos->boss_y+bos->pix.height()));
    bal->setAngle(i);
    scene->addItem(bal);
}

void gameControl::addLife()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    life = new lifeAdd(*this);
    life->setPos(QPoint((rand()%7+1)*100%VIEW_WIDTH,0));
    scene->addItem(life);
}

void gameControl::addLife(QPointF pos)
{
    life = new lifeAdd(*this);
    life->setPos(pos);
    scene->addItem(life);
}

void gameControl::handleBomb(QPointF p)
{
    collision* col = new collision(*this);
    col->setPos(p);
    col->setScale(3.0);
    scene->addItem(col);
    if(music){
        QSound *sound = new QSound(SOUND_BOMB, this);
        sound->setLoops(1);
        sound->play();
    }

    //处理爆炸区域
    QList<QGraphicsItem *> list = scene->items(QRectF(p.x()-60,p.y()-60,120,120), Qt::IntersectsItemShape);
    foreach(QGraphicsItem *item, list){
        auto t = item->data(GI_type);
        if(t == GT_enemy){
            updataScore(100+qrand()%20);
            startCollision(item->pos());
            if(qrand()%100 < 20)    addLife(item->pos());
            removeItem(*item);
            return;
        }
        if(t == GT_enemyBall || t == GT_bossBall){
            removeItem(*item);
            return;
        }
        if(t== GT_boss){
            this->bos->bossLifeChange(-1);
            return;
        }
    }
}

void gameControl::appProgress()
{
    flag = !flag;
    if(!flag){
        //scene->setForegroundBrush(QColor(0,0,0,127));
        Timer.stop();
        bulletTimer.stop();
        timerAddEnemy.stop();
        addLifeTimer.stop();
        if(bossBallShoot.isActive()){
            bossBallShootBook = true;
            bossBallShoot.stop();
        }
        if(circleTimer.isActive()){
              circleTimer.stop();
              circleTimerBook = true;
        }
        if(addCircleTimer.isActive()){
            addCircleTimer.stop();
            addCircleTimerBook = true;
        }
        if(addSkillTwoTimer.isActive()){
            addSkillTwoTimer.stop();
            addSkillTwoTimerBook = true;
        }
        if(disappearWingPlaneTimer.isActive()){
            disappearWingPlaneTimer.stop();
            disappearWingPlaneBook = true;
        }
        if(addBossTimer.isActive()){
            addBossBook1 = true;
            addBossTimer.stop();
        }
        if(bos->bossIsActive()){
            bos->bossAddStop();
            addBossBook2 = true;
        }
        Rank rank;
        node q;
        q.name = "玩家";
        q.score = QString::number(score);
        q.time = QDateTime::currentDateTime().toString("yyyy.MM.dd..hh:mm.ap");
        if(gameStyle == 3)  q.model = "无敌模式";
        else {
            q.model = (gameStyle == 1 ? "冒险模式":"无尽模式");
        }
        //QMessageBox::question(0, tr("提示"), tr("游戏暂停,游戏目前得分是：%1,排名是： %2").arg(score).arg(rank.getRank(q)), QMessageBox::Yes);//弹出信息提示框
        QIcon* Icon = new QIcon(GAME_ICON);
        QMessageBox mess(QMessageBox::Information, tr("提示"), tr("游戏暂停,游戏目前得分是：%1,排名是： %2").arg(score).arg(rank.getRank(q)));
        mess.setWindowIcon(*Icon);
        QPushButton *buttonContinue = (mess.addButton(tr("继续游戏"), QMessageBox::AcceptRole));
        QPushButton *buttonNew = (mess.addButton(tr("重新开始"), QMessageBox::YesRole));
        QPushButton *buttonQuit = (mess.addButton(tr("退出游戏"), QMessageBox::RejectRole));
        mess.exec();
        if(mess.clickedButton()==buttonNew)
        {
            QString program = QApplication::applicationFilePath();
            QStringList arguments = QApplication::arguments();
            QString workingDirectory = QDir::currentPath();
            QProcess::startDetached(program, arguments, workingDirectory);
            QApplication::exit();
        }
        else if(mess.clickedButton()==buttonQuit)
        {
            emit exitApp();
        }
        else if(mess.clickedButton()==buttonContinue)
        {
            appProgress();
        }
    }
    else{
        //scene->setForegroundBrush(Qt::NoBrush);
        Timer.start();//游戏刷新频率的计时器
        bulletTimer.start();//技能恢复的计时器
        timerAddEnemy.start();//敌机的出现频率
        addLifeTimer.start();//血块掉落
        if(bossBallShootBook){
            bossBallShoot.start();
            bossBallShootBook = false;
        }
        if(circleTimerBook){
              circleTimer.start();
              circleTimerBook = false;
        }
        if( addCircleTimerBook){
            addCircleTimer.start();
            addCircleTimerBook = false;
        }
        if(addSkillTwoTimerBook){
            addSkillTwoTimer.start();
            addSkillTwoTimerBook = false;
        }
        if(addBossBook1){
            addBossTimer.start();
            addBossBook1 = false;
        }
        if(addBossBook2){
            bos->bossStart();
            addBossBook2 = false;
        }
    }
}

void gameControl::removeCircle()
{
    scene->removeItem(cir);
}

void gameControl::setCircle()
{
    myplane->setCircleStatue(true);
    updataSkilltext();
}

void gameControl::addSkillOne()
{
    myplane->addBulletRain(1);
    updataSkilltext();
}

bool gameControl::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::KeyPress) {
        handleKeyPressed((QKeyEvent *)event);
        return true;
    }
    if(event->type() == QEvent::KeyRelease) {
        handleKeyReleased((QKeyEvent *)event);
        return true;
    }
    return QObject::eventFilter(watched, event);//既不是按压也不是释放就一直等待
}

void gameControl::handleKeyPressed(QKeyEvent *event)
{
    if(!event->isAutoRepeat())
    {
        int key = event->key();
        //flag为真即为游戏进行，为假即为暂停，暂停游戏时，不可接受按键
        if(flag){
            if(key == Qt::Key_D)   myplane->setSpeedX(10);//右
            if(key == Qt::Key_A)   myplane->setSpeedX(-10);//左
            if(key == Qt::Key_W)   myplane->setSpeedY(-10);//上
            if(key == Qt::Key_S)   myplane->setSpeedY(10);//下
            if(key == Qt::Key_Space)    myplane->setFireStatue(true);//发射子弹
            if(key == Qt::Key_J){
                if(myplane->getCircleStatue() && updataScore(-500)){
                    addCircle();
                }
                else{
                    //qDebug()<<"护盾技能正在冷却";
                    addText(QPointF(VIEW_WIDTH/2-70,VIEW_HEIGHT/2),2);
                }
            }
            if(key == Qt::Key_K){
                if(myplane->getBUlletRain()>0 && updataScore(-1000)){
                    myplane->addBulletRain(-1);
                    updataSkilltext();
                    for(int i=1;i<4;i++)
                        QTimer::singleShot(100*i,this,SLOT(addBulletRain()));
                }
                else{
                    //qDebug()<<"弹幕雨技能正在冷却";
                    addText(QPointF(VIEW_WIDTH/2-70,VIEW_HEIGHT/2),3);
                }
            }
            if(key == Qt::Key_L){
                if(myplane->getWingPlane()>0 && updataScore(-500)){
                    myplane->addWingPlane(-1);
                    updataSkilltext();
                    addWingPlane();
                }
                else{
                    //qDebug()<<"僚机技能正在冷却中";
                    addText(QPointF(VIEW_WIDTH/2-70,VIEW_HEIGHT/2),4);
                }
            }
            if(key == Qt::Key_H){
                if(finalAttack > 0){
                    addFinalAttack(-1);
                    addLaser();
                }
                else{
                    //qDebug()<<"终极技能正在收集中";
                    addText(QPointF(VIEW_WIDTH/2-70,VIEW_HEIGHT/2),1);
                }
            }
            if(key == Qt::Key_Escape){
                appProgress();
            }
        }
    }
}

void gameControl::handleKeyReleased(QKeyEvent *event)
{
    if(!event->isAutoRepeat())
    {
        int key = event->key();
        //释放保持不动
        if(flag){
            if(key == Qt::Key_D)   myplane->setSpeedX(0);
            if(key == Qt::Key_A)   myplane->setSpeedX(0);
            if(key == Qt::Key_W)   myplane->setSpeedY(0);
            if(key == Qt::Key_S)   myplane->setSpeedY(0);
            if(key == Qt::Key_Space)    myplane->setFireStatue(false);
        }
    }
}
/*在按下一个键不放后，会发生：

    1.触发keypressevent()，此时isautorepeat()返回false；

    2.set isautorepeat(),使其返回值为true;//指set一系列函数

    3.触发keyreleaseevent()，此时isautorepeat()返回true；

重复触发keypressevent（），keyreleaseevent（），isautorepeat（）都返回ture；

若放开这个键，则发生：

    4.触发keypressevent()，此时isautorepeat()返回true；

    5. set isautorepeat(),使其返回值为false;

    6. 触发keyreleaseevent()，此时isautorepeat()返回false；

停止。*/
