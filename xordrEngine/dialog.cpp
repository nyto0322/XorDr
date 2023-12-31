#include "dialog.h"

Dialog::Dialog(QString name,QString text,int size)
{
    m_name = name;
    m_text = text;
    m_size = size;
}

QString Dialog::getName()
{
    return m_name;
}

QString Dialog::getText()
{
    return m_text;
}

int Dialog::getFontDelta()
{
    return m_size;
}
