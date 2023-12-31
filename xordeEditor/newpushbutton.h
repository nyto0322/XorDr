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
#include <QPixmap>
#include <QDebug>
#include <QIcon>
#include <QPropertyAnimation>


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
    NewPushButton(QWidget *parent = nullptr);
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);
    void mousePressEvent(QMouseEvent*);
    void setUnlock(bool);
    QString loadError = "";
    QPoint getPos();


    void setNormal(QString);
    void setEnter(QString);
    void setPress(QString);
    void setSound(QString);
    void setPos(QPoint);
    void setSize(QSize);

signals:

};

#endif // NEWPUSHBUTTON_H
