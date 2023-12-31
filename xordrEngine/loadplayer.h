#ifndef LOADPLAYER_H
#define LOADPLAYER_H

#include <QWidget>
#include "newpushbutton.h"
#include "data.h"
#include "savedata.h"
#include <QMap>
#include <QPushButton>
#include <QFile>
#include <QStackedWidget>

class LoadPlayer : public QWidget
{
    Q_OBJECT
    NewPushButton* toMainBtn;
    NewPushButton* toSceneBtn;
    NewPushButton* toSaveBtn;

    QVector<SwitchButton*> vecIndexBtn;

    SaveData* sdata;
    void showData();
    QMap<int,QMap<int,QLabel*>> timeLabel;
    QMap<int,QMap<int,QLabel*>> pixLabel;
    QMap<int,QMap<int,QLabel*>> textLabel;



public:
    explicit LoadPlayer(SaveData*,Data*,QWidget *parent = nullptr);
    bool isFromScene;
    void fromScene(bool);
    SingleData *qLoad();
    void saveDataUpdate(int,int);

signals:
    void toMain();
    void toScene();
    void toSave();
    void loadData(int,int,int,int);

};

#endif // LOADPLAYER_H
