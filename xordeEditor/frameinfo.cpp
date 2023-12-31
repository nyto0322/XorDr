#include "frameinfo.h"


FrameInfo::FrameInfo(QString pix, QPoint bp, QSize bs, QPoint tp, QSize ts, QFont f)
{
    m_pix = pix;
    m_backpoint = bp;
    m_backsize = bs;
    m_textpoint = tp;
    m_textsize = ts;
    m_font = f;
}

QString FrameInfo::getPix()
{
    return m_pix;
}

QPoint FrameInfo::getBackPoint()
{
    return m_backpoint;
}

QSize FrameInfo::getBackSize()
{
    return m_backsize;
}

QPoint FrameInfo::getTextPoint()
{
    return m_textpoint;
}

QSize FrameInfo::getTextSize()
{
    return m_textsize;
}

QFont FrameInfo::getFont()
{
    return m_font;
}

void FrameInfo::setPix(QString p)
{
    m_pix = p;
}

void FrameInfo::setBackPoint(QPoint p)
{
    m_backpoint = p;
}

void FrameInfo::setBackSize(QSize s)
{
    m_backsize = s;
}

void FrameInfo::setTextPoint(QPoint p)
{
    m_textpoint = p;
}

void FrameInfo::setTextSize(QSize s)
{
    m_textsize = s;
}

void FrameInfo::setFont(QFont f)
{
    m_font = f;
}


