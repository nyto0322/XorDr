#ifndef BUTTONEDITOR_H
#define BUTTONEDITOR_H

#include <QWidget>
#include "newpushbutton.h"
#include "switchbutton.h"
#include <QFileDialog>

namespace Ui {
class ButtonEditor;
}

class ButtonEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ButtonEditor(QString ,NewPushButton* ,QWidget *parent = nullptr);
    explicit ButtonEditor(QString ,SwitchButton* ,QWidget *parent = nullptr);
    void init(NewPushButton*);
    void init(SwitchButton*);
    ~ButtonEditor();

private:
    Ui::ButtonEditor *ui;
};

#endif // BUTTONEDITOR_H
