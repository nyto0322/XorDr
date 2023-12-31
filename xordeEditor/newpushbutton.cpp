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

NewPushButton::NewPushButton(QWidget *parent) :
    QPushButton(parent)
  ,normalImgPath("")
  ,enterImgPath("")
  ,pressImgPath("")
  ,clickSoundPath("")
  ,pos(QPoint(0,0))
  ,size(QSize(0,0))
{
  this->setFixedSize(size);
  this->setStyleSheet("QPushButton{border:0px;}");
  this->setIcon(QPixmap());
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



    QPushButton::mousePressEvent(e);
}

QPoint NewPushButton::getPos()
{
    return pos;
}



void NewPushButton::setNormal(QString s)
{
    normalImgPath = s;
}

void NewPushButton::setEnter(QString s)
{
    enterImgPath = s;
}

void NewPushButton::setPress(QString p)
{
    pressImgPath = p;
}

void NewPushButton::setSound(QString s)
{
    clickSoundPath = s;
}

void NewPushButton::setPos(QPoint p)
{
    pos = p;
}

void NewPushButton::setSize(QSize s)
{
    size = s;
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





