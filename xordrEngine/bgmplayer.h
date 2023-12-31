#ifndef BGMPLAYER_H
#define BGMPLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "saveconfig.h"


class BgmPlayer : public QObject
{
    Q_OBJECT
    QMediaPlaylist* playList;
    QMediaPlayer* bgmer;

public:
    explicit BgmPlayer(QObject *parent = nullptr);
    void playBgm(QString);
    void setVolume(int);

signals:

};

#endif // BGMPLAYER_H
