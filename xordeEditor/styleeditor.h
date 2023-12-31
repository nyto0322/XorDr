#ifndef STYLEEDITOR_H
#define STYLEEDITOR_H

#include <QWidget>
#include "data.h"
#include <QFontDialog>

namespace Ui {
class StyleEditor;
}

class StyleEditor : public QWidget
{
    Q_OBJECT
    Data* data;
    void save();

public:
    explicit StyleEditor(QWidget *parent = nullptr);
    void init(Data*);
    ~StyleEditor();

private:
    Ui::StyleEditor *ui;
};

#endif // STYLEEDITOR_H
