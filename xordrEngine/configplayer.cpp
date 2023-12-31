#include "configplayer.h"


ConfigPlayer::ConfigPlayer(Data * d, QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(980,600);
    this->move(0,0);
    this->setAutoFillBackground(true);                              //要写这句才能上色！！！
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,QBrush(*d->getConfigBackground()));
    this->setPalette(palette);
    this->show();

    toMainBtn = new NewPushButton(*d->getOtherPlayerBtn()[0]);
    toSceneBtn = new NewPushButton(*d->getOtherPlayerBtn()[1]);
    toMainBtn->setParent(this);
    toSceneBtn->setParent(this);

    toMainBtn->move(toMainBtn->getPos());
    toSceneBtn->move(toSceneBtn->getPos());
    toMainBtn->show();
    toSceneBtn->show();
    connect(toMainBtn,&QPushButton::clicked,this,&ConfigPlayer::toMain);
    connect(toSceneBtn,&QPushButton::clicked,this,&ConfigPlayer::toScene);

    SaveConfig* sConfig = new SaveConfig(this);


    QString m_S = d->getSliderStyleSheet();
    /*QString("QSlider::groove:horizontal{\
                            height: 6px; \
                            left:  -5px; \
                            right: -5px; \
                            border:0px;   \
                            border-radius:10px;  \
                            background:rgba(0,0,0,50);\
                     } \
                     QSlider::handle:horizontal{ \
                            width:  20px; \
                            height: 20px; \
                            margin-top: -7px; \
                            margin-bottom: -7px; \
                            margin-left: 5px; \
                            margin-right: 5px; \
                            border-image:url(C:/Users/Nyto/Desktop/btn.png);\
                    } \
                    QSlider::sub-page:horizontal{\
                            border-radius:10px;  \
                            background:rgba(80,166,234,1);\
                    }");*/

    QLabel* skipSpeedL = new QLabel(this);
    skipSpeedL->setPixmap(*d->getConfigSlider()[0]->imgL);
    skipSpeedL->setGeometry(QRect(d->getConfigSlider()[0]->posL,d->getConfigSlider()[0]->sizeL));
    QSlider* skipSpeedS = new QSlider(Qt::Horizontal,this);
    skipSpeedS->setGeometry(QRect(d->getConfigSlider()[0]->posS,d->getConfigSlider()[0]->sizeS));
    skipSpeedS->setStyleSheet(m_S);
    skipSpeedS->setMinimum(-50);
    skipSpeedS->setMaximum(900);//改！ 按照反函数滑动？
    skipSpeedS->setValue(skipSpeed);
    connect(skipSpeedS,&QSlider::sliderReleased,[=](){
        skipSpeed = skipSpeedS->value();
        sConfig->save();
    });
    QLabel* autoSpeedL = new QLabel(this);
    autoSpeedL->setPixmap(*d->getConfigSlider()[1]->imgL);
    autoSpeedL->setGeometry(QRect(d->getConfigSlider()[1]->posL,d->getConfigSlider()[1]->sizeL));
    QSlider* autoSpeedS = new QSlider(Qt::Horizontal,this);
    autoSpeedS->setGeometry(QRect(d->getConfigSlider()[1]->posS,d->getConfigSlider()[1]->sizeS));
    autoSpeedS->setStyleSheet(m_S);
    autoSpeedS->setMinimum(0);
    autoSpeedS->setMaximum(2000);
    autoSpeedS->setValue(autoSpeed);
    connect(autoSpeedS,&QSlider::sliderReleased,[=](){
        autoSpeed = autoSpeedS->value();
        sConfig->save();
    });
    QLabel* textShowSpeedL = new QLabel("textShowSpeed",this);
    textShowSpeedL->setPixmap(*d->getConfigSlider()[2]->imgL);
    textShowSpeedL->setGeometry(QRect(d->getConfigSlider()[2]->posL,d->getConfigSlider()[2]->sizeL));
    QSlider* textShowSpeedS = new QSlider(Qt::Horizontal,this);
    textShowSpeedS->setGeometry(QRect(d->getConfigSlider()[2]->posS,d->getConfigSlider()[2]->sizeS));
    textShowSpeedS->setStyleSheet(m_S);
    textShowSpeedS->setMinimum(-100);
    textShowSpeedS->setMaximum(400);
    textShowSpeedS->setValue(textShowSpeed);
    connect(textShowSpeedS,&QSlider::sliderReleased,[=](){
        textShowSpeed = textShowSpeedS->value();
        sConfig->save();
    });
    QLabel* textSizeL = new QLabel("textSize",this);
    textSizeL->setPixmap(*d->getConfigSlider()[3]->imgL);
    textSizeL->setGeometry(QRect(d->getConfigSlider()[3]->posL,d->getConfigSlider()[3]->sizeL));
    QSlider* textSizeS = new QSlider(Qt::Horizontal,this);
    textSizeS->setGeometry(QRect(d->getConfigSlider()[3]->posS,d->getConfigSlider()[3]->sizeS));
    textSizeS->setStyleSheet(m_S);
    textSizeS->setMinimum(-10);
    textSizeS->setMaximum(10);
    textSizeS->setValue(textSize);
    connect(textSizeS,&QSlider::sliderReleased,[=](){
        textSize = textSizeS->value();
        sConfig->save();
    });
    QLabel* mainVolumeL = new QLabel("mainVolume",this);
    mainVolumeL->setPixmap(*d->getConfigSlider()[4]->imgL);
    mainVolumeL->setGeometry(QRect(d->getConfigSlider()[4]->posL,d->getConfigSlider()[4]->sizeL));
    QSlider* mainVolumeS = new QSlider(Qt::Horizontal,this);
    mainVolumeS->setGeometry(QRect(d->getConfigSlider()[4]->posS,d->getConfigSlider()[4]->sizeS));
    mainVolumeS->setStyleSheet(m_S);
    mainVolumeS->setMinimum(0);
    mainVolumeS->setMaximum(100);
    mainVolumeS->setValue(mainVolume);
    connect(mainVolumeS,&QSlider::sliderReleased,[=](){
        mainVolume = mainVolumeS->value();
        sConfig->save();
    });
    QLabel* mainSceneBgmVolumeL = new QLabel("mainSceneBgmVolume",this);
    mainSceneBgmVolumeL->setPixmap(*d->getConfigSlider()[5]->imgL);
    mainSceneBgmVolumeL->setGeometry(QRect(d->getConfigSlider()[5]->posL,d->getConfigSlider()[5]->sizeL));
    QSlider* mainSceneBgmVolumeS = new QSlider(Qt::Horizontal,this);
    mainSceneBgmVolumeS->setGeometry(QRect(d->getConfigSlider()[5]->posS,d->getConfigSlider()[5]->sizeS));
    mainSceneBgmVolumeS->setStyleSheet(m_S);
    mainSceneBgmVolumeS->setMinimum(0);
    mainSceneBgmVolumeS->setMaximum(100);
    mainSceneBgmVolumeS->setValue(mainSceneBgmVolume);
    connect(mainSceneBgmVolumeS,&QSlider::sliderReleased,[=](){
        mainSceneBgmVolume = mainSceneBgmVolumeS->value();
        sConfig->save();
    });
    QLabel* vocalVolumeL = new QLabel("vocalVolume",this);
    vocalVolumeL->setPixmap(*d->getConfigSlider()[6]->imgL);
    vocalVolumeL->setGeometry(QRect(d->getConfigSlider()[6]->posL,d->getConfigSlider()[6]->sizeL));
    QSlider* vocalVolumeS = new QSlider(Qt::Horizontal,this);
    vocalVolumeS->setGeometry(QRect(d->getConfigSlider()[6]->posS,d->getConfigSlider()[6]->sizeS));
    vocalVolumeS->setStyleSheet(m_S);
    vocalVolumeS->setMinimum(0);
    vocalVolumeS->setMaximum(100);
    vocalVolumeS->setValue(vocalVolume);
    connect(vocalVolumeS,&QSlider::sliderReleased,[=](){
        vocalVolume = vocalVolumeS->value();
        sConfig->save();
    });
    QLabel* bgmVolumeL = new QLabel("bgmVolume",this);
    bgmVolumeL->setPixmap(*d->getConfigSlider()[7]->imgL);
    bgmVolumeL->setGeometry(QRect(d->getConfigSlider()[7]->posL,d->getConfigSlider()[7]->sizeL));
    QSlider* bgmVolumeS = new QSlider(Qt::Horizontal,this);
    bgmVolumeS->setGeometry(QRect(d->getConfigSlider()[7]->posS,d->getConfigSlider()[7]->sizeS));
    bgmVolumeS->setStyleSheet(m_S);
    bgmVolumeS->setMinimum(0);
    bgmVolumeS->setMaximum(100);
    bgmVolumeS->setValue(bgmVolume);
    connect(bgmVolumeS,&QSlider::sliderReleased,[=](){
        bgmVolume = bgmVolumeS->value();
        sConfig->save();
    });
    QLabel* bgmVolumeWhenVocalL = new QLabel("bgmVolumeWhenVocal",this);
    bgmVolumeWhenVocalL->setPixmap(*d->getConfigSlider()[8]->imgL);
    bgmVolumeWhenVocalL->setGeometry(QRect(d->getConfigSlider()[8]->posL,d->getConfigSlider()[8]->sizeL));
    QSlider* bgmVolumeWhenVocalS = new QSlider(Qt::Horizontal,this);
    bgmVolumeWhenVocalS->setGeometry(QRect(d->getConfigSlider()[8]->posS,d->getConfigSlider()[8]->sizeS));
    bgmVolumeWhenVocalS->setStyleSheet(m_S);
    bgmVolumeWhenVocalS->setMinimum(0);
    bgmVolumeWhenVocalS->setMaximum(100);
    bgmVolumeWhenVocalS->setValue(bgmVolumeWhenVocal);
    connect(bgmVolumeWhenVocalS,&QSlider::sliderReleased,[=](){
        bgmVolumeWhenVocal = bgmVolumeWhenVocalS->value();
        sConfig->save();
    });
    QLabel* soundVolumeL = new QLabel("soundVolume",this);
    soundVolumeL->setPixmap(*d->getConfigSlider()[9]->imgL);
    soundVolumeL->setGeometry(QRect(d->getConfigSlider()[9]->posL,d->getConfigSlider()[9]->sizeL));
    QSlider* soundVolumeS = new QSlider(Qt::Horizontal,this);
    soundVolumeS->setGeometry(QRect(d->getConfigSlider()[9]->posS,d->getConfigSlider()[9]->sizeS));
    soundVolumeS->setStyleSheet(m_S);
    soundVolumeS->setMinimum(0);
    soundVolumeS->setMaximum(100);
    soundVolumeS->setValue(soundVolume);
    connect(soundVolumeS,&QSlider::sliderReleased,[=](){
        soundVolume = soundVolumeS->value();
        sConfig->save();
    });
}

void ConfigPlayer::isFromScene(bool isS)
{
    if(isS)
    {
        toSceneBtn->setEnabled(true);
    }
    else
    {
        toSceneBtn->setEnabled(false);
    }
}
