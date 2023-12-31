#include "bgmplayer.h"

BgmPlayer::BgmPlayer(QObject *parent) : QObject(parent)
{
    playList = new QMediaPlaylist(this);
    bgmer = new QMediaPlayer(this);
    playList->setPlaybackMode(QMediaPlaylist::Loop);
}

void BgmPlayer::playBgm(QString bgmPath)
{
    if(!playList->isEmpty())                       //不为空，停止播放，置空
    {
        bgmer->stop();
        playList->clear();
    }
    if(bgmPath == "none")                           //为none,不放bgm
    {
        return;
    }
    playList->addMedia(QUrl::fromLocalFile(bgmPath));   //有确定bgm，放
    bgmer->setPlaylist(playList);
    bgmer->setVolume(mainVolume*bgmVolume/100);
    bgmer->play();
}

void BgmPlayer::setVolume(int v)
{
    bgmer->setVolume(v);
}
