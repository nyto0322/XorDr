#ifndef SAVEPLAYER_H
#define SAVEPLAYER_H

#include <QWidget>
#include "newpushbutton.h"
#include "data.h"
#include "savedata.h"
#include "ui_mainwindow.h"
#include <QMap>
#include <QPushButton>
#include <QByteArray>
#include <QDateTime>
#include <QStackedWidget>
#include <QListWidget>
#include <QListView>

class SavePlayer : public QWidget
{
    Q_OBJECT
    NewPushButton* toSceneBtn;
    NewPushButton* toMainBtn;
    NewPushButton* toLoadBtn;
    SaveData* sdata;
    //void saveData();
    //void showData(SingleData*,QWidget*);
    //void save(SingleData*,int,int);
    QVector<SwitchButton*> vecIndexBtn;
    SingleData* singleData;
    //QPixmap* currentPix;
    //QMap<int,QMap<int,SingleData*>> datamap;
public:
    explicit SavePlayer(SaveData*,Data*,QWidget *parent = nullptr);
    void qSave(int,int,int,int);
    void inputSaveData(int,int,int,int,QPixmap*,QString);
    bool isFromScene;
    void fromScene(bool);


signals:
    void toScene();
    void toMain();
    void toLoad();
    void saveDataUpdate(int,int);

};

#endif // SAVEPLAYER_H
