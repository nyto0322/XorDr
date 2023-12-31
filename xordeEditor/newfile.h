#ifndef NEWFILE_H
#define NEWFILE_H

#include <QWidget>
#include <QFile>
#include <QFileDialog>

namespace Ui {
class NewFile;
}

class NewFile : public QWidget
{
    Q_OBJECT

public:
    explicit NewFile(QWidget *parent = nullptr);
    ~NewFile();

private:
    Ui::NewFile *ui;

signals:
    void create(QString name,QString path);
};

#endif // NEWFILE_H
