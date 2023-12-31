#ifndef CHAPTEREDITOR_H
#define CHAPTEREDITOR_H

#include <QWidget>
#include "chapter.h"

namespace Ui {
class ChapterEditor;
}

class ChapterEditor : public QWidget
{
    Q_OBJECT
    Chapter* chapter;
    void reInit();

public:
    explicit ChapterEditor(QWidget *parent = nullptr);
    void init(Chapter*);
    ~ChapterEditor();

private:
    Ui::ChapterEditor *ui;

signals:
    void remove();
    void rename(int ,QString);
};

#endif // CHAPTEREDITOR_H
