#ifndef CONFIG_H
#define CONFIG_H
#include <QPointF>

extern int myPlaneFullLife;//myplane初始血条
extern int level;//关卡
extern int attackStyle;//攻击方式
extern int difficulty;//难度
extern QString playerName;//玩家姓名
extern QString backgroundPath;//地图名字
extern int gameStyle;//模式
extern int music;//音乐
extern int grade;//等级
extern int hero;//英雄

/*场景配置*/
#define VIEW_WIDTH 500
#define VIEW_HEIGHT 730
#define GAME_ICON ":/image/res/app.ico"
#define GAME_BG ":/image/res/img_bg_level_5.jpg"
#define BG_SPEED 3
#define GAME_RATE 1000/33
#define GAME_RES_PATH "./res.rcc" //rcc文件路径

/*定时器间隔*/
#define BULLET_TIMER 5000
#define ENEMY_TIMER 1500
#define LIFE_TIMER 20000
#define DISAPPEARWINGMAN 15000
#define ADDSKILLTWO_TIMER 5000
#define CIRCLE_RECODE  15000
#define CIRCLE_KEEP  7000

/*音乐资源*/
#define SOUND_BACKGROUND ":/music/res/bg.wav"
#define SOUND_SHOOT ":/music/res/Shoot.wav"
#define SOUND_BOMB ":/music/res/bomb.wav"
#define BOMB_PATH  ":/image/res/bomb-%1.png"   //爆炸资源图片

/*boss配置*/
#define BOSS_PIX ":/image/res/boss_%1.png"
#define BOSSBALL ":/image/res/BossBall1.png"
#define bossBall_speed 3
#define BOSS_RATE 20000
#define BOSS_FAN ":/image/res/sucai-011.png"


/*飞机配置*/
#define MYPLANE ":/image/res/myplane_%1_%2.png"
#define BULLET_SPEED  10
#define MYPLANE_BULLET ":/image/res/bullet_11.png"
#define BULLETRIAN ":/image/res/hero_bullet_7.png"
#define CIRCLE_PIXMAP ":/image/res/circle.png"


/*敌机配置*/
#define ENEMY_PATH ":/image/res/Enemy%1.png"//敌机飞机
#define ENEMY_BALL ":/image/res/Ball1.BMP"

/*僚机配置*/
#define WINGPLANE_BULLET ":/image/res/bullet_12.png"
#define WINGPLANE_PIX ":/image/res/MyPlane.png"

/*物品掉落*/
#define EQUIPMENT ":/image/res/package_2.png"
#define LIFEADD ":/image/res/LifeAdder.png"

/*界面背景*/
#define GameOver_UI_BG ":/image/res/gameover.png"
#define START_UI_BG ":/image/res/LogInBackground.png"

enum gameObjectItem{
    GI_type,
};

enum gameObjectType{
    GT_myplane,//我的飞机
    GT_myplaneBall,//我的飞机子弹
    GT_boss,//boss
    GT_bossBall,//boss子弹
    GT_enemy,//敌机
    GT_enemyBall,//敌机子弹
    GT_wingMan,//僚机本体无敌
    GT_wingManBullet,//僚机子弹
    GT_lifeAdder,//血块
    GT_circle,//护罩
    GT_laser,//激光
    GT_equipment,//武器包
};

#endif // CONFIG_H
