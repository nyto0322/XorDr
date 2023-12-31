#ifndef FIGURE_H
#define FIGURE_H

#include <QObject>
#include <QImage>
#include <QPoint>

//#include "chapter.h"

//class Chapter;

class Figure
{
public:
    QString m_mainfig;
    QString m_status;
    QPoint m_pos;
    double m_size;
    double m_start;
    double m_duration;
    double m_jrSize;
    QString m_animation;
    double m_ani_start;
    double m_ani_duration;
    int m_ani_range;
public:
    Figure(QString,QString,QPoint,double,double,double,double,QString,double,double,int);
    QString getMainfig()const;
    QString getStatus()const;
    QPoint getPos();
    double getSize();
    double getStart() const;
    double getDuration() const;
    double getJrSize();
    QString getAnimation();
    double getAniStart();
    double getAniDuration();
    int getAniRange();
};

#endif // FIGURE_H
