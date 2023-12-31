#ifndef NEWPUSHBUTTON_H
#define NEWPUSHBUTTON_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QMouseEvent>
#include <QEvent>
#include <QPoint>
#include <QSize>
#include "saveconfig.h"
#include <QPixmap>
#include <QDebug>
#include <QIcon>
#include <QPropertyAnimation>
#include <QMediaPlayer>

class NewPushButton : public QPushButton
{
    Q_OBJECT
public:
    QString normalImgPath;
    QString enterImgPath;
    QString pressImgPath;
    QString clickSoundPath;
    QPoint pos;
    QSize size;
    bool unlock = false;

public:
    explicit NewPushButton(QString,QString,QString,QString,QPoint,QSize);
    NewPushButton(NewPushButton const &);
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);
    void mousePressEvent(QMouseEvent*);
    void setUnlock(bool);
    QString loadError = "";
    QPoint getPos();


signals:

};

#endif // NEWPUSHBUTTON_H
