#include "newpushbutton.h"



NewPushButton::NewPushButton(QString normal, QString enter,QString press, QString click,QPoint p, QSize s)
    :normalImgPath(normal)
    ,enterImgPath(enter)
    ,pressImgPath(press)
    ,clickSoundPath(click)
    ,pos(p)
    ,size(s)
{
    QPixmap pix;
    pix.load(this->normalImgPath);
    if(pix.isNull())
    {
        loadError = QString("config_beginButton_normalImgPath加载失败")+=normalImgPath;
    }

    this->setFixedSize(size);
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(QPixmap(pix));
    this->setIconSize(size);
}

NewPushButton::NewPushButton(const NewPushButton & n)
    :normalImgPath(n.normalImgPath)
    ,enterImgPath(n.enterImgPath)
    ,pressImgPath(n.pressImgPath)
    ,clickSoundPath(n.clickSoundPath)
    ,pos(n.pos)
    ,size(n.size)

{
    QPixmap pix;
    pix.load(this->normalImgPath);
    if(pix.isNull())
    {
        loadError = QString("config_beginButton_normalImgPath加载失败")+=normalImgPath;
    }
    this->setFixedSize(size);
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(QPixmap(pix));
    this->setIconSize(size);
}

void NewPushButton::enterEvent(QEvent *)
{
    this->setIcon(QPixmap(enterImgPath));
}

void NewPushButton::leaveEvent(QEvent *)
{
    if(unlock)
    {
        this->setIcon(QIcon());
    }
    else
    {
        this->setIcon(QPixmap(normalImgPath));
    }
}

void NewPushButton::mousePressEvent(QMouseEvent *e)
{
    this->setIcon(QPixmap(pressImgPath));

    QMediaPlayer* player = new QMediaPlayer(this);
    player->setMedia(QUrl::fromLocalFile(this->clickSoundPath));
    player->setVolume(mainVolume*soundVolume/100);
    player->play();


    connect(player,&QMediaPlayer::mediaStatusChanged,this,[=](QMediaPlayer::MediaStatus status){
        if(status == QMediaPlayer::EndOfMedia)
        {
            disconnect(player,&QMediaPlayer::mediaStatusChanged,0,0);
            player->deleteLater();
        }
    },Qt::UniqueConnection);
    QPushButton::mousePressEvent(e);
}

QPoint NewPushButton::getPos()
{
    return pos;
}

void NewPushButton::setUnlock(bool u)
{
    unlock = u;
    if(u)
    {
        this->setIcon(QIcon());
    }
    else
    {
        this->setIcon(QPixmap(this->normalImgPath));
    }
}





