#ifndef FRAMEINFO_H
#define FRAMEINFO_H

#include <QPixmap>
#include <QPoint>
#include <QFont>
#include <QSize>

class FrameInfo
{
    QString m_pix;
    QPoint m_backpoint;
    QSize m_backsize;
    QPoint m_textpoint;
    QSize m_textsize;
    QFont m_font;
public:
    FrameInfo(QString, QPoint, QSize, QPoint, QSize, QFont);
    FrameInfo();
    QString getPix();
    QPoint getBackPoint();
    QSize getBackSize();
    QPoint getTextPoint();
    QSize getTextSize();
    QFont getFont();


    void setPix(QString);
    void setBackPoint(QPoint);
    void setBackSize(QSize);
    void setTextPoint(QPoint);
    void setTextSize(QSize);
    void setFont(QFont);
};

#endif // FRAMEINFO_H

