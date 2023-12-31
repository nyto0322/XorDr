#include "chapter.h"


Dialog::Dialog(QString name,QString text,int size)
{
    m_name = name;
    m_text = text;
    m_size = size;
}

QString Dialog::getName()
{
    return m_name;
}

QString Dialog::getText()
{
    return m_text;
}

int Dialog::getFontDelta()
{
    return m_size;
}







Sound::Sound(QString s,int time)
{
    m_soundPath = s;
    m_start = time;
}

QString Sound::getSoundPath()
{
    return m_soundPath;
}

int Sound::getStart()
{
    return m_start;
}





Special::Special(QMovie* m, int time,QPoint p)
{
    m_special = m;
    m_start = time;
    m_point = p;
}



QMovie *Special::getSpecial() const
{
    return m_special;
}

QPoint Special::getPos()
{
    return m_point;
}

int Special::getStart()
{
    return m_start;
}





Chapter::Chapter(int i,QObject *parent) : QObject(parent)
{
    currentChapter = i;
    loadChapter();
}

void Chapter::loadChapter()
{
    QString currentPath = QCoreApplication::applicationDirPath();
    //加载dialog资源
    QString filePathC = QString("%1/res/command/dialog/%2.txt").arg(currentPath).arg(currentChapter);
    QFile fileDialog(filePathC);
    fileDialog.open(QIODevice::ReadOnly);
    if(!fileDialog.isOpen())
    {
        loadError = QString("dialog脚本加载失败")+=filePathC;
    }
    while(!fileDialog.atEnd())
    {
        QString str=fileDialog.readLine();
        int first = str.indexOf(":");
        int index = str.mid(0,first).toInt();
        int second = str.indexOf(":",first+1);
        QString name = str.mid(first+1,second-first-1);
        int third = str.indexOf(":",second+1);
        QString text = str.mid(second+1,third-second-1);
        int end = str.indexOf(";");
        int size = str.mid(third+1,end-third-1).toInt();
        Dialog* dia = new Dialog(name,text,size);
        dialog.insert(index,dia);
    }

    fileDialog.close();


    //加载vocal资源
    filePathC = QString("%1/res/command/vocal/%2.txt").arg(currentPath).arg(currentChapter);
    QFile fileVocal(filePathC);
    fileVocal.open(QIODevice::ReadOnly);
    if(!fileVocal.isOpen())
    {
        loadError = QString("vocal脚本加载失败")+=filePathC;
    }
    while(!fileVocal.atEnd())
    {
        QString str=fileVocal.readLine();
        int first = str.indexOf(":");
        int index = str.mid(0,first).toInt();
        int end = str.indexOf(";");

        QString filePath = currentPath;
        filePath+=QString("/res/resource/vocal/");
        filePath+=str.mid(first+1,end-first-1);       //具体路径！！！！

        //失败反馈！
        vocal.insert(index,filePath);
    }
    fileVocal.close();


    //加载bgm资源
    filePathC = QString("%1/res/command/bgm/%2.txt").arg(currentPath).arg(currentChapter);
    QFile fileBgm(filePathC);
    fileBgm.open(QIODevice::ReadOnly);
    if(!fileBgm.isOpen())
    {
        loadError = QString("bgm脚本加载失败")+=filePathC;
    }
    while(!fileBgm.atEnd())
    {
        QString str=fileBgm.readLine();
        int first = str.indexOf(":");
        int index = str.mid(0,first).toInt();
        int end = str.indexOf(";");
        QString fileName = str.mid(first+1,end-first-1);
        QString filePath;
        if(fileName == "none")
        {
            filePath="none";
        }
        else
        {
            filePath = currentPath;
            filePath += QString("/res/resource/bgm/");
            filePath += fileName;
        }
        bgm.insert(index,filePath);
    }
    fileBgm.close();



    //加载perform脚本
    filePathC = QString("%1/res/command/perform/%2.txt").arg(currentPath).arg(currentChapter);
    QFile filePerform(filePathC);
    filePerform.open(QIODevice::ReadOnly);
    if(!filePerform.isOpen())
    {
        loadError = QString("perform脚本加载失败")+=filePathC;
    }
    while(!filePerform.atEnd())
    {
        QString str=filePerform.readLine();
        int first = str.indexOf(":");
        int index = str.mid(0,first).toInt();
        int end = str.indexOf(";");
        QString str2 = str.mid(first+1,end-first-1);


        //value值解析
        QVector<Figure> vecFig;
        int pos1 = str2.indexOf("(");
        int pos2 = str2.indexOf(")");

        while(pos1!=-1)
        {
            QString strin = str2.mid(pos1+1,pos2-pos1-1);

            int p1 = strin.indexOf(":");
            int p2 = strin.indexOf(":",p1+1);
            int p3 = strin.indexOf(":",p2+1);
            int p4 = strin.indexOf(":",p3+1);
            int p5 = strin.indexOf(":",p4+1);
            int p6 = strin.indexOf(":",p5+1);
            int p7 = strin.indexOf(":",p6+1);
            int p8 = strin.indexOf(":",p7+1);
            int p9 = strin.indexOf(":",p8+1);
            int p10 = strin.indexOf(":",p9+1);
            int p11 = strin.indexOf(":",p10+1);

            QString mainfigStr = strin.mid(0,p1);
            QString statusStr = strin.mid(p1+1,p2-p1-1);
            QString xStr = strin.mid(p2+1,p3-p2-1);
            QString yStr = strin.mid(p3+1,p4-p3-1);
            QString sizeStr = strin.mid(p4+1,p5-p4-1);
            QString startStr = strin.mid(p5+1,p6-p5-1);
            QString durationStr = strin.mid(p6+1,p7-p6-1);
            QString jrSizeStr = strin.mid(p7+1,p8-p7-1);
            QString animationStr = strin.mid(p8+1,p9-p8-1);
            QString aniStartStr = strin.mid(p9+1,p10-p9-1);
            QString aniDurationStr = strin.mid(p10+1,p11-p10-1);
            QString aniRangeStr = strin.mid(p11+1);
            //qDebug()<<aniRangeStr;


            QString mainfigPath = currentPath;
            mainfigPath+=QString("/res/resource/figure/");
            mainfigPath+=mainfigStr;                           //具体路径！！！！
            QString statusPath = currentPath;
            statusPath+=QString("/res/resource/status/");
            statusPath+=statusStr;                           //具体路径！！！！

            QImage* mainfig = new QImage(mainfigPath);
            if(mainfig->isNull())
            {
                loadError = QString("figure资源加载失败")+=mainfigPath;
            }
            QImage* status = new QImage(statusPath);
            if(status->isNull())
            {
                loadError = QString("status资源加载失败")+=statusPath;
            }
            QPoint pos = QPoint(xStr.toInt(),yStr.toInt());

            Figure figure(mainfig,status,pos,sizeStr.toDouble(),startStr.toDouble()
                          ,durationStr.toDouble(),jrSizeStr.toDouble(),animationStr
                          ,aniStartStr.toDouble(),aniDurationStr.toDouble(),aniRangeStr.toInt());

            vecFig.push_back(figure);

            pos1 = str2.indexOf("(",pos2+1);
            pos2 = str2.indexOf(")",pos2+1);
        }

        perform.insert(index,vecFig);

    }
    filePerform.close();


    //加载cg资源
    filePathC = QString("%1/res/command/cg/%2.txt").arg(currentPath).arg(currentChapter);
    QFile fileCg(filePathC);
    fileCg.open(QIODevice::ReadOnly);
    if(!fileCg.isOpen())
    {
        loadError = QString("cg脚本加载失败")+=filePathC;
    }
    while(!fileCg.atEnd())
    {
        QString str=fileCg.readLine();
        int first = str.indexOf(":");
        int index = str.mid(0,first).toInt();
        int end = str.indexOf(";");


        QString fileName=str.mid(first+1,end-first-1);                           //具体路径！！！！
        QString filePath;
        if(fileName=="none")
        {
            filePath = "none";
        }
        else
        {
            filePath = currentPath;
            filePath+=QString("/res/resource/cg/");
            filePath+=fileName;
        }

        cg.insert(index,filePath);
    }
    fileCg.close();





    //加载background资源
    filePathC = QString("%1/res/command/background/%2.txt").arg(currentPath).arg(currentChapter);
    QFile fileBackground(filePathC);
    fileBackground.open(QIODevice::ReadOnly);
    if(!fileBackground.isOpen())
    {
       loadError = QString("background脚本加载失败")+=filePathC;
    }
    while(!fileBackground.atEnd())
    {
        QString str=fileBackground.readLine();
        int first = str.indexOf(":");
        int index = str.mid(0,first).toInt();
        int end = str.indexOf(";");

        QString filePath = currentPath;
        filePath+=QString("/res/resource/background/");
        filePath+=str.mid(first+1,end-first-1);                           //具体路径！！！！

        if(str.mid(first+1,end-first-1)!="")
        {
            QImage* image = new QImage(filePath);
            if(image->isNull())
            {
                loadError = QString("background资源加载失败")+=filePath;
            }
            background.insert(index,image);
        }
    }
    fileBackground.close();


    //加载音效
    filePathC = QString("%1/res/command/sound/%2.txt").arg(currentPath).arg(currentChapter);
    QFile fileSound(filePathC);
    fileSound.open(QIODevice::ReadOnly);
    if(!fileSound.isOpen())
    {
        loadError = QString("sound脚本加载失败")+=filePathC;
    }
    while(!fileSound.atEnd())
    {
        QString str=fileSound.readLine();
        int first = str.indexOf(":");
        int index = str.mid(0,first).toInt();
        int end = str.indexOf(";");
        QString str2 = str.mid(first+1,end-first-1);


        //value值解析
        QVector<Sound> vecSound;
        int pos1 = str2.indexOf("(");
        int pos2 = str2.indexOf(")");

        while(pos1!=-1)
        {
            QString strin = str2.mid(pos1+1,pos2-pos1-1);

            int p1 = strin.indexOf(":");

            QString soundPath = currentPath;
            soundPath+=QString("/res/resource/sound/");
            soundPath+=strin.mid(0,p1);                      //具体路径！！！！


            int start = strin.mid(p1+1).toInt();

            Sound sound(soundPath,start);
            vecSound.push_back(sound);
            pos1 = str2.indexOf("(",pos2+1);
            pos2 = str2.indexOf(")",pos2+1);
        }



        this->sound.insert(index,vecSound);
    }
    fileSound.close();



    //加载特效
    filePathC = QString("%1/res/command/special/%2.txt").arg(currentPath).arg(currentChapter);
    QFile fileSpecial(filePathC);
    fileSpecial.open(QIODevice::ReadOnly);
    if(!fileSpecial.isOpen())
    {
        loadError = QString("special脚本加载失败")+=filePathC;
    }
    while(!fileSpecial.atEnd())
    {
        QString str=fileSpecial.readLine();
        int first = str.indexOf(":");
        int index = str.mid(0,first).toInt();
        int end = str.indexOf(";");
        QString str2 = str.mid(first+1,end-first-1);


        //value值解析
        QVector<Special> vecSpecial;
        int pos1 = str2.indexOf("(");
        int pos2 = str2.indexOf(")");

        while(pos1!=-1)
        {
            QString strin = str2.mid(pos1+1,pos2-pos1-1);

            int p1 = strin.indexOf(":");
            int p2 = strin.indexOf(":",p1+1);
            int p3 = strin.indexOf(":",p2+1);

            QString moviePath = currentPath;
            moviePath+=QString("/res/resource/special/");
            moviePath+=strin.mid(0,p1);                      //具体路径！！！！

            QMovie* moviefile = new QMovie(moviePath);
            if(!moviefile->isValid())
            {
                loadError = QString("special资源加载失败")+=moviePath;
            }

            int x = strin.mid(p1+1,p2-p1-1).toInt();
            int y = strin.mid(p2+1,p3-p2-1).toInt();
            int start = strin.mid(p3+1).toInt();


            Special special(moviefile,start,QPoint(x,y));
            vecSpecial.push_back(special);


            pos1 = str2.indexOf("(",pos2+1);
            pos2 = str2.indexOf(")",pos2+1);
        }

        this->special.insert(index,vecSpecial);

    }
    //qDebug()<<special[3][0].m_point;
    fileSpecial.close();




    //加载选择支
    filePathC = QString("%1/res/command/choice/%2.txt").arg(currentPath).arg(currentChapter);
    QFile fileChoice(filePathC);
    fileChoice.open(QIODevice::ReadOnly);
    if(!fileChoice.isOpen())
    {
        loadError = QString("choice脚本加载失败")+=filePathC;
    }
    while(!fileChoice.atEnd())
    {
        QString str=fileChoice.readLine();
        int first = str.indexOf(":");
        int index = str.mid(0,first).toInt();
        int end = str.indexOf(";");
        if(index==0)
        {
            int next = str.mid(first+1,end-first-1).toInt();
            nextChapter = next;
        }
        else
        {
            nextChapter = -1;
            QString str2 = str.mid(first+1,end-first-1);
           //value值解析
            QVector<ChoicePushButton*> vecChoice;
            int pos1 = str2.indexOf("(");
            int pos2 = str2.indexOf(")");

            while(pos1!=-1)
            {
                QString strin = str2.mid(pos1+1,pos2-pos1-1);


                int p1 = strin.indexOf(":");
                int p2 = strin.indexOf(":",p1+1);
                int p3 = strin.indexOf(":",p2+1);
                int p4 = strin.indexOf(":",p3+1);
                int p5 = strin.indexOf(":",p4+1);
                int p6 = strin.indexOf(":",p5+1);
                int p7 = strin.indexOf(":",p6+1);
                int p8 = strin.indexOf(":",p7+1);
                int p9 = strin.indexOf(":",p8+1);
                int p10 = strin.indexOf(":",p9+1);
                int p11 = strin.indexOf(":",p10+1);
                int p12 = strin.indexOf(":",p11+1);
                int p13 = strin.indexOf(":",p12+1);
                int p14 = strin.indexOf(":",p13+1);
                int p15 = strin.indexOf(":",p14+1);

                QString text = strin.mid(0,p1);
                int next = strin.mid(p1+1,p2-p1-1).toInt();
                QString nName = strin.mid(p2+1,p3-p2-1);
                QString mName = strin.mid(p3+1,p4-p3-1);
                QString pName = strin.mid(p4+1,p5-p4-1);
                QString sName = strin.mid(p5+1,p6-p5-1);
                int bX = strin.mid(p6+1,p7-p6-1).toInt();
                int bY = strin.mid(p7+1,p8-p7-1).toInt();
                int bW = strin.mid(p8+1,p9-p8-1).toInt();
                int bH = strin.mid(p9+1,p10-p9-1).toInt();
                int tX = strin.mid(p10+1,p11-p10-1).toInt();
                int tY = strin.mid(p11+1,p12-p11-1).toInt();
                int tW = strin.mid(p12+1,p13-p12-1).toInt();
                int tH = strin.mid(p13+1,p14-p13-1).toInt();
                int fD = strin.mid(p14+1,p15-p14-1).toInt();
                QString showAfterChapter = strin.mid(p15+1);

                QString nPath = currentPath;
                QString mPath = currentPath;
                QString pPath = currentPath;
                QString sPath = currentPath;
                nPath+=QString("/res/resource/choice/");
                nPath+=nName;
                mPath+=QString("/res/resource/choice/");
                mPath+=mName;
                pPath+=QString("/res/resource/choice/");
                pPath+=pName;
                sPath+=QString("/res/resource/choice/");
                sPath+=sName;

                QVector<int> sac;
                int an = showAfterChapter.indexOf("&");
                int ban = 0;
                while(an!=-1)
                {
                    sac.push_back(showAfterChapter.mid(ban,an-ban).toInt());
                    ban = an + 1;
                    an = showAfterChapter.indexOf("&",ban);
                }

//                for(QVector<int>::iterator it = sac.begin();it!=sac.end();it++)
//                {
//                    qDebug()<<*it;
//                    //qDebug()<<sd->haveRead[*it];
//                }



                ChoicePushButton* c = new ChoicePushButton(nPath,mPath,pPath,sPath,QPoint(bX,bY),QSize(bW,bH)
                            ,text,next,QPoint(tX,tY),QSize(tW,tH),fD,sac);
                if(c->loadError != "")
                {
                    loadError = c->loadError;
                }

                vecChoice.push_back(c);

                pos1 = str2.indexOf("(",pos2+1);
                pos2 = str2.indexOf(")",pos2+1);
            }

            this->choice.insert(index,vecChoice);
        }

    }


    //qDebug()<<choice[5]["选项2"]<<"!!!!!!!";
    fileChoice.close();


//    QMap<int,QVector<Special>>::iterator iter = special.begin();
//    while (iter != special.end())
//    {
//        qDebug() << "Iterator " << iter.key() << ":" ;
//        for(QVector<Special>::iterator it = iter.value().begin();it!=iter.value().end();it++)
//        {
//            qDebug() << it->m_start;
//            qDebug() << it->m_point;
//            qDebug() << it->m_special->fileName();
//        }
//        iter++;

//    }
//    QMap<int,QVector<Sound>>::iterator iter = sound.begin();
//    while (iter != sound.end())
//    {
//        qDebug() << "Iterator " << iter.key() << ":" ;
//        for(QVector<Sound>::iterator it = iter.value().begin();it!=iter.value().end();it++)
//        {
//            qDebug() << it->m_start;
//            it->m_sound->play();
//        }
//        iter++;
//    }
    //qDebug()<<nextChapter;

}

QMap<int, Dialog *> Chapter::getDialog()
{
    return dialog;
}

QMap<int, QString> Chapter::getVocal()
{
    return vocal;
}

QMap<int, QString> Chapter::getBgm()
{
    return bgm;
}

QMap<int, QVector<Figure> > Chapter::getPerform()
{
    return perform;
}

QMap<int, QString> Chapter::getCg()
{
    return cg;
}

QMap<int, QImage *> Chapter::getBackground()
{
    return background;
}

QMap<int, QVector<Special> > Chapter::getSpecial()
{
    return special;
}

QMap<int, QVector<Sound> > Chapter::getSound()
{
    return sound;
}

QMap<int, QVector<ChoicePushButton *> > Chapter::getChoice()
{
    return choice;
}

int Chapter::getNextChapter()
{
    return nextChapter;
}
int Chapter::getCurrentChapter()
{
    return currentChapter;
}


