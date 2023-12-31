#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QImage>
#include <QSound>
#include <QVector>
#include "data.h"
#include "savedata.h"
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QString>
#include <QMap>
#include "newpushbutton.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "sceneplayer.h"
#include "configplayer.h"
#include "saveplayer.h"
#include "loadplayer.h"
#include "galleryplayer.h"
#include "saveconfig.h"
#include <QStackedWidget>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QStackedWidget* stack;
    Data* data;
    SaveData* sData;
    void initMain();

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
