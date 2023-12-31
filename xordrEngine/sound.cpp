#include "sound.h"

Sound::Sound(QString s,int time)
{
    m_soundPath = s;
    m_start = time;
}

QString Sound::getSoundPath()
{
    return m_soundPath;
}

int Sound::getStart()
{
    return m_start;
}
