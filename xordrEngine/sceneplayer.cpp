#include "sceneplayer.h"




void ScenePlayer::playDialog()
{
    dialogIsGradual = true;           //禁用点击即下一节，而是把他显示完
    QString name = chapterMap[currentChapter]->getDialog()[currentSection]->getName();
    QString text = chapterMap[currentChapter]->getDialog()[currentSection]->getText();
    nameLabel->setText(name);
    QFont tempFontN = nameFrame->getFont();
    tempFontN.setPointSize(tempFontN.pointSize()+textSize);
    textLabel->setFont(tempFontN);
    nameLabel->show();

    QFont tempFontT = textFrame->getFont();
    if(sd->haveRead[currentChapter] == -1 || sd->haveRead[currentChapter] >= currentSection)
    {
        textLabel->setStyleSheet("color:yellow;");
    }
    else
    {
        textLabel->setStyleSheet("color:black;");
        sd->haveRead[currentChapter] = currentSection;
        sd->saveHaveRead();
        if(isSkip)
        {
            skipS->cancel();
        }
    }

    tempFontT.setPointSize(tempFontT.pointSize()+chapterMap[currentChapter]->getDialog()[currentSection]->getFontDelta()+textSize);
    textLabel->setFont(tempFontT);
    textLabel->setNormalText("");//先清空，防止上一句话延迟
    textLabel->setGradualText(text);


    QListWidgetItem* item = new QListWidgetItem(hisList);
    item->setSizeHint(QSize(hisList->width()*0.9,hisList->height()*0.2));           //改高度？？
    QString histext = "";
    if(name!="")
    {
        histext="【"+name+"】";
    }
    histext=histext+"\n"+text;
    item->setFont(textFrame->getFont());
    item->setText(histext);
    item->setForeground(Qt::white);                                                 //改颜色？？
    SingleData* single = new SingleData(currentChapter,currentSection,previousChapter,nextChapter);
    itemMap.insert(item,single);
}

void ScenePlayer::playBgm()
{
    bgmPlayer->setVolume(mainVolume*bgmVolume/100);    //需要，以实时更改
    if(!chapterMap[currentChapter]->getBgm().contains(currentSection))
    {
        return;            //如果没有新的bgm就不更改bgm
    }
    bgmPlayer->playBgm(chapterMap[currentChapter]->getBgm()[currentSection]);
}

void ScenePlayer::playBackground()
{
    if(!chapterMap[currentChapter]->getBackground().contains(currentSection))
    {
        return;
    }
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,QBrush(*chapterMap[currentChapter]->getBackground()[currentSection]));
    this->setPalette(palette);
}

void ScenePlayer::playChoice()
{
    //qDebug()<<nextChapter<<"playchoice";
    if(this->nextChapter!=-1)       //已有确定值
    {
        return;
    }
    if(chapterMap[currentChapter]->getNextChapter()!=-1)
    {
        this->nextChapter=chapterMap[currentChapter]->getNextChapter();    //无分支，直接赋定值
        return;
    }
    if(!chapterMap[currentChapter]->getChoice().contains(currentSection))  //有分支，但还未读到
    {
        return;
    }
    //进入分支！
    //出现选择按钮！！！！！！！！！！！
    //禁用skip auto按钮
    skipS->setEnabled(false);
    autoS->setEnabled(false);
    hideB->setEnabled(false);
    previousB->setEnabled(false);
    nextB->setEnabled(false);
    //停止skip auto按钮作用
    bool skipPlayIsActive = false;
    bool autoPlayIsActive = false;
    if(skipPlay->isActive())
    {
        isSkip = false;
        skipPlay->stop();
        skipPlayIsActive = true; //进行效果暂存
    }
    if(isAuto)
    {
        isAuto = false;
        autoPlayIsActive = true;
    }


    vecChoice = chapterMap[currentChapter]->getChoice()[currentSection];
    forbidClickToNext = true;        //禁止通过直接点击进入下一节

    for(int i = 0;i < vecChoice.size();i++)
    {
        vecChoice[i]->setParent(this);
        vecChoice[i]->move(vecChoice[i]->getPos());

        vecChoice[i]->textLabel->move(vecChoice[i]->getTextPos());
        QFont tempFont;
        tempFont = textFrame->getFont();
        tempFont.setPointSize(textFrame->getFont().pointSize()+vecChoice[i]->getfontDelta());
        vecChoice[i]->textLabel->setFont(tempFont);

        vecChoice[i]->show();
        //vecChoice[i]->setWindowModality(Qt::ApplicationModal);

        //隐藏当前周目不可见选项
//        for(QVector<int>::iterator it = vecChoice[i]->getShowAfterChapter().begin();it!=vecChoice[i]->getShowAfterChapter().end();it++)
//        {
//            if(*it == 0)
//            {
//                continue;
//            }
//            qDebug()<<i<<"::"<<*it;
//            //qDebug()<<sd->haveRead[*it];
//            if(sd->haveRead[*it] != -1)
//            {
//                vecChoice[i]->hide();
//                break;
//            }
//        }

        for(int it = 0;it < vecChoice[i]->getShowAfterChapter().size();it++)
        {
            if(vecChoice[i]->getShowAfterChapter()[it] == 0)
            {
                continue;
            }
            //qDebug()<<i<<"::"<<vecChoice[i]->getShowAfterChapter()[it];
            //qDebug()<<sd->haveRead[*it];
            if(sd->haveRead[vecChoice[i]->getShowAfterChapter()[it]] != -1)
            {
                vecChoice[i]->hide();
                break;
            }
        }

        connect(vecChoice[i],&QPushButton::clicked,this,[=](){
            //qDebug()<<"clicked";
            nextChapter = vecChoice[i]->getNext();
            for(int j = 0;j < vecChoice.size();j++)
            {
                vecChoice[j]->hide();
                disconnect(vecChoice[i],0,0,0);
                //一定要disconnect！！！不然多次newgame后产生多次connect会导致多次响应，debug了一下午！！！！！淦！！！！！！
            }
            //在历史记录中体现选择项
            hisList->item(hisList->count()-1)->setText(hisList->item(hisList->count()-1)->text()+vecChoice[i]->textLabel->text());
            forbidClickToNext = false;
            if(skipPlayIsActive)
            {
                isSkip = true;
                skipPlay->start();
            }
            if(autoPlayIsActive)
            {
                isAuto = true;
            }
            skipS->setEnabled(true);
            autoS->setEnabled(true);
            hideB->setEnabled(true);
            previousB->setEnabled(true);
            nextB->setEnabled(true);
            playNextScene();
        });
        //在出选项的时候返回标题：
        connect(this,&ScenePlayer::backMain,this,[=](){
            vecChoice[i]->hide();
            disconnect(vecChoice[i],0,0,0);
            forbidClickToNext = false;
            skipS->setEnabled(true);
            autoS->setEnabled(true);
            hideB->setEnabled(true);
            previousB->setEnabled(true);
            nextB->setEnabled(true);
        });
    }
}

void ScenePlayer::playSound()
{
    if(!chapterMap[currentChapter]->getSound().contains(currentSection))
    {
        return;
    }
    QVector<Sound> vecS = chapterMap[currentChapter]->getSound()[currentSection];
    for(int i = 0;i < vecS.size();i++)
    {
        QMediaPlayer* player = new QMediaPlayer(this);
        player->setVolume(bgmVolume*mainVolume/100);
        //vecSoundPlayer.push_back(player);
        player->setMedia(QUrl::fromLocalFile(vecS[i].getSoundPath()));
        QTimer::singleShot(vecS[i].getStart()*1000,this,[=](){
            player->play();
        });//延时播放

        auto conn = std::make_shared<QMetaObject::Connection>();
        *conn=connect(this,&ScenePlayer::next,player,[=](){
            player->setVolume(0);
            // qDebug()<<"next";
            disconnect(*conn);
        },Qt::UniqueConnection);
        connect(player,&QMediaPlayer::mediaStatusChanged,this,[=](QMediaPlayer::MediaStatus status){
            if(status == QMediaPlayer::EndOfMedia)
            {
                disconnect(*conn);
                disconnect(player,&QMediaPlayer::mediaStatusChanged,0,0);
                player->deleteLater();
            }
        },Qt::UniqueConnection);//放完销毁


        //强制结束delete产生冲突?!!强制结束只改变音量
        //delete时disconnect改变音量的连接
        //又debug了一个半小时。。。。。。。。。。。。。。。
        //看起来很丑但至少能跑。。。。。。。。。。

    }
}

void ScenePlayer::playVocal()
{
    if(!chapterMap[currentChapter]->getVocal().contains(currentSection)||isSkip)
    {
        vocalIsNull = true;
        return;
    }
    vocalIsNull = false;
    vocalPlayer->setMedia(QUrl::fromLocalFile(chapterMap[currentChapter]->getVocal()[currentSection]));
    vocalPlayer->setVolume(vocalVolume*mainVolume/100);
    vocalPlayer->play();
}

void ScenePlayer::playCG()
{
    if(!chapterMap[currentChapter]->getCg().contains(currentSection))
    {
        return;
    }
    QString path = chapterMap[currentChapter]->getCg()[currentSection];
    if(path != "none")
    {
        QImage ima(path);
        QPalette palette =currentCg->palette();
        palette.setBrush(QPalette::Window,QBrush(ima));
        currentCg->setAutoFillBackground(true);                   //要写这句！！！
        currentCg->setPalette(palette);
        currentCg->show();
    }
    else
    {
        currentCg->hide();
    }
}


void ScenePlayer::playSpecial()
{
    if(!chapterMap[currentChapter]->getSpecial().contains(currentSection))
    {
        return;
    }
    QVector<Special> vecS = chapterMap[currentChapter]->getSpecial()[currentSection];
    for(int i = 0;i < vecS.size();i++)
    {
        QLabel* mLabel = new QLabel(this);
        mLabel->move(vecS[i].getPos());
        mLabel->setFixedSize(200,200);
        mLabel->setMovie(vecS[i].getSpecial());
        QTimer::singleShot(vecS[i].getStart()*1000,this,[=](){
            mLabel->show();
            vecS[i].getSpecial()->start();
            auto conn = std::make_shared<QMetaObject::Connection>();
            *conn=connect(this,&ScenePlayer::next,mLabel,[=](){
                mLabel->hide();
                disconnect(*conn);
            },Qt::UniqueConnection);

            connect(vecS[i].getSpecial(),&QMovie::frameChanged,[=](int c){
                if(c == vecS[i].getSpecial()->frameCount() - 1)        //最后一帧即停止
                {
                    vecS[i].getSpecial()->stop();
                    mLabel->deleteLater();
                    disconnect(vecS[i].getSpecial(),0,0,0);
                    disconnect(*conn);
                }
            });

        });
    }
}


void ScenePlayer::playPerform()
{
    if(!chapterMap[currentChapter]->getPerform().contains(currentSection))
    {
        return;
    }
    QVector<Figure> vecF = chapterMap[currentChapter]->getPerform()[currentSection];
    performPlayer->playPerform(vecF);
    performPlayer->show();

    performPlayer_jr->playPerform(vecF);
    performPlayer_jr->show();
}





ScenePlayer::ScenePlayer(SaveData * s, Data* d, QWidget *parent) : QWidget(parent)
{
    data = d;
    sd = s;
    nameFrame = d->getNameFrame();
    textFrame = d->getTextFrame();
    chapterMap = d->getChapterMap();
    this->setFixedSize(d->getSize());
    this->move(0,0);
    this->setAutoFillBackground(true);                              //要写这句才能上色！！！

    bgmPlayer = new BgmPlayer(this);
    vocalPlayer = new QMediaPlayer(this);



    connect(vocalPlayer,&QMediaPlayer::stateChanged,this,[=](QMediaPlayer::State state){
        if(isAuto && ( (state == QMediaPlayer::StoppedState) ))
        {
            QTimer::singleShot(autoSpeed,this,[=](){
                this->playNextScene();
            });
        }
        if(state == QMediaPlayer::PlayingState)
        {
            bgmPlayer->setVolume(mainVolume*bgmVolumeWhenVocal/100);
        }
        if(state == QMediaPlayer::StoppedState)
        {
            bgmPlayer->setVolume(mainVolume*bgmVolume/100);
        }

    });
    connect(this,&ScenePlayer::next,vocalPlayer,[=](){
        vocalPlayer->stop();
    });


    {

        performPlayer = new PerformPlayer(this);
        performPlayer->move(0,0);
        performPlayer->setFixedSize(this->size());



        //从底到顶依次创建Widget
        currentCg = new QWidget(this);
        currentCg->move(0,0);
        currentCg->setFixedSize(d->getSize());



        nameBackLabel = new QLabel(this);
        nameBackLabel->move(nameFrame->getBackPoint());
        nameBackLabel->setFixedSize(nameFrame->getBackSize());
        nameBackLabel->setPixmap(*nameFrame->getPix());
        nameBackLabel->setFont(nameFrame->getFont());
        nameBackLabel->show();

        textBackLabel = new QLabel(this);
        textBackLabel->move(textFrame->getBackPoint());
        textBackLabel->setFixedSize(textFrame->getBackSize());
        textBackLabel->setPixmap(*textFrame->getPix());
        textBackLabel->show();


        nameLabel = new QLabel(nameBackLabel);
        nameLabel->move(nameFrame->getTextPoint());
        nameLabel->setFixedSize(nameFrame->getTextSize());
        nameLabel->setFont(nameFrame->getFont());
        nameLabel->setAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
        nameLabel->setWordWrap(true);


        textLabel = new TextLabel(textBackLabel);
        textLabel->move(textFrame->getTextPoint());
        textLabel->setFixedSize(textFrame->getTextSize());
        textLabel->setFont(textFrame->getFont());
        textLabel->setAlignment(Qt::AlignTop);
        textLabel->setWordWrap(true);

        connect(textLabel,&TextLabel::isOver,this,[=](){
            dialogIsGradual = false;
            if(vocalIsNull && isAuto)
            {
                QTimer::singleShot(1000+autoSpeed,this,[=](){playNextScene();});
            }
        },Qt::UniqueConnection);


        performPlayer_jr = new PerformPlayerJr(textBackLabel);
        performPlayer_jr->move(0,0);
        performPlayer_jr->setFixedSize(textBackLabel->size());

        connect(this,&ScenePlayer::next,this,[=](){
            performPlayer->hide();                                  //留着，不然无法显示，不知道为什么
            performPlayer->clearPerform();
            performPlayer_jr->hide();
            performPlayer_jr->clearPerform();
        });




        hisList = new QListWidget(this);
        hisList->setFixedSize(d->getSize());
        hisList->move(0,0);
        hisList->setStyleSheet(d->getHistoryStyleSheet());
        hisList->setFocusPolicy(Qt::NoFocus);
//"/*设置垂直滚动的全局属性值*/\
//QScrollBar:vertical\
//{\
//    width:20px;\
//    background:rgba(0,0,0,0%);\
//    margin:0px,0px,0px,0px;\
//    padding-top:0px;\
//    padding-bottom:0px;\
//}\
///*设置垂直滚动的滚动条属性值*/\
//QScrollBar::handle:vertical\
//{\
//    width:20px;\
//    background:rgba(0,0,0,25%);\
//    border-radius:2px;\
//    min-height:20;\
//}\
///*设置垂直滚动的滚动槽属性值*/\
//QScrollBar::handle:vertical:hover\
//{\
//    width:20px;\
//    background:rgba(0,0,0,50%);\
//    border-radius:2px;\
//    min-height:20;\
//}\
///*设置垂直滚动的上下端的箭头属性值*/\
//QScrollBar::add-line:vertical,QScrollBar::sub-line:vertical\
//{\
//    height:20px;width:20px;\
//}\
///*设置垂直滚动的下端箭头到滚动条之间的滚动槽属性值*/\
//QScrollBar::add-page:vertical\
//{\
//    background:rgba(0,255,255,10%);\
//    border-radius:2px;\
//}\
///*设置垂直滚动的上端箭头到滚动条之间的滚动槽属性值*/\
//QScrollBar::sub-page:vertical\
//{\
//    background:rgba(0,255,255,10%);\
//    border-radius:2px;\
//}\
//QListWidget\
//{\
//    border:0px;\
//    background-color:rgba(0,0,0,50);\
//}\
///*列表每个item的默认属性值*/\
//QListWidget::Item\
//{\
//    border:10px solid rgba(255,255,255,10);\
//    background-color: rgba(0,0,0,20);\
//}\
///*列表每个item在鼠标移到上面时的属性值*/\
//QListWidget::Item:hover\
//{\
//    background-color:rgba(0,0,0,30);\
//}\
///*列表每个item在被选中时的属性值*/\
//QListWidget::item:selected\
//{\
//    background-color:rgba(0,0,0,50);\
//}"





        NewPushButton* btn = new NewPushButton(*d->getOtherPlayerBtn()[1]);
        btn->setParent(hisList);
        btn->move(btn->getPos());
        connect(btn,&QPushButton::clicked,this,[=](){
            nameBackLabel->show();
            textBackLabel->show();
            for(int i = 0;i<vecToolBtn.size();i++)
            {
                vecToolBtn[i]->show();
            }
            for(int i = 0;i<vecToolSwitch.size();i++)
            {
                vecToolSwitch[i]->show();
            }
            hisList->hide();
        });
        hisList->hide();
    }


    skipPlay = new QTimer(this);
    connect(skipPlay,&QTimer::timeout,this,&ScenePlayer::playNextScene);

    vecToolBtn = d->getSceneBtn();
    vecToolSwitch = d->getSceneSwitch();
    {
        unlockS = d->getSceneSwitch()[0];
        autoS = d->getSceneSwitch()[1];
        skipS = d->getSceneSwitch()[2];
        qsaveB = d->getSceneBtn()[0];
        qloadB = d->getSceneBtn()[1];
        saveB = d->getSceneBtn()[2];
        loadB = d->getSceneBtn()[3];
        previousB = d->getSceneBtn()[4];
        logB = d->getSceneBtn()[5];
        nextB = d->getSceneBtn()[6];
        hideB = d->getSceneBtn()[7];
        configB = d->getSceneBtn()[8];
        homepageB = d->getSceneBtn()[9];
        for(int i = 0;i<vecToolBtn.size();i++)
        {
            vecToolBtn[i]->setParent(this);
            vecToolBtn[i]->move(vecToolBtn[i]->getPos());
        }
        for(int i = 0;i<vecToolSwitch.size();i++)
        {
            vecToolSwitch[i]->setParent(this);
            vecToolSwitch[i]->move(vecToolSwitch[i]->getPos());
        }

    }

    connect(unlockS,&SwitchButton::toggled,[=](bool c){
        if(c)
        {
            for(int i = 0;i<vecToolBtn.size();i++)
            {
                vecToolBtn[i]->setUnlock(true);
            }
            for(int i = 0;i<vecToolSwitch.size();i++)
            {
                vecToolSwitch[i]->setUnlock(true);
            }
        }
        else
        {
            for(int i = 0;i<vecToolBtn.size();i++)
            {
                vecToolBtn[i]->setUnlock(false);
            }
            for(int i = 0;i<vecToolSwitch.size();i++)
            {
                vecToolSwitch[i]->setUnlock(false);
            }

        }
    });
    connect(autoS,&SwitchButton::toggled,[=](bool c){
        if(c)
        {
            if(!dialogIsGradual && (vocalPlayer->state() != QMediaPlayer::PlayingState) )
            {
                playNextScene();//如果没放完就按就放了之后connect自动下一节，如果放完了再按就直接手动下一节
            }
            if(skipS->isToggled())//若skip正在运行则停止skip
            {
                skipS->cancel();//内部会发送信号停止计时器，相当于关掉开关
                isSkip = false;
            }
            isAuto = true;
        }
        else
        {
            isAuto = false;
        }

    });
    connect(skipS,&SwitchButton::toggled,[=](bool c){
        if(c)
        {
            if(autoS->isToggled())//若auto正在运行则停止auto
            {
                autoS->cancel();
                isAuto = false;
            }
            skipPlay->start(100+skipSpeed);
            isSkip = true;
        }
        else
        {
            skipPlay->stop();
            isSkip = false;
        }
    });


    connect(qsaveB,&NewPushButton::clicked,[=](){
        this->cancelAutoAndSkip();
        emit qSave(currentChapter,currentSection,previousChapter,nextChapter);
        //快速存档
    });
    connect(qloadB,&NewPushButton::clicked,[=](){
        this->cancelAutoAndSkip();
        emit qLoad();
    });
    connect(saveB,&NewPushButton::clicked,[=](){
        this->cancelAutoAndSkip();
        QPixmap* pixmap = new QPixmap(size());
        nameBackLabel->hide();
        textBackLabel->hide();
        for(int i = 0;i<vecToolBtn.size();i++)
        {
            vecToolBtn[i]->hide();
            vecToolBtn[i]->hide();
        }
        for(int i = 0;i<vecToolSwitch.size();i++)
        {
            vecToolSwitch[i]->hide();
            vecToolSwitch[i]->hide();
        }
        render(pixmap);//保存当前窗口
        *pixmap = pixmap->scaled(d->getDataPlayerBtn()[0]->size,Qt::KeepAspectRatio,Qt::SmoothTransformation);
        nameBackLabel->show();
        textBackLabel->show();
        for(int i = 0;i<vecToolBtn.size();i++)
        {
            vecToolBtn[i]->show();
            vecToolBtn[i]->show();
        }
        for(int i = 0;i<vecToolSwitch.size();i++)
        {
            vecToolSwitch[i]->show();
            vecToolSwitch[i]->show();
        }
        emit toSave(currentChapter,currentSection,previousChapter,nextChapter
                    ,pixmap,chapterMap[currentChapter]->getDialog()[currentSection]->getText());
    });
    connect(loadB,&NewPushButton::clicked,[=](){
        this->cancelAutoAndSkip();
        emit toLoad();
    });
    connect(previousB,&NewPushButton::clicked,[=](){
        this->cancelAutoAndSkip();
        if(previousChapter != -1)
        {
            emit next();
            bgmPlayer->playBgm("none");
            currentCg->hide();
            currentChapter = previousChapter;
            currentSection = 1;
            nextChapter = -1;
            previousChapter = -1;
            playScene(currentChapter,currentSection);        //可能需要优化？
        }
    });
    connect(logB,&NewPushButton::clicked,[=](){
        this->cancelAutoAndSkip();
        nameBackLabel->hide();
        textBackLabel->hide();
        for(int i = 0;i<vecToolBtn.size();i++)
        {
            vecToolBtn[i]->hide();
        }
        for(int i = 0;i<vecToolSwitch.size();i++)
        {
            vecToolSwitch[i]->hide();
        }
        this->cancelAutoAndSkip();
        isHistory = true;
        hisList->show();
    });
    connect(hisList,&QListWidget::itemClicked,this,[=](QListWidgetItem* it){
        this->endScene();
        this->playRandomScene(itemMap[it]->currentChapter
                              ,itemMap[it]->currentSection
                              ,itemMap[it]->previousChapter
                              ,itemMap[it]->nextChapter);
        nameBackLabel->show();
        textBackLabel->show();
        for(int i = 0;i<vecToolBtn.size();i++)
        {
            vecToolBtn[i]->show();
        }
        for(int i = 0;i<vecToolSwitch.size();i++)
        {
            vecToolSwitch[i]->show();
        }
        isHistory = false;
        hisList->hide();
    });
    connect(nextB,&NewPushButton::clicked,[=](){
        this->cancelAutoAndSkip();
        if(nextChapter!=-1)
        {
            currentSection = -1;         //强行结束这一章
            playNextScene();
        }
    });
    connect(hideB,&NewPushButton::clicked,[=](){
        nameBackLabel->hide();
        textBackLabel->hide();
        for(int i = 0;i<vecToolBtn.size();i++)
        {
            vecToolBtn[i]->hide();
        }
        for(int i = 0;i<vecToolSwitch.size();i++)
        {
            vecToolSwitch[i]->hide();
        }
        this->cancelAutoAndSkip();
        isHide = true;
    });
    connect(configB,&NewPushButton::clicked,[=](){
        this->cancelAutoAndSkip();
        emit toConfig();
    });
    connect(homepageB,&NewPushButton::clicked,[=](){
        this->endScene();
        emit backMain();
    });
}




void ScenePlayer::playScene(int c, int s)
{
    currentChapter = c;
    currentSection = s;
    playDialog();
    playBgm();
    playBackground();
    playChoice();
    playSound();
    playVocal();
    playCG();
    playPerform();
    playSpecial();
}



void ScenePlayer::playNextScene()
{
    if(currentChapter == 0 || currentChapter == -1)       //解决auto模式下，会发生先返回标题并置current=0后执行该函数导致chapterMap[0]的报错问题
    {
        return;
    }
    if(dialogIsGradual)
    {
        textLabel->pressToNext();
        return;
    }
    emit next();       //使得独立并行音效特效等控件不可见
    //    for(int i = 0;i<vecSoundPlayer.size();i++)
    //    {
    //        vecSoundPlayer[i]->stop();
    //    }
    //    vecSoundPlayer.clear();

    //依据dialog判定是否结束，请保证dialog贯穿全文！
    currentSection++;
    if(!chapterMap[currentChapter]->getDialog().contains(currentSection))//如果没有下一节就检查Choice加载下一章
    {
        if(currentSection != -1)//本章已正常读完
        {
            sd->haveRead[currentChapter] = -1;
            //看看要不要改主界面背景         //使用const迭代器，否则会崩溃
            for(QMap<int,QString>::const_iterator it = data->getMainPic().constBegin();it != data->getMainPic().constEnd();it++)
            {
                if(it.key() == currentChapter)
                {
                    sd->mainPicName = it.value();
                    QString currentPath = QCoreApplication::applicationDirPath();
                    QString mainpicPath = currentPath;
                    mainpicPath+=QString("/res/resource/config/");
                    mainpicPath+=sd->mainPicName;
                    QImage* img = new QImage(mainpicPath);
                    sd->mainPic = img;
                }
            }
        }
        previousChapter = currentChapter;
        currentChapter = nextChapter;
        nextChapter = -1;
        currentSection = 1;
    }

    if(currentChapter == 0)//如果接下来的一章为0就返回主界面
    {
        //全部读完了吗？
        bool isAllOver = true;       //假设读完了
        for(QMap<int,int>::const_iterator it = sd->haveRead.constBegin();it!=sd->haveRead.constEnd();it++)
        {
            if(it.value()!=-1)
            {
                isAllOver = false;     //其实没读完
                break;
            }
        }
        sd->galleryIsOpen = isAllOver;
        sd->saveHaveRead();
        this->endScene();
        emit backMain();
    }
    else
    {
        playScene(currentChapter,currentSection);
    }
}

void ScenePlayer::playRandomScene(int c, int s, int p, int n)
{
    hisList->clear();
    //itemMap.clear();
    previousChapter = p;
    nextChapter = n;
    int bgmBeginS = s;
    while(bgmBeginS>0)
    {
        if(!chapterMap[c]->getBgm().contains(bgmBeginS))
        {
            bgmBeginS--;
        }
        else
        {
            bgmPlayer->playBgm(chapterMap[c]->getBgm()[bgmBeginS]);
            break;
        }
    }

    int backBeginS = s;
    while(backBeginS>0)
    {
        if(!chapterMap[c]->getBackground().contains(backBeginS))
        {
            backBeginS--;
        }
        else
        {
            (chapterMap[c]->getBgm()[backBeginS]);
            QPalette palette = this->palette();
            palette.setBrush(QPalette::Window,QBrush(*chapterMap[c]->getBackground()[backBeginS]));
            this->setPalette(palette);
            break;
        }
    }
    currentChapter = c;
    currentSection = s;
    for(int i = 1;i<currentSection;i++)
    {
        QString name = chapterMap[currentChapter]->getDialog()[i]->getName();
        QString text = chapterMap[currentChapter]->getDialog()[i]->getText();

        QListWidgetItem* item = new QListWidgetItem(hisList);
        item->setSizeHint(QSize(hisList->width()*0.9,hisList->height()*0.2));           //改高度？？
        QString histext = "";
        if(name!="")
        {
            histext="【"+name+"】";
        }
        histext=histext+"\n"+text;
        item->setFont(textFrame->getFont());
        item->setText(histext);
        item->setForeground(Qt::white);                                                 //改颜色？？
        SingleData* single = new SingleData(currentChapter,i,previousChapter,nextChapter);
        itemMap.insert(item,single);
    }
    playScene(c,s);
}

void ScenePlayer::endScene()
{
    emit next();
    bgmPlayer->playBgm("none");
    vocalPlayer->stop();
    skipPlay->stop();
    currentCg->hide();
    nextChapter = -1;
    currentChapter = 0;
    currentSection = 1;
    previousChapter = -1;
    this->cancelAutoAndSkip();
    hisList->clear();
    //itemMap.clear();



    //禁用按钮能防止奇奇怪怪的崩溃bug
//        skipS->setEnabled(false);
//        autoS->setEnabled(false);
    //不行这会导致更多bug,,
    //总之不要在快结束的瞬间点击按钮就行了。。。
    //已解决
}

void ScenePlayer::cancelAutoAndSkip()
{
    if(autoS->isToggled())
    {
        autoS->cancel();
        isAuto = false;
    }
    if(skipS->isToggled())
    {
        skipS->cancel();
        isSkip = false;
    }
}

void ScenePlayer::mousePressEvent(QMouseEvent *event)
{
    if(isHide)
    {
        nameBackLabel->show();
        textBackLabel->show();
        for(int i = 0;i<vecToolBtn.size();i++)
        {
            vecToolBtn[i]->show();
        }
        for(int i = 0;i<vecToolSwitch.size();i++)
        {
            vecToolSwitch[i]->show();
        }
        isHide = false;
        return;
    }
    if(autoS->isToggled())
    {
        autoS->cancel();
        isAuto = false;
        return;
    }
    if(skipS->isToggled())
    {
        skipS->cancel();
        isSkip = false;
        return;
    }
    if(!forbidClickToNext)
    {
        playNextScene();
    }
    QWidget::mousePressEvent(event);
}

ScenePlayer::~ScenePlayer()
{

}
