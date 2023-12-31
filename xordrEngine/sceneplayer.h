#ifndef SCENEPLAYER_H
#define SCENEPLAYER_H

#include <QWidget>
#include "data.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMouseEvent>
#include "bgmplayer.h"
#include "performplayer.h"
#include <QTimer>
#include "textlabel.h"
#include <QMap>
#include "savedata.h"
#include <QListWidget>
#include "newpushbutton.h"
#include <QVector>
#include <QTimer>
#include <QPixmap>
#include <QButtonGroup>
#include "saveconfig.h"
#include <QListWidget>
#include <QColor>



class ScenePlayer : public QWidget
{
    Q_OBJECT
    Data* data;
    QMap<int,Chapter*> chapterMap;
    int previousChapter = -1;
    int currentChapter;
    int currentSection;
    int nextChapter = -1;
    FrameInfo* nameFrame;
    FrameInfo* textFrame;

    QLabel* nameBackLabel;
    QLabel* textBackLabel;
    QLabel* nameLabel;
    TextLabel* textLabel;



    BgmPlayer* bgmPlayer;
    QWidget* currentCg;
    QMediaPlayer* vocalPlayer;
    PerformPlayer* performPlayer;
    PerformPlayerJr* performPlayer_jr;

    QListWidget* hisList;
    QMap<QListWidgetItem*,SingleData*> itemMap;

    QVector<ChoicePushButton*> vecChoice;


    QTimer* skipPlay;


    SwitchButton* unlockS;
    SwitchButton* autoS;
    SwitchButton* skipS;
    NewPushButton* qsaveB;
    NewPushButton* qloadB;
    NewPushButton* saveB;
    NewPushButton* loadB;
    NewPushButton* previousB;
    NewPushButton* logB;
    NewPushButton* nextB;
    NewPushButton* configB;
    NewPushButton* hideB;
    NewPushButton* homepageB;

    QVector<SwitchButton*> vecToolSwitch;
    QVector<NewPushButton*> vecToolBtn;



    void playDialog();
    void playBgm();
    void playBackground();
    void playChoice();
    void playSound();
    void playVocal();
    void playCG();
    void playPerform();
    void playSpecial();


    bool vocalIsNull;

    bool forbidClickToNext = false;
    bool dialogIsGradual = false;

    bool isSkip = false;
    bool isAuto = false;

    bool isHide = false;
    bool isHistory = false;



    //void caohanshu(int);
    void cancelAutoAndSkip();

    SaveData* sd;




public:
    explicit ScenePlayer(SaveData*,Data*,QWidget *parent = nullptr);
    void playScene(int,int);
    void playNextScene();
    void playRandomScene(int,int,int,int);
    void endScene();



    void mousePressEvent(QMouseEvent *event);

    ~ScenePlayer();

signals:
    void backMain();
    void next();            //让未执行完的独立特效音效隐藏
    void clickMouse();

    void toConfig();
    void toSave(int,int,int,int,QPixmap*,QString);        //发射章节
    void toLoad();

    void qSave(int,int,int,int);
    void qLoad();


    //void isnext();//给performplayer



    //void jrFigureShow();
    //void FigureShow();

};

#endif // SCENEPLAYER_H
