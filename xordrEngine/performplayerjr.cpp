#include "performplayerjr.h"
#include "performplayer.h"
#include <QTimer>
#include <QDebug>

PerformPlayerJr::PerformPlayerJr(QWidget *parent) : QWidget(parent)
{

}


void PerformPlayerJr::playPerform(QVector<Figure> vecF)
{
    vecPerform = vecF;
    for(int i = 0;i < vecPerform.size();i++)
    {
//        if(vecPerform[i].getJrSize()!=0)
//        {
//            QLabel* jrMainLabel = new QLabel(jrParent);
//            QLabel* jrStatusLabel = new QLabel(jrParent);
//            jrMainLabel->move(0,0);
//            jrStatusLabel->move(0,0);
//            jrMainLabel->setFixedSize(jrParent->height(),jrParent->height());
//            jrStatusLabel->setFixedSize(jrParent->height(),jrParent->height());

//            QPixmap mainfig = QPixmap::fromImage(*vecPerform[i].getMainfig()).scaled(jrMainLabel->size(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
//            QPixmap status = QPixmap::fromImage(*vecPerform[i].getStatus()).scaled(jrStatusLabel->size(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);


//            jrMainLabel->setPixmap(mainfig);
//            jrStatusLabel->setPixmap(status);

//            //默认hide状态，防止快速点击导致之后创建的被显示出来
//            jrMainLabel->hide();
//            jrStatusLabel->hide();


//            if(!isnext)
//            {
//                QTimer::singleShot(vecPerform[i].getStart()*1000,this,[=](){
//                    jrMainLabel->show();
//                    jrStatusLabel->show();
//                });
//            }


//            if(vecPerform[i].getDuration()!=-1)
//            {
//                QTimer::singleShot(vecPerform[i].getDuration()*1000+vecPerform[i].getStart()*1000,this,[=](){
//                    jrMainLabel->hide();
//                    jrStatusLabel->hide();
//                });
//            }
//        }

        if(vecPerform[i].getJrSize()==0)
        {
            continue;
        }

        QLabel* mainLabel = new QLabel(this);
        QLabel* statusLabel = new QLabel(mainLabel);
        mainLabel->move(0,0);
        mainLabel->setFixedSize(parentWidget()->height(),parentWidget()->height());
        statusLabel->move(0,0);
        statusLabel->setFixedSize(mainLabel->size());

        mainLabel->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
        statusLabel->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);

        QPixmap mainfig = QPixmap::fromImage(*vecF[i].getMainfig()).scaled(mainLabel->size(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        QPixmap status = QPixmap::fromImage(*vecF[i].getStatus()).scaled(statusLabel->size(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);


        mainLabel->setPixmap(mainfig);
        statusLabel->setPixmap(status);

        mainLabel->hide();
        statusLabel->hide();

        QTimer::singleShot(vecPerform[i].getStart()*1000,this,[=](){
            mainLabel->show();
            statusLabel->show();
        });

        if(vecPerform[i].getDuration()!=-1)
        {
            QTimer::singleShot(vecPerform[i].getDuration()*1000+vecPerform[i].getStart()*1000,this,[=](){
                mainLabel->hide();
                statusLabel->hide();
//                deleteLaterAndLater(mainLabel);
//                deleteLaterAndLater(statusLabel);
            });

        }
//        else
//        {
//            connect(this,&PerformPlayer::deleteBegin,this,[=](){
//                deleteLaterAndLater(mainLabel);
//                deleteLaterAndLater(statusLabel);
//            });
//        }
        VecMainLabel.push_back(mainLabel);
        VecStatusLabel.push_back(statusLabel);
    }
}

void PerformPlayerJr::clearPerform()
{
    for(int i = 0;i<VecMainLabel.size();i++)
    {
        VecMainLabel[i]->clear();
        //deleteLaterAndLater(VecMainLabel[i]);

    }
    for(int i = 0;i<VecStatusLabel.size();i++)
    {
        VecStatusLabel[i]->clear();
        //deleteLaterAndLater(VecStatusLabel[i]);
    }
}

//void PerformPlayerJr::deleteLaterAndLater(QWidget* w)
//{
//    for(int i = 0;i<vecTimer.size();i++)
//    {
//        vecTimer[i]->stop();
//        vecTimer[i]->deleteLater();
//    }
//    vecTimer.clear();

//     //w->deleteLater();
//    //同样的问题，，，
//}
