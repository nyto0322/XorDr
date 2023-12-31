#ifndef CONFIGEDITOR_H
#define CONFIGEDITOR_H

#include <QWidget>
#include "data.h"
#include "mainbacklist.h"
#include <QFileDialog>

namespace Ui {
class ConfigEditor;
}

class ConfigEditor : public QWidget
{
    Q_OBJECT
    Data* data;
    MainBackList* mbl;
    void save();
public:
    explicit ConfigEditor(QWidget *parent = nullptr);
    void init(Data*);
    ~ConfigEditor();

private:
    Ui::ConfigEditor *ui;
};

#endif // CONFIGEDITOR_H
