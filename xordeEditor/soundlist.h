#ifndef SOUNDLIST_H
#define SOUNDLIST_H

#include <QWidget>
#include "chapter.h"

namespace Ui {
class SoundList;
}

class SoundList : public QWidget
{
    Q_OBJECT
    int currentChapter;
    int currentSection;

public:
    explicit SoundList(int,int,QVector<Sound>&,QWidget *parent = nullptr);
    ~SoundList();

private:
    Ui::SoundList *ui;
signals:
    void save(int,QVector<Sound>&);
};

#endif // SOUNDLIST_H
