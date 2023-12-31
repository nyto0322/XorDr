#ifndef CHOICELIST_H
#define CHOICELIST_H

#include <QWidget>
#include "chapter.h"

namespace Ui {
class ChoiceList;
}

class ChoiceList : public QWidget
{
    Q_OBJECT
    int currentChapter;
    int currentSection;
    QVector<ChoicePushButton*> cbtnVec;
    void add();

public:
    explicit ChoiceList(int,int,QVector<ChoicePushButton*>&,QWidget *parent = nullptr);
    ~ChoiceList();

private:
    Ui::ChoiceList *ui;
signals:
    void save(int,QVector<ChoicePushButton*>&);

};

#endif // CHOICELIST_H
