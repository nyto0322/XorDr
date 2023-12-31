#ifndef PERFORMPLAYER_H
#define PERFORMPLAYER_H

#include <QWidget>
#include "figure.h"
#include <QVector>
#include <QLabel>
#include <QTimer>
#include <QDebug>
#include <QPropertyAnimation>

class PerformPlayer : public QWidget
{
    Q_OBJECT
    QVector<Figure> vecPerform;
    QWidget* jrParent;
    QVector<QLabel*> vecMainLabel;
    QVector<QLabel*> vecStatusLabel;

    void playAnimation(QLabel*,int i);

    //QVector<QTimer*> vecTimer;

public:
    explicit PerformPlayer(QWidget *parent = nullptr);
    void playPerform(QVector<Figure>);
    void clearPerform();
    //void deleteLaterAndLater(QWidget*);

signals:
    //void deleteBegin();

};

class PerformPlayerJr : public QWidget
{
    Q_OBJECT
    QVector<Figure> vecPerform;
    QWidget* jrParent;
    QVector<QLabel*> VecMainLabel;
    QVector<QLabel*> VecStatusLabel;

   // QVector<QTimer*> vecTimer;

public:
    explicit PerformPlayerJr(QWidget *parent = nullptr);
    void playPerform(QVector<Figure>);
    void clearPerform();
    //void deleteLaterAndLater(QWidget*);
signals:

};

#endif // PERFORMPLAYER_H
