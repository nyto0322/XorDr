#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "configeditor.h"
#include "styleeditor.h"
#include "chaptereditor.h"
#include "data.h"
#include <QMap>
#include <QTreeWidgetItem>
#include "newfile.h"
#include <QTime>


static int i=0;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
//    ConfigEditor* configEditor;
//    StyleEditor* styleEditor;
//    QMap<QTreeWidgetItem*,ChapterEditor*> chapterEditorMap;
    QMap<int,QMenu*> menuMap;


    void openFile(QString);
    void newFile(QString name,QString path);




public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_treeWidget_customContextMenuRequested(const QPoint &pos);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
