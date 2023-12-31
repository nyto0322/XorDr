#include "performplayer.h"



PerformPlayer::PerformPlayer(QWidget *parentMain) : QWidget(parentMain)
{
}

void PerformPlayer::playPerform(QVector<Figure> vecF)
{
    vecPerform = vecF;

    for(int i = 0;i < vecPerform.size();i++)
    {
        QLabel* mainLabel = new QLabel(this);
        QLabel* statusLabel = new QLabel(mainLabel);
        vecMainLabel.push_back(mainLabel);
        vecStatusLabel.push_back(statusLabel);

        mainLabel->move(vecPerform[i].getPos());
        mainLabel->setFixedSize(vecPerform[i].getMainfig()->size()*vecPerform[i].getSize());
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
        //默认hide状态，防止快速点击导致之后创建的被显示出来


        QTimer::singleShot(vecPerform[i].getStart()*1000,this,[=](){
//            if(mainLabel!=nullptr)
//            {
                mainLabel->show();
//            }
//            if(statusLabel!=nullptr)
//            {
                statusLabel->show();
//            }
        });


        if(vecPerform[i].getAnimation()!="none")
        {
            playAnimation(mainLabel,i);
        }




        if(vecPerform[i].getDuration()!=-1)
        {
            QTimer::singleShot(vecPerform[i].getDuration()*1000+vecPerform[i].getStart()*1000,this,[=]()mutable{
//                if(mainLabel!=nullptr)
//                {
                    mainLabel->hide();
//                    mainLabel->deleteLater();
//                    mainLabel=nullptr;
//                }
//                if(statusLabel!=nullptr)
//                {
                    statusLabel->hide();
//                    statusLabel->deleteLater();
//                    statusLabel=nullptr;
//                }


//                mainLabel->deleteLater();
//                statusLabel->deleteLater();
            });
        }
//        else           //一直持续下去的perform
//        {
//            connect(this,&PerformPlayer::deleteBegin,this,[=]()mutable{
//                QTimer::singleShot(vecPerform[i].getStart()*1000,this,[=]()mutable{  //保证在show之后delete
//                    if(mainLabel!=nullptr)
//                    {
//                        mainLabel->deleteLater();
//                        mainLabel=nullptr;
//                    }
//                    if(statusLabel!=nullptr)
//                    {
//                        statusLabel->deleteLater();
//                        statusLabel=nullptr;
//                    }
//                 });
//            });
//        }
    }
}

void PerformPlayer::playAnimation(QLabel * label, int i)
{
    if(vecPerform[i].getAnimation()=="bounce")
    {
        QTimer::singleShot(vecPerform[i].getAniStart()*1000,this,[=](){
            QPropertyAnimation * animation1 = new QPropertyAnimation(label,"geometry");
            animation1->setDuration(vecPerform[i].getAniDuration()*1000);
            animation1->setStartValue(QRect(label->x(),label->y(),label->width(),label->height()));
            animation1->setEasingCurve(QEasingCurve::InOutQuad);

            int range = vecPerform[i].getAniRange();
            int shakeCount = 20;
            double step = 1.0/shakeCount;
            for(int i = 1; i < shakeCount; i++)
            {
                range = i&1 ? -range : range;
                animation1->setKeyValueAt(step*i,QRect(label->x(),label->y()+range,label->width(),label->height()));
            }
            animation1->setEndValue(QRect(label->x(),label->y(),label->width(),label->height()));
            animation1->start(QAbstractAnimation::DeleteWhenStopped);
        });
        return;
    }
    if(vecPerform[i].getAnimation()=="tremble")
    {
        QTimer::singleShot(vecPerform[i].getAniStart()*1000,this,[=](){
            QPropertyAnimation * animation1 = new QPropertyAnimation(label,"geometry");
            animation1->setDuration(vecPerform[i].getAniDuration()*1000);
            animation1->setStartValue(QRect(label->x(),label->y(),label->width(),label->height()));
            animation1->setEasingCurve(QEasingCurve::InOutQuad);

            int range = vecPerform[i].getAniRange();
            int shakeCount = 20;
            double step = 1.0/shakeCount;
            for(int i = 1; i < shakeCount; i++)
            {
                range = i&1 ? -range : range;
                animation1->setKeyValueAt(step*i,QRect(label->x()+range,label->y(),label->width(),label->height()));
            }
            animation1->setEndValue(QRect(label->x(),label->y(),label->width(),label->height()));
            animation1->start(QAbstractAnimation::DeleteWhenStopped);
        });
        return;
    }
    if(vecPerform[i].getAnimation()=="moveX")
    {
        QTimer::singleShot(vecPerform[i].getAniStart()*1000,this,[=](){
            QPropertyAnimation * animation1 = new QPropertyAnimation(label,"geometry");
            animation1->setDuration(vecPerform[i].getAniDuration()*1000);
            animation1->setStartValue(QRect(label->x(),label->y(),label->width(),label->height()));
            animation1->setEasingCurve(QEasingCurve::InOutQuad);

            int range = vecPerform[i].getAniRange();
            animation1->setEndValue(QRect(label->x()+range,label->y(),label->width(),label->height()));
            animation1->start(QAbstractAnimation::DeleteWhenStopped);
        });
        return;
    }
    if(vecPerform[i].getAnimation()=="moveY")
    {
        QTimer::singleShot(vecPerform[i].getAniStart()*1000,this,[=](){
            QPropertyAnimation * animation1 = new QPropertyAnimation(label,"geometry");
            animation1->setDuration(vecPerform[i].getAniDuration()*1000);
            animation1->setStartValue(QRect(label->x(),label->y(),label->width(),label->height()));
            animation1->setEasingCurve(QEasingCurve::InOutQuad);

            int range = vecPerform[i].getAniRange();
            animation1->setEndValue(QRect(label->x(),label->y()+range,label->width(),label->height()));
            animation1->start(QAbstractAnimation::DeleteWhenStopped);
        });
        return;
    }





}


void PerformPlayer::clearPerform()
{
    for(int i = 0;i<vecMainLabel.size();i++)
    {
        vecMainLabel[i]->clear();
    }
    for(int i = 0;i<vecStatusLabel.size();i++)
    {
        vecStatusLabel[i]->clear();
    }
    //emit deleteBegin();
}

//void PerformPlayer::deleteLaterAndLater(QWidget* w)
//{
//    w->deleteLater();
//    //delete会出问题：perform效果还在等待执行，却已经被delete掉。。。。
//    //若使用计时器延后delete，快速点击会导致QTimer大量累计，
//        //报错内容：QEventDispatcherWin32::registerTimer: Failed to create a timer
                    //(当前程序已使用了 Window 管理器对象的系统允许的所有句柄。)
//让他们挂在树上自动delete吧，，，，，，，，，，，，，，，
//更待研究，，，，，，，，，，，，，，，，，，
//}







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
