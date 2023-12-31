#ifndef SPECIALLIST_H
#define SPECIALLIST_H

#include <QWidget>
#include "chapter.h"

namespace Ui {
class SpecialList;
}

class SpecialList : public QWidget
{
    Q_OBJECT
    int currentChapter;
    int currentSection;

public:
    explicit SpecialList(int,int,QVector<Special>&,QWidget *parent = nullptr);
    ~SpecialList();

private:
    Ui::SpecialList *ui;
signals:
    void save(int,QVector<Special>&);

};

#endif // SPECIALLIST_H
