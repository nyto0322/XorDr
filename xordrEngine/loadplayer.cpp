#include "loadplayer.h"


void LoadPlayer::showData()
{

}

LoadPlayer::LoadPlayer(SaveData* sd, Data *d, QWidget *parent) : QWidget(parent)
{
    sdata = sd;
    this->setFixedSize(980,600);
    this->move(0,0);
    this->setAutoFillBackground(true);                              //要写这句才能上色！！！
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,QBrush(*d->getLoadBackground()));
    this->setPalette(palette);
    this->show();



    QStackedWidget* stack = new QStackedWidget(this);
    stack->setFixedSize(980,600);
    for(int i = 0;i<10;i++)
    {
        QWidget* w = new QWidget(this);
        w->setFixedSize(980,600);
        stack->addWidget(w);
        for(int k = 0;k<10;k++)
        {
            NewPushButton* dataBtn = new NewPushButton(*d->getDataPlayerBtn()[k]);
            dataBtn->setParent(w);
            dataBtn->move(dataBtn->getPos());
            QLabel* btnTime = new QLabel(dataBtn);
            btnTime->setAlignment(Qt::AlignLeft|Qt::AlignTop);
            btnTime->setText(sdata->saveData[i][k]->dateTime);
            btnTime->setFixedSize(dataBtn->size);
            btnTime->move(25,12);

            QLabel* btnPix = new QLabel(dataBtn);
            btnPix->setAlignment(Qt::AlignLeft|Qt::AlignTop);
            btnPix->setFixedSize(dataBtn->size*0.8);
            if(!sdata->saveData[i][k]->currentPix->isNull())
            {
                btnPix->setPixmap((*sdata->saveData[i][k]->currentPix).scaled(btnPix->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
            }
            btnPix->move(15,30);

            QLabel* btnText = new QLabel(dataBtn);
            btnText->setAlignment(Qt::AlignLeft|Qt::AlignTop);
            btnText->setWordWrap(true);
            btnText->setText(sdata->saveData[i][k]->currentText);
            btnText->setFixedSize(dataBtn->size*0.8);
            btnText->move(12,110);

            timeLabel[i][k] = btnTime;
            pixLabel[i][k] = btnPix;
            textLabel[i][k] = btnText;

            connect(dataBtn,&QPushButton::clicked,[=](){
                emit loadData(sdata->saveData[i][k]->currentChapter
                              ,sdata->saveData[i][k]->currentSection
                              ,sdata->saveData[i][k]->previousChapter
                              ,sdata->saveData[i][k]->nextChapter);
            });
        }
        SwitchButton* indexBtn = new SwitchButton(*d->getDataPlayerIndexBtn()[i]);
        indexBtn->setParent(this);
        indexBtn->move(indexBtn->getPos());
        vecIndexBtn.push_back(indexBtn);
        connect(indexBtn,&SwitchButton::toggled,[=](){
            stack->setCurrentIndex(i);
            indexBtn->setKeep(true);
            for(int j = 0;j<10;j++)
            {
                if(j!=i)
                {
                    vecIndexBtn[j]->init();
                }
            }
        });
    }
    stack->setCurrentIndex(0);
    vecIndexBtn[0]->setKeep(true);
    vecIndexBtn[0]->light();












    toMainBtn = new NewPushButton(*d->getOtherPlayerBtn()[0]);
    toSceneBtn = new NewPushButton(*d->getOtherPlayerBtn()[1]);
    toSaveBtn = new NewPushButton(*d->getOtherPlayerBtn()[2]);
    toMainBtn->setParent(this);
    toSceneBtn->setParent(this);
    toSaveBtn->setParent(this);

    toMainBtn->move(toMainBtn->getPos());
    toSceneBtn->move(toSceneBtn->getPos());
    toSaveBtn->move(toSaveBtn->getPos());
    toMainBtn->show();
    toSceneBtn->show();
    toSaveBtn->show();
    connect(toMainBtn,&QPushButton::clicked,this,&LoadPlayer::toMain);
    connect(toSceneBtn,&QPushButton::clicked,this,&LoadPlayer::toScene);
    connect(toSaveBtn,&QPushButton::clicked,this,&LoadPlayer::toSave);
}


void LoadPlayer::fromScene(bool isS)
{
    isFromScene = isS;
    if(isS)
    {
        toSceneBtn->setEnabled(true);
        toSaveBtn->setEnabled(true);
    }
    else
    {
        toSceneBtn->setEnabled(false);
        toSaveBtn->setEnabled(false);
    }
}

SingleData* LoadPlayer::qLoad()
{
    return sdata->qSaveData;
}

void LoadPlayer::saveDataUpdate(int i,int k)
{
    timeLabel[i][k] ->setText(sdata->saveData[i][k]->dateTime);
    pixLabel[i][k]->setPixmap((*sdata->saveData[i][k]->currentPix).scaled(pixLabel[i][k]->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
    textLabel[i][k] ->setText(sdata->saveData[i][k]->currentText);
}
