#ifndef PERFORMPLAYERJR_H
#define PERFORMPLAYERJR_H

#include <QWidget>
#include "figure.h"
#include <QLabel>
#include <QTimer>

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

#endif // PERFORMPLAYERJR_H
