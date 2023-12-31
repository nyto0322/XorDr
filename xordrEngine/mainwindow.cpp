#include "mainwindow.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    data = new Data(this);
    if(data->loadError!="")
    {
        QMessageBox::critical(this,"错误",data->loadError);
    }
    QPixmap pixmap;
    pixmap.load(data->getMouse());
    QCursor cursor(pixmap,0,0);
    setCursor(cursor);

    sData = new SaveData(this);
    initMain();
}



void MainWindow::initMain()
{
    this->setWindowIcon(data->getIcon());
    this->setWindowTitle(data->getTitle());

    stack = new QStackedWidget(this);
    QWidget* page0main = new QWidget(stack);
    QWidget* page1play = new QWidget(stack);
    QWidget* page2datasave = new QWidget(stack);
    QWidget* page3dataload = new QWidget(stack);
    QWidget* page4gallery = new QWidget(stack);
    QWidget* page5config = new QWidget(stack);
    stack->addWidget(page0main);
    stack->addWidget(page1play);
    stack->addWidget(page2datasave);
    stack->addWidget(page3dataload);
    stack->addWidget(page4gallery);
    stack->addWidget(page5config);
    stack->setCurrentIndex(0);
    this->setFixedSize(data->getSize());
    stack->setFixedSize(data->getSize());
    stack->move(0,0);

    page0main->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,QBrush(*sData->mainPic));
    page0main->setPalette(palette);

    QMap<int,NewPushButton*> btnmap = data->getBeginBtn();
    NewPushButton* btnNewgame = btnmap[0];
    NewPushButton* btnContinue = btnmap[1];
    NewPushButton* btnDataload = btnmap[2];
    NewPushButton* btnExtra = btnmap[3];
    NewPushButton* btnSystem = btnmap[4];
    NewPushButton* btnExit = btnmap[5];

    btnNewgame->setParent(page0main);
    btnNewgame->move(btnNewgame->getPos());
    btnContinue->setParent(page0main);
    btnContinue->move(btnContinue->getPos());
    btnDataload->setParent(page0main);
    btnDataload->move(btnDataload->getPos());
    btnExtra->setParent(page0main);
    btnExtra->move(btnExtra->getPos());
    btnSystem->setParent(page0main);
    btnSystem->move(btnSystem->getPos());
    btnExit->setParent(page0main);
    btnExit->move(btnExit->getPos());

    ScenePlayer* scenePlayer = new ScenePlayer(sData,data,page1play);
    SavePlayer* savePlayer = new SavePlayer(sData,data,page2datasave);
    LoadPlayer* loadPlayer = new LoadPlayer(sData,data,page3dataload);
    GalleryPlayer* galleryPlayer = new GalleryPlayer(data,page4gallery);
    ConfigPlayer* configPlayer = new ConfigPlayer(data,page5config);

    QMediaPlaylist* playList = new QMediaPlaylist(this);
    QMediaPlayer* bgmer = new QMediaPlayer(this);
    playList->addMedia(QUrl::fromLocalFile(data->getBgmPath()));
    playList->setPlaybackMode(QMediaPlaylist::Loop);            //播放列表循环
    bgmer->setPlaylist(playList);                              //置播放列表到播放器
    bgmer->setVolume(mainVolume*mainSceneBgmVolume/100);           //设置音量
    bgmer->play();


    if(!sData->galleryIsOpen)
    {
        btnExtra->hide();
    }



    connect(btnNewgame,&QPushButton::clicked,[=](){
        stack->setCurrentIndex(1);
        bgmer->stop();
        scenePlayer->playScene(1,1);
    });
    connect(scenePlayer,&ScenePlayer::backMain,[=](){
        stack->setCurrentIndex(0);
        bgmer->setVolume(mainVolume*mainSceneBgmVolume/100);
        bgmer->play();
        if(btnExtra->isHidden() && sData->galleryIsOpen)
        {
            btnExtra->show();
        }
        QPalette palette = this->palette();
        palette.setBrush(QPalette::Window,QBrush(*sData->mainPic));
        page0main->setPalette(palette);
    });
    connect(scenePlayer,&ScenePlayer::toConfig,[=](){
        stack->setCurrentIndex(5);
        configPlayer->isFromScene(true);
    });
    connect(scenePlayer,&ScenePlayer::toSave,[=](int c,int s,int p,int n,QPixmap* pix,QString text){
        stack->setCurrentIndex(2);
        savePlayer->inputSaveData(c,s,p,n,pix,text);
        savePlayer->fromScene(true);
    });

    connect(savePlayer,&SavePlayer::toScene,[=](){
        stack->setCurrentIndex(1);
    });

    connect(scenePlayer,&ScenePlayer::toLoad,[=](){
        stack->setCurrentIndex(3);
        loadPlayer->fromScene(true);
    });
    connect(scenePlayer,&ScenePlayer::qSave,savePlayer,&SavePlayer::qSave);
    connect(scenePlayer,&ScenePlayer::qLoad,[=](){
        if(loadPlayer->qLoad()->currentChapter!=0
                &&loadPlayer->qLoad()->currentSection!=0) //qload continue 当不存在qsave时
        {
            scenePlayer->endScene();
            scenePlayer->playRandomScene(loadPlayer->qLoad()->currentChapter,
                                         loadPlayer->qLoad()->currentSection,
                                         loadPlayer->qLoad()->previousChapter,
                                         loadPlayer->qLoad()->nextChapter);
        }
    });




    connect(btnContinue,&QPushButton::clicked,[=](){
        if(loadPlayer->qLoad()->currentChapter!=0
                &&loadPlayer->qLoad()->currentSection!=0) //qload continue 当不存在qsave时
        {
            stack->setCurrentIndex(1);
            bgmer->stop();
            scenePlayer->playRandomScene(loadPlayer->qLoad()->currentChapter,
                                         loadPlayer->qLoad()->currentSection,
                                         loadPlayer->qLoad()->previousChapter,
                                         loadPlayer->qLoad()->nextChapter);
            //在这一章内寻找最近的back与bgm加载
            //保证每章开头都有设置bgm与back
        }
    });



    connect(btnDataload,&QPushButton::clicked,[=](){
        stack->setCurrentIndex(3);
        loadPlayer->fromScene(false);
    });
    connect(loadPlayer,&LoadPlayer::toMain,[=](){
        scenePlayer->endScene();
        stack->setCurrentIndex(0);
        bgmer->setVolume(mainVolume*mainSceneBgmVolume/100);           //设置音量
        bgmer->play();
    });
    connect(loadPlayer,&LoadPlayer::toScene,[=](){
        stack->setCurrentIndex(1);
    });
    connect(loadPlayer,&LoadPlayer::loadData,[=](int cc,int cs,int pc,int nc){
        if(cc!=0 && cc!=-1)
        {
            scenePlayer->endScene();
            stack->setCurrentIndex(1);
            bgmer->stop();
            scenePlayer->playRandomScene(cc,cs,pc,nc);
        }
    });
    connect(loadPlayer,&LoadPlayer::toSave,[=](){
        stack->setCurrentIndex(2);
        savePlayer->fromScene(loadPlayer->isFromScene);
    });


    connect(savePlayer,&SavePlayer::toMain,[=](){
        scenePlayer->endScene();
        stack->setCurrentIndex(0);
        bgmer->setVolume(mainVolume*mainSceneBgmVolume/100);
        bgmer->play();
    });
    connect(savePlayer,&SavePlayer::toLoad,[=](){
        stack->setCurrentIndex(3);
        loadPlayer->fromScene(savePlayer->isFromScene);
    });
    connect(savePlayer,&SavePlayer::saveDataUpdate,loadPlayer,&LoadPlayer::saveDataUpdate);



    connect(btnExtra,&QPushButton::clicked,[=](){
        stack->setCurrentIndex(4);
    });
    connect(galleryPlayer,&GalleryPlayer::toMain,[=](){
        stack->setCurrentIndex(0);
        bgmer->play();
    });
    connect(galleryPlayer,&GalleryPlayer::stopMainBgm,[=](){
        bgmer->stop();
    });



    connect(btnSystem,&QPushButton::clicked,[=](){
        stack->setCurrentIndex(5);
        configPlayer->isFromScene(false);
    });

    connect(configPlayer,&ConfigPlayer::toMain,[=](){
        scenePlayer->endScene();
        stack->setCurrentIndex(0);
        bgmer->setVolume(mainVolume*mainSceneBgmVolume/100);           //设置音量
        bgmer->play();
    });
    connect(configPlayer,&ConfigPlayer::toScene,[=](){
        stack->setCurrentIndex(1);
    });



    connect(btnExit,&QPushButton::clicked,[=](){
        if(QMessageBox::question(this,"退出吗","真的要退出吗")==QMessageBox::Yes)
        {
            exit(0);
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
    delete data;
    delete sData;
}

