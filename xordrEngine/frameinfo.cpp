#include "frameinfo.h"


FrameInfo::FrameInfo(QPixmap *pix, QPoint bp, QSize bs, QPoint tp, QSize ts, QFont f)
{
    m_pix = pix;
    m_backpoint = bp;
    m_backsize = bs;
    m_textpoint = tp;
    m_textsize = ts;
    m_font = f;
}

QPixmap *FrameInfo::getPix()
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


