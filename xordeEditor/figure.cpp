#include "figure.h"
#include <QDebug>



Figure::Figure(QString mFig, QString status, QPoint pos, double size, double start, double duration
               , double jrs, QString ani, double anist, double anidur,int anira)
{
    m_mainfig=mFig;
    m_status=status;
    m_pos=pos;
    m_size=size;
    m_start=start;
    m_duration=duration;
    m_jrSize=jrs;
    m_animation = ani;
    m_ani_start = anist;
    m_ani_duration = anidur;
    m_ani_range = anira;
}

QString Figure::getMainfig() const
{
    return m_mainfig;
}

QString Figure::getStatus() const
{
    return m_status;
}

QPoint Figure::getPos()
{
    return m_pos;
}

double Figure::getSize()
{
   // qDebug()<<m_size;
    return m_size;
}

double Figure::getStart() const
{
    return m_start;
}

double Figure::getDuration() const
{
    return m_duration;
}

double Figure::getJrSize()
{
    return m_jrSize;
}

QString Figure::getAnimation()
{
    return m_animation;
}

double Figure::getAniStart()
{
    return m_ani_start;
}

double Figure::getAniDuration()
{
    return m_ani_duration;
}

int Figure::getAniRange()
{
    return m_ani_range;
}
