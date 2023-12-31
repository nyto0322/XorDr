#ifndef SOUND_H
#define SOUND_H

#include <QSound>
//#include "chapter.h"

//class Chapter;

class Sound
{
    //friend Chapter;
    QString m_soundPath;
    int m_start;
public:
    Sound(QString,int);
    QString getSoundPath();
    int getStart();


};

#endif // SOUND_H
