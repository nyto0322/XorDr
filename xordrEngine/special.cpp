#include "special.h"



Special::Special(QMovie* m, int time,QPoint p)
{
    m_special = m;
    m_start = time;
    m_point = p;
}

QMovie *Special::getSpecial() const
{
    return m_special;
}

QPoint Special::getPos()
{
    return m_point;
}

int Special::getStart()
{
    return m_start;
}
