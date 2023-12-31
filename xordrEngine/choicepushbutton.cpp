#include "choicepushbutton.h"
#include <QDebug>



ChoicePushButton::ChoicePushButton(QString nn,QString nm,QString np,QString ns,QPoint npos,QSize nsize
                                   ,QString te,int ne,QPoint tp,QSize ts,int fd,QVector<int> sac)
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

QPoint ChoicePushButton::getTextPos()
{
    return textPos;
}

int ChoicePushButton::getNext()
{
    return next;
}

int ChoicePushButton::getfontDelta()
{
    return fontDelta;
}

QVector<int> ChoicePushButton::getShowAfterChapter()
{
    return showAfterChapter;
}


