#include "textlabel.h"
#include <QDebug>
#include "saveconfig.h"

TextLabel::TextLabel(QWidget *parent) : QLabel(parent)
{
    connect(&m_time, &QTimer::timeout,this,&TextLabel::changed);
    setWordWrap(true);
    m_net = 0;
}

void TextLabel::setNormalText(QString text)
{
    QLabel::setText(text);
}

void TextLabel::setGradualText(QString text)
{
    m_time.start(100+textShowSpeed);
    m_text = text;
}

void TextLabel::changed()
{
    m_net ++;
    if (m_net > m_text.size())
    {
        m_time.stop();
        m_net = 0;
        emit isOver();
    }
    else
    {
        QLabel::setText(m_text.left(m_net));
    }
}

void TextLabel::pressToNext()
{
    m_time.stop();
    m_net = 0;
    setNormalText(m_text);
    emit isOver();
}
