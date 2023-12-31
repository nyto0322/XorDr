#ifndef CHOICEPUSHBUTTON_H
#define CHOICEPUSHBUTTON_H

#include <QObject>
#include <QWidget>
#include "newpushbutton.h"
#include <QLabel>
#include <QVector>

class ChoicePushButton : public NewPushButton
{
    Q_OBJECT
    QString text;
    int next;
    QPoint textPos;
    QSize textSize;
    int fontDelta;
    QVector<int> showAfterChapter;
public:
    QLabel* textLabel;
    explicit ChoicePushButton(QString,QString,QString,QString,QPoint,QSize,QString,int,QPoint,QSize,int,QVector<int>);
    QPoint getTextPos();
    int getNext();
    int getfontDelta();
    QVector<int> getShowAfterChapter();


signals:

};

#endif // CHOICEPUSHBUTTON_H
