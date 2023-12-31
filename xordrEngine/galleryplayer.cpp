 #include "galleryplayer.h"




GalleryPlayer::GalleryPlayer(Data * d, QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(d->getSize());
    this->move(0,0);
    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,QBrush(*d->getGalleryBackground()));
    this->setPalette(palette);
    this->show();



    tableWidget = new QTableWidget(this);
    tableWidget->move(d->getGallerycgPos());
    tableWidget->setColumnCount(d->getGallerycgColumn());
    tableWidget->setFixedSize(d->getGallerycgWidth(),d->getGallerycgWidth()/tableWidget->columnCount()*this->height()/this->width()*d->getGallerycgRow());
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止编辑
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //自适应宽度
    tableWidget->setFrameShape(QFrame::NoFrame); //设置无边框
    tableWidget->setShowGrid(false); //设置不显示格子线
    tableWidget->setGridStyle(Qt::SolidLine);
//    tableWidget->setSortingEnabled(true);    //排序可见的
//    tableWidget->setCornerButtonEnabled(true);

    //去除选中虚线框
    tableWidget->setFocusPolicy(Qt::NoFocus);


    //设置列宽杭高
    tableWidget->verticalHeader()->setVisible(false);
    tableWidget->horizontalHeader()->setVisible(false);
    tableWidget->horizontalHeader()->setDefaultSectionSize(tableWidget->width()/tableWidget->columnCount());
    tableWidget->verticalHeader()->setDefaultSectionSize(tableWidget->width()/tableWidget->columnCount()*this->height()/this->width());


    tableWidget->setStyleSheet(d->getGallerycgStyleSheet());


//    tableWidget->setStyleSheet(
//                "QTableWidget {"
//                "background-color: rgba(255, 192, 203, 20%);"
//                "}"
//                "QTableWidget::item {"
//                "background-color: rgba(255, 192, 203, 20%);"
//                "}"
//                "QTableWidget::item:hover {"
//                "background-color: rgba(255, 192, 203, 60%);"
//                "}"
//                "QScrollBar::handle:vertical"
//                "{"
//                "background: rgba(255, 192, 203, 60%); "// 垂直滚动条 handle 的背景色
//                "border: 0px solid grey;            "// 垂直滚动条 handle 边框
//                "border-radius:3px;                 "// 垂直滚动条 handle 圆角
//                "width: 8px;                        "// 垂直滚动条 handle 宽度
//                "}"
//                "QScrollBar::vertical  "                  // 垂直滚动条 区域
//                "{"
//                "border-width:1px;  "                     // 垂直滚动条 区域 边框宽度
//                "border-style: solid;         "           // 垂直滚动条 区域 边框类型
//                "border-color: rgba(255, 192, 203, 60%);" // 垂直滚动条 区域 边框颜色
//                "width: 8px;       "                      // 垂直滚动条 区域 宽度
//                "margin:0px 0px 0px 0px;      "           // 垂直滚动条 区域 margin
//                "border-radius:3px;      "                // 垂直滚动条 区域 圆角
//                "}"
//                "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical "// 垂直滚动条  handle上、下区域（未被handle占用的区域）
//                "{"
//                "background:rgba(255, 192, 203, 60%);       "                     // 垂直滚动条 handle上、下区域的背景色
//                "}"
//                "QScollBar::add-line:vertical, QScrollBar::sub-line:vertical " // 垂直滚动条 最顶端与最低端的区域
//                "{"
//                "background:transparent;         "                             // 垂直滚动条 最顶端与最低端区域的背景色
//                "}");
//    tableWidget->setStyleSheet(
//                "QTableWidget {\
//                background-color: rgba(255, 192, 203, 20%);\
//                }\
//                QTableWidget::item {\
//                background-color: rgba(255, 192, 203, 20%);\
//                }\
//                QTableWidget::item:hover {\
//                background-color: rgba(255, 192, 203, 60%);\
//                }\
//                QScrollBar::handle:vertica{\
//                background: rgba(0, 192, 203, 60%); \
//                border: 0px solid grey;           \
//                border-radius:3px;                \
//                width: 15px;}                  \
//                QScrollBar::vertical{               \
//                border-width:1px; \
//                border-style: solid;        \
//                border-color: rgba(255, 192, 203, 60%);\
//                width: 15px;     \
//                margin:0px 0px 0px 0px;    \
//                border-radius:3px;    \
//                }\
//                QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical{\
//                background:rgba(0 ,245 ,255, 60%);   \
//                }");



    toMainBtn = new NewPushButton(*d->getOtherPlayerBtn()[0]);
    toMainBtn->setParent(this);
    toMainBtn->move(toMainBtn->getPos());
    toMainBtn->show();
    connect(toMainBtn,&QPushButton::clicked,this,[=](){
        playBtn->cancel();
        emit toMain();
    });







    //获取cg，直接读取文件
    QString currentPath = QCoreApplication::applicationDirPath();
    QString filePathC = QString("%1/res/resource/cg").arg(currentPath);

    QDir dir(filePathC);
    QStringList filter;
    filter<<"*.png";
    dir.setNameFilters(filter);
    QList<QFileInfo> *fileInfo = new QList<QFileInfo>(dir.entryInfoList(filter));
    for (int i = 0; i< fileInfo->size(); i++)
    {
        QLabel* l = new QLabel(this);
        l->setFixedSize(tableWidget->width()/tableWidget->columnCount()
                        ,tableWidget->width()/tableWidget->columnCount()*this->height()/this->width());
        QImage* img = new QImage(fileInfo->at(i).filePath());
        l->setPixmap(QPixmap::fromImage(img->scaled(l->size()*0.9,Qt::KeepAspectRatio,Qt::SmoothTransformation)));
        l->setAlignment(Qt::AlignCenter);
        int pi = i / tableWidget->columnCount();
        int pj = i % tableWidget->columnCount();
        if(pi == tableWidget->rowCount())
        {
            tableWidget->setRowCount(tableWidget->rowCount()+1);
        }
        tableWidget->setCellWidget(pi,pj,l);
        itemMap[pi][pj] = img;

    }
    connect(tableWidget,&QTableWidget::cellClicked,[=](int a,int b){
        if(itemMap[a].contains(b))
        {
            cgShow->setPixmap(QPixmap::fromImage(*itemMap[a][b]));
            cgShow->show();
        }
    });



    //音乐播放
    mediaWidget = new QWidget(this);
    mediaWidget->setGeometry(d->getGallerymediaRect());
    mediaWidget->show();

    listWidget = new QListWidget(mediaWidget);
    listWidget->setFixedSize(mediaWidget->width(),mediaWidget->height()*0.8);
    playList = new QMediaPlaylist(this);
    playList ->setPlaybackMode(QMediaPlaylist::Loop);
    singlePlayList = new QMediaPlaylist(this);
    singlePlayList ->setPlaybackMode(QMediaPlaylist::Loop);
    player = new QMediaPlayer(this);



    listWidget->setStyleSheet(d->getGallerymediaStyleSheet());
    listWidget->setFocusPolicy(Qt::NoFocus);






    filePathC = QString("%1/res/resource/bgm").arg(currentPath);
    QDir bgmdir(filePathC);
    QStringList bgmfilter;
    bgmfilter<<"*.mp3";
    dir.setNameFilters(filter);
    QList<QFileInfo> *bgmfileInfo = new QList<QFileInfo>(bgmdir.entryInfoList(bgmfilter));
    for (int i = 0; i< bgmfileInfo->size(); i++)
    {
        QListWidgetItem* item = new QListWidgetItem(listWidget);
        QString fileName = bgmfileInfo->at(i).fileName();
        item->setText(fileName.mid(0,fileName.length()-4));
        listWidget->addItem(item);
        playList->addMedia(QUrl::fromLocalFile(bgmfileInfo->at(i).filePath()));
        bgmItemMap.insert(item,i);
    }
    listWidget->setCurrentRow(0);
    playList->setCurrentIndex(0);
    singlePlayList->addMedia(playList->currentMedia());

    player->setPlaylist(playList);
    player->setVolume(mainVolume*bgmVolume/100);

    preBtn = new NewPushButton(*d->getGallerymediaBtn()[0]);
    preBtn->setParent(mediaWidget);
    preBtn->move(preBtn->getPos());
    connect(preBtn,&NewPushButton::clicked,this,&GalleryPlayer::previousBtnClicked);
    nextBtn = new NewPushButton(*d->getGallerymediaBtn()[1]);
    nextBtn->setParent(mediaWidget);
    nextBtn->move(nextBtn->getPos());
    connect(nextBtn,&NewPushButton::clicked,this,&GalleryPlayer::nextBtnClicked);
    playBtn = new SwitchButton(*d->getGallerymediaSwitch()[0]);
    playBtn->setParent(mediaWidget);
    playBtn->move(playBtn->getPos());
    connect(playBtn,&SwitchButton::toggled,this,&GalleryPlayer::playBtnClicked);
    modeBtn = new SwitchButton(*d->getGallerymediaSwitch()[1]);
    modeBtn->setParent(mediaWidget);
    modeBtn->move(modeBtn->getPos());
    connect(modeBtn,&SwitchButton::toggled,this,&GalleryPlayer::modeBtnClicked);

    connect(listWidget,&QListWidget::itemClicked,this,&GalleryPlayer::listBtnClicked);
    connect(playList,&QMediaPlaylist::currentIndexChanged,[=](int a){listWidget->setCurrentRow(a);});

    QSlider* bgmVolumeS = new QSlider(Qt::Horizontal,mediaWidget);
    bgmVolumeS->setGeometry(d->getGallerymediaSliderRect());
    bgmVolumeS->setStyleSheet(d->getSliderStyleSheet());
    bgmVolumeS->setMinimum(0);
    bgmVolumeS->setMaximum(100);
    bgmVolumeS->setValue(bgmVolume);
    connect(bgmVolumeS,&QSlider::sliderReleased,[=](){
        player->setVolume(bgmVolumeS->value()*mainVolume/100);
    });

    cgShow = new QLabel(this);
    cgShow->setFixedSize(this->size());
    cgShow->move(0,0);
    cgShow->hide();
    cgShow->activateWindow();
}


void GalleryPlayer::previousBtnClicked()
{
    player->stop();
    if(playList->mediaCount() == 0)
    {
        return ;
    }
    playList->previous();
    singlePlayList->clear();
    singlePlayList->addMedia(playList->currentMedia());
    if(playBtn->isToggled())
    {
        player->play();
    }
}

void GalleryPlayer::nextBtnClicked()
{
    player->stop();
    if(playList->mediaCount() == 0)
    {
        return;
    }
    playList->next();
    singlePlayList->clear();
    singlePlayList->addMedia(playList->currentMedia());
    if(playBtn->isToggled())
    {
        player->play();
    }
}

void GalleryPlayer::playBtnClicked(bool i)
{
    if(i)
    {
        emit stopMainBgm();
        player->play();
    }
    else
    {
        player->pause();
    }
}

void GalleryPlayer::modeBtnClicked(bool i) //是否单曲
{
    if(i)
    {
        player->stop();
        singlePlayList->clear();
        singlePlayList->addMedia(playList->currentMedia());
        player->setPlaylist(singlePlayList);
        if(playBtn->isToggled())
        {
            player->play();
        }
    }
    else
    {
        player->stop();
        int row = listWidget->currentRow();
        player->setPlaylist(playList);       //会重置定位？
        playList->setCurrentIndex(row);     //定位至该行

        if(playBtn->isToggled())
        {
            player->play();
        }
    }
}

void GalleryPlayer::listBtnClicked(QListWidgetItem * item)
{
    player->stop();
    if(playList->mediaCount() == 0)
    {
        return ;
    }
    playList->setCurrentIndex(bgmItemMap[item]);
    singlePlayList->clear();
    singlePlayList->addMedia(playList->currentMedia());
    if(playBtn->isToggled())
    {
        player->play();
    }
}

void GalleryPlayer::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::RightButton && !cgShow->isHidden())
    {
        cgShow->hide();
    }
    QWidget::mousePressEvent(e);
}
