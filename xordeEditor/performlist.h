#ifndef PERFORMLIST_H
#define PERFORMLIST_H

#include <QWidget>
#include "chapter.h"

namespace Ui {
class PerformList;
}

class PerformList : public QWidget
{
    Q_OBJECT
    int currentChapter;
    int currentSection;

public:
    explicit PerformList(int,int,QVector<Figure>&,QWidget *parent = nullptr);



    ~PerformList();

private:
    Ui::PerformList *ui;
signals:
    void save(int,QVector<Figure>&);

};

#endif // PERFORMLIST_H
