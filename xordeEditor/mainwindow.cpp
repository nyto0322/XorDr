#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QPushButton>
#include <QDialog>
#include <QFileDialog>
#include <QDebug>
#include "data.h"
#include "configeditor.h"
#include <QDockWidget>
#include "chaptereditor.h"




void MainWindow::openFile(QString filepath)
{
    //打开文件夹
    i++;
    QVector<QWidget*>v;
    QMap<QTreeWidgetItem*,ChapterEditor*> chapterEditorMap;
    ConfigEditor* configEditor = new ConfigEditor();
    StyleEditor* styleEditor = new StyleEditor();
    v.push_back(configEditor);
    v.push_back(styleEditor);

    configEditor->setParent(ui->stackedWidget);
    ui->stackedWidget->addWidget(configEditor);
    styleEditor->setParent(ui->stackedWidget);
    ui->stackedWidget->addWidget(styleEditor);



    QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget);
    item->setText(0,filepath.mid(filepath.lastIndexOf("/")+1));
    ui->treeWidget->addTopLevelItem(item);
    QVariant var0(i);
    item->setData(0,Qt::UserRole,var0);  //节点为i





    Data* data = new Data(filepath,this);


    //config读取数据
    QTreeWidgetItem* itemConfig = new QTreeWidgetItem(item);
    itemConfig->setText(0,"config");
    item->addChild(itemConfig);
    configEditor->init(data);



    //style读取数据
    QTreeWidgetItem* itemStyle = new QTreeWidgetItem(item);
    itemStyle->setText(0,"style");
    item->addChild(itemStyle);
    styleEditor->init(data);


    //chapter读取数据
    QTreeWidgetItem* itemAllChapter = new QTreeWidgetItem(item);
    itemAllChapter->setText(0,"chapter");
    //        QVariant var1(1);
    //        itemAllChapter->setData(0,Qt::UserRole,var1);  //节点为1
    item->addChild(itemAllChapter);




    for(QMap<int,Chapter*>::const_iterator it = data->getChapterMap().constBegin();
        it != data->getChapterMap().constEnd();it++)
    {
        ChapterEditor* chapterEditor = new ChapterEditor();
        chapterEditor->setParent(ui->stackedWidget);
        chapterEditor->init(it.value());
        ui->stackedWidget->addWidget(chapterEditor);
        v.push_back(chapterEditor);
        connect(chapterEditor,&ChapterEditor::rename,[=](int pre,QString){
            data->removeChapter(pre);
            data->insertChapter(it.value());
        });


        QTreeWidgetItem* itemChapter = new QTreeWidgetItem(itemAllChapter);
        itemChapter->setText(0,QString::number(it.value()->getCurrentChapter()));
        itemAllChapter->addChild(itemChapter);
        chapterEditorMap.insert(itemChapter,chapterEditor);

        connect(chapterEditor,&ChapterEditor::rename,[=](int,QString s){
            itemChapter->setText(0,s);
        });
        connect(chapterEditor,&ChapterEditor::remove,[=](){
            data->removeChapter(it.key());
            delete chapterEditor;
            delete itemChapter;
        });
    }

    //关闭选项
    //保存选项
    QAction* action_save = new QAction("保存",this);
    QAction* action_close = new QAction("关闭",this);
    QAction* action_newChapter = new QAction("添加新章",this);
    connect(action_save,&QAction::triggered,data,&Data::save);
    connect(action_close,&QAction::triggered,[=](){
        //            for(int i = ui->stackedWidget->count(); i >= 0; i--)            //倒序删除
        //            {
        //                QWidget* widget = ui->stackedWidget->widget(i);
        //                ui->stackedWidget->removeWidget(widget);
        //                widget->deleteLater();
        //            }
        for(QVector<QWidget*>::const_iterator it = v.begin();it!=v.end();it++)
        {
            delete *it;
        }
        delete item;
    });

    //        QMap<QTreeWidgetItem*,ChapterEditor*>* pointm=&chapterEditorMap;
    //        QVector<QWidget*>* pointv=&v;

    int newI = 10000;
    connect(action_newChapter,&QAction::triggered,[=]()mutable{
        Chapter* c = new Chapter(data->getCurrentPath(),newI++);
        c->setDialog(1,new Dialog("","",0));
        data->insertChapter(c);


        ChapterEditor* chapterEditor = new ChapterEditor();
        chapterEditor->setParent(ui->stackedWidget);
        chapterEditor->init(c);
        ui->stackedWidget->addWidget(chapterEditor);
        connect(chapterEditor,&ChapterEditor::rename,[=](int pre,QString){
            data->removeChapter(pre);
            data->insertChapter(c);
        });

        QTreeWidgetItem* itemChapter = new QTreeWidgetItem(itemAllChapter);
        itemChapter->setText(0,QString::number(c->getCurrentChapter()));
        itemAllChapter->addChild(itemChapter);

        connect(ui->treeWidget,&QTreeWidget::itemDoubleClicked,[=](QTreeWidgetItem* itemT){
            if(itemT == itemChapter)
            {
                ui->stackedWidget->setCurrentWidget(chapterEditor);
            }
        });

        connect(chapterEditor,&ChapterEditor::rename,[=](int,QString s){
            itemChapter->setText(0,s);
        });
        connect(chapterEditor,&ChapterEditor::remove,[=](){
            data->removeChapter(c->getCurrentChapter());
            delete chapterEditor;
            delete itemChapter;
        });

    });

    QMenu *popMenu =new QMenu(this);
    popMenu->addAction(action_save);
    popMenu->addAction(action_close);
    popMenu->addSeparator();
    popMenu->addAction(action_newChapter);
    menuMap.insert(i,popMenu);




    connect(ui->treeWidget,&QTreeWidget::itemDoubleClicked,[=](QTreeWidgetItem* itemT){
        if(itemT == itemConfig)
        {
            ui->stackedWidget->setCurrentWidget(configEditor);
        }
        else if(itemT == itemStyle)
        {
            ui->stackedWidget->setCurrentWidget(styleEditor);
        }
        else
        {
            for(QMap<QTreeWidgetItem*,ChapterEditor*>::const_iterator it = chapterEditorMap.constBegin();
                it != chapterEditorMap.constEnd();it++)
            {
                if(itemT == it.key())
                {
                    ui->stackedWidget->setCurrentWidget(chapterEditorMap[itemT]);
                }
            }
        }
    });


}

void MainWindow::newFile(QString name, QString path)
{
    QString dirName = path+'/'+name;
    QDir dir(dirName);
    if(!dir.exists())
    {
        dir.mkdir(dirName);
    }
    else
    {
        qDebug()<<"存在同名文件夹";
        return;
    }
    dir.mkdir(dirName+"/res");
    dir.mkdir(dirName+"/res/command");
    dir.mkdir(dirName+"/res/command/background");
    dir.mkdir(dirName+"/res/command/bgm");
    dir.mkdir(dirName+"/res/command/cg");
    dir.mkdir(dirName+"/res/command/choice");
    dir.mkdir(dirName+"/res/command/dialog");
    dir.mkdir(dirName+"/res/command/perform");
    dir.mkdir(dirName+"/res/command/sound");
    dir.mkdir(dirName+"/res/command/special");
    dir.mkdir(dirName+"/res/command/vocal");
    dir.mkdir(dirName+"/res/resource");
    dir.mkdir(dirName+"/res/resource/background");
    dir.mkdir(dirName+"/res/resource/bgm");
    dir.mkdir(dirName+"/res/resource/cg");
    dir.mkdir(dirName+"/res/resource/choice");
    dir.mkdir(dirName+"/res/resource/config");
    dir.mkdir(dirName+"/res/resource/figure");
    dir.mkdir(dirName+"/res/resource/status");
    dir.mkdir(dirName+"/res/resource/sound");
    dir.mkdir(dirName+"/res/resource/special");
    dir.mkdir(dirName+"/res/resource/vocal");
    dir.mkdir(dirName+"/res/savedata");


    QFile file1(dirName+"/res/savedata.txt");
    file1.open(QIODevice::ReadWrite|QIODevice::Text);
    QByteArray arr;
    arr+="q:::::;\n";
    for(int i = 0;i<100;i++)
    {
        arr+="n::::::;\n";
    }
    file1.write(arr);
    file1.close();

    QFile file2(dirName+"/res/config.txt");
    file2.open(QIODevice::ReadWrite|QIODevice::Text);
    file2.close();

    QFile file3(dirName+"/res/saveconfig.txt");
    file3.open(QIODevice::ReadWrite|QIODevice::Text);
    QByteArray arr2;
    arr2+="-50;\n0;\n-50;\n0;\n50;\n50;\n50;\n50;\n50;\n35;";
    file3.write(arr2);
    file3.close();

    QFile file4(dirName+"/res/haveread.txt");
    file4.open(QIODevice::ReadWrite|QIODevice::Text);
    //在保存时更改！

    file4.close();


    openFile(path+'/'+name); 
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //可拖动
    ui->treeWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->treeWidget->setAcceptDrops(true);
    ui->treeWidget->setDragEnabled(true);
    ui->treeWidget->setDefaultDropAction(Qt::MoveAction);
    ui->treeWidget->setDragDropMode(QAbstractItemView::InternalMove);



    this->setCentralWidget(ui->stackedWidget);


    connect(ui->actiondock,&QAction::triggered,ui->dockWidget,&QWidget::show);


    //打开文件
    connect(ui->actionopen,&QAction::triggered,[=](){
        QFileDialog* file = new QFileDialog(this);
        file->setFileMode(QFileDialog::Directory);
        QString filename = file->getExistingDirectory();
        if(filename!="")
            this->openFile(filename);
    });

    //新建文件
    connect(ui->actionnew,&QAction::triggered,this,[=](){
        NewFile* newfile = new NewFile();
        newfile->show();
        connect(newfile,&NewFile::create,this,&MainWindow::newFile);
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_treeWidget_customContextMenuRequested(const QPoint &pos)
{
    QTreeWidgetItem* curItem=ui->treeWidget->itemAt(pos);  //获取当前被点击的节点
    if(curItem==NULL)return;           //在空白位置右击
    QVariant var = curItem->data(0,Qt::UserRole);
    for(int i = 0;i<50;i++)
    {
        if(var == i)
        {
            menuMap[i]->exec(QCursor::pos());//弹出位置为光标位置
        }
    }
}
