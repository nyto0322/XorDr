#ifndef FRAMEINFO_H
#define FRAMEINFO_H

#include <QPixmap>
#include <QPoint>
#include <QFont>
#include <QSize>

class FrameInfo
{
    QPixmap* m_pix;
    QPoint m_backpoint;
    QSize m_backsize;
    QPoint m_textpoint;
    QSize m_textsize;
    QFont m_font;
public:
    FrameInfo(QPixmap*,QPoint,QSize,QPoint,QSize,QFont);
    QPixmap* getPix();
    QPoint getBackPoint();
    QSize getBackSize();
    QPoint getTextPoint();
    QSize getTextSize();
    QFont getFont();


};

#endif // FRAMEINFO_H

