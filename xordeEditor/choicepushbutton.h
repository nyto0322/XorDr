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
public:
    QString text;
    int next;
    QPoint textPos;
    QSize textSize;
    int fontDelta;
    QString showAfterChapter;
public:
    QLabel* textLabel;
    explicit ChoicePushButton(QString, QString, QString, QString, QPoint, QSize, QString, int, QPoint, QSize, int, QString);
    explicit ChoicePushButton(NewPushButton, QString, int, QPoint, QSize, int, QString);
    QString getText();
    QPoint getTextPos();
    QSize getTextSize();
    int getNext();
    int getfontDelta();
    QString getShowAfterChapter();


signals:

};

#endif // CHOICEPUSHBUTTON_H
