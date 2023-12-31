#ifndef CONFIGPLAYER_H
#define CONFIGPLAYER_H

#include <QWidget>
#include "newpushbutton.h"
#include "data.h"
#include <QPushButton>
#include "saveconfig.h"
#include <QSlider>
#include <QDebug>


class ConfigPlayer : public QWidget
{
    Q_OBJECT
    NewPushButton* toMainBtn;
    NewPushButton* toSceneBtn;
public:
    explicit ConfigPlayer(Data*,QWidget *parent = nullptr);

    //改变数据后写文件并且更改全局变量

    void isFromScene(bool);

signals:
    void toMain();
    void toScene();

};

#endif // CONFIGPLAYER_H
