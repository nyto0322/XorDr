#ifndef SINGLESECTIONEDITOR_H
#define SINGLESECTIONEDITOR_H

#include <QWidget>
#include "chapter.h"
#include <QFileDialog>

namespace Ui {
class SingleSectionEditor;
}

class SingleSectionEditor : public QWidget
{
    Q_OBJECT

    int currentSection;
    Chapter* chapter;
    Dialog* dialog;
public:
    explicit SingleSectionEditor(QWidget *parent = nullptr);
    void init(int,Chapter*);
    ~SingleSectionEditor();
    void save();

private:
    Ui::SingleSectionEditor *ui;

signals:
    void reInit();

};

#endif // SINGLESECTIONEDITOR_H
