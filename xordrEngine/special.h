#ifndef SPECIAL_H
#define SPECIAL_H

#include <QMovie>
#include <QPoint>
//#include "chapter.h"

//class Chapter;

class Special
{
    //friend Chapter;
    QMovie* m_special;
    QPoint m_point;
    int m_start;
public:
    Special(QMovie*,int,QPoint);
    QMovie* getSpecial()const;
    QPoint getPos();
    int getStart();

};

#endif // SPECIAL_H
