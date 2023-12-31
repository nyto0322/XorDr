#include "choicepushbutton.h"
#include <QDebug>



ChoicePushButton::ChoicePushButton(QString nn,QString nm,QString np,QString ns,QPoint npos,QSize nsize
                                   ,QString te,int ne,QPoint tp,QSize ts,int fd,QString sac)
    :NewPushButton(nn,nm,np,ns,npos,nsize)
    ,text(te)
    ,next(ne)
    ,textPos(tp)
    ,textSize(ts)
    ,fontDelta(fd)
    ,showAfterChapter(sac)

{
    textLabel = new QLabel(this);
    textLabel->setText(text);
    textLabel->setFixedSize(textSize);
    textLabel->setAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
}

ChoicePushButton::ChoicePushButton(NewPushButton n, QString te, int ne, QPoint tp, QSize ts, int fd, QString sac)
    :NewPushButton(n)
    ,text(te)
    ,next(ne)
    ,textPos(tp)
    ,textSize(ts)
    ,fontDelta(fd)
    ,showAfterChapter(sac)

{
    textLabel = new QLabel(this);
    textLabel->setText(text);
    textLabel->setFixedSize(textSize);
    textLabel->setAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
}

QString ChoicePushButton::getText()
{
    return text;
}

QPoint ChoicePushButton::getTextPos()
{
    return textPos;
}

QSize ChoicePushButton::getTextSize()
{
    return textSize;
}

int ChoicePushButton::getNext()
{
    return next;
}

int ChoicePushButton::getfontDelta()
{
    return fontDelta;
}

QString ChoicePushButton::getShowAfterChapter()
{
    return showAfterChapter;
}


