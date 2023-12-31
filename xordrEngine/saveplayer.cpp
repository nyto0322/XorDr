#include "saveplayer.h"



//void SavePlayer::saveData()
//{
//}

//void SavePlayer::showData(SingleData * sd, QWidget * btn)
//{
//    //加载存档画面
//    QLabel* label = new QLabel(sd->dateTime,btn);
//    label->move(25,12);
//}

SavePlayer::SavePlayer(SaveData * sd, Data *d, QWidget *parent) : QWidget(parent)
{
    sdata = sd;
    this->setFixedSize(980,600);
    this->move(0,0);
    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,QBrush(*d->getSaveBackground()));
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


            connect(dataBtn,&QPushButton::clicked,[=](){
                sdata->saveData[i][k] = singleData;
                sdata->save();
                //sdata->load();
                emit saveDataUpdate(i,k);
                btnTime->setText(sdata->saveData[i][k]->dateTime);
                btnPix->setPixmap((*sdata->saveData[i][k]->currentPix).scaled(btnPix->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
                btnText->setText(sdata->saveData[i][k]->currentText);
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


    toSceneBtn = new NewPushButton(*d->getOtherPlayerBtn()[1]);
    toSceneBtn->setParent(this);
    toSceneBtn->move(toSceneBtn->getPos());
    connect(toSceneBtn,&QPushButton::clicked,this,&SavePlayer::toScene);
    toMainBtn = new NewPushButton(*d->getOtherPlayerBtn()[0]);
    toMainBtn->setParent(this);
    toMainBtn->move(toMainBtn->getPos());
    connect(toMainBtn,&QPushButton::clicked,this,&SavePlayer::toMain);
    toLoadBtn = new NewPushButton(*d->getOtherPlayerBtn()[3]);
    toLoadBtn->setParent(this);
    toLoadBtn->move(toLoadBtn->getPos());
    connect(toLoadBtn,&QPushButton::clicked,this,&SavePlayer::toLoad);
}

//void SavePlayer::save(SingleData *s, int i, int j)
//{
//    sdata->saveData[i][j] = s;
//    sdata->save();
//    sdata->load();
//}

void SavePlayer::qSave(int c, int s, int p, int n)
{
    QDateTime time = QDateTime::currentDateTime();
    sdata->qSaveData = new SingleData(c,s,p,n,time.toString("yyyy-MM-dd    hh:mm"),this);
    sdata->save();
}

void SavePlayer::inputSaveData(int c, int s, int p, int n,QPixmap* pix,QString text)
{
    QDateTime time = QDateTime::currentDateTime();
    singleData = new SingleData(c,s,p,n,time.toString("yyyy-MM-dd    hh:mm"),this,text,pix);
}

void SavePlayer::fromScene(bool isS)
{
    isFromScene = isS;
    if(isS)
    {
        toSceneBtn->setEnabled(true);
    }
    else
    {
        toSceneBtn->setEnabled(false);
    }
}
