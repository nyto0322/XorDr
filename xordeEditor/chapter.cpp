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





Special::Special(QString m, int time,QPoint p)
{
    m_special = m;
    m_start = time;
    m_point = p;
}



QString Special::getSpecial() const
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





Chapter::Chapter(QString path,int i,QObject *parent) : QObject(parent)
{
    currentChapter = i;
    loadChapter(path);
}

void Chapter::loadChapter(QString filePath)
{
    QString currentPath = filePath;
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

        QString filePath=str.mid(first+1,end-first-1);

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
        filePath = str.mid(first+1,end-first-1);
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


            QPoint pos = QPoint(xStr.toInt(),yStr.toInt());

            Figure figure(mainfigStr,statusStr,pos,sizeStr.toDouble(),startStr.toDouble()
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


        QString fileName=str.mid(first+1,end-first-1);
        cg.insert(index,fileName);
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

        background.insert(index,str.mid(first+1,end-first-1));
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

            QString soundPath = strin.mid(0,p1);                      //具体路径！！！！


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

            QString movie=strin.mid(0,p1);                      //具体路径！！！！


            int x = strin.mid(p1+1,p2-p1-1).toInt();
            int y = strin.mid(p2+1,p3-p2-1).toInt();
            int start = strin.mid(p3+1).toInt();


            Special special(movie,start,QPoint(x,y));
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





                ChoicePushButton* c = new ChoicePushButton(nName,mName,pName,sName,QPoint(bX,bY),QSize(bW,bH)
                            ,text,next,QPoint(tX,tY),QSize(tW,tH),fD,showAfterChapter);

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

QMap<int, QString> Chapter::getBackground()
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



void Chapter::setDialog(int s, Dialog *d)
{
    dialog.insert(s,d);
}

void Chapter::setVocal(int s, QString v)
{
    vocal.insert(s,v);
    if(v=="")
    {
        vocal.remove(s);
    }
}

void Chapter::setBgm(int s, QString b)
{
    bgm.insert(s,b);
    if(b=="")
    {
        bgm.remove(s);
    }
}

void Chapter::setPerform(int p, QVector<Figure> f)
{
    perform.insert(p,f);
}

void Chapter::setCg(int s, QString c)
{
    cg.insert(s,c);
    if(c=="")
    {
        cg.remove(s);
    }
}

void Chapter::setBackground(int s, QString b)
{
    background.insert(s,b);
    if(b=="")
    {
        background.remove(s);
    }
}

void Chapter::setSpecial(int i, QVector<Special> s)
{
    special.insert(i,s);
}

void Chapter::setSound(int i, QVector<Sound>s)
{
    sound.insert(i,s);
}

void Chapter::setChoice(int i, QVector<ChoicePushButton *> c)
{
    choice.insert(i,c);
}

void Chapter::setNextChapter(int n)
{
    nextChapter = n;
}

void Chapter::setCurrentChapter(int c)
{
    currentChapter = c;
}





void Chapter::remove(int currentSection)
{
    removeM(vocal,currentSection);
    removeM(bgm,currentSection);
    removeM(cg,currentSection);
    removeM(background,currentSection);
    removeM(perform,currentSection);
    removeM(sound,currentSection);
    removeM(special,currentSection);
    removeM(choice,currentSection);
    removeM(dialog,currentSection);//模板函数查找vit时基于dialog.size判断是否结束循环，dialog于最后更改
}

void Chapter::insert(int currentSection)
{
    if(currentSection==dialog.size()+1)//标记 延后一节结束，仅dialog
    {
        dialog.insert(dialog.size()+1,new Dialog("","",0));
    }
    else
    {
        int m_net = currentSection;
        QMap<int,Dialog*>::const_iterator vit1 = dialog.constFind(currentSection);
        QMap<int,Dialog*>::const_iterator vit2;
        while(1)
        {
            if(!dialog.contains(m_net))
            {
                m_net++;
                if(m_net>dialog.size())
                {
                    break;
                }
            }
            else
            {
                if(currentSection==m_net)
                {
                    vit2=dialog.constFind(m_net)+1;
                }
                else
                {
                    vit2=dialog.constFind(m_net);
                }

                break;
            }
        }

        QMap<int,Dialog*> temp_m;
        bool t = false;
        for(QMap<int,Dialog*>::const_iterator it = dialog.constBegin();it!=dialog.constEnd();it++)
        {
            if(vit1!=dialog.constEnd())//vit1存在
            {
                if(it==vit1)
                {
                    temp_m.insert(it.key(),new Dialog("","",0));
                    t=true;//下一轮开始更改key
                }
            }
            else//vit1不存在
            {
                if(it==vit2)
                {
                    t=true;
                }
            }


            if(!t)
            {
                temp_m.insert(it.key(),it.value());
            }
            else
            {
                temp_m.insert(it.key()+1,it.value());
            }
        }
        dialog.clear();
        dialog=temp_m;
    }

    insertM(vocal,currentSection);
    insertM(bgm,currentSection);
    insertM(cg,currentSection);
    insertM(background,currentSection);
    insertM(perform,currentSection);
    insertM(special,currentSection);
    insertM(sound,currentSection);
    insertM(choice,currentSection);
}





void Chapter::save(QString path)
{
    emit chapterSaveBegin();
    QFile dialogFile(path+(QString("/res/command/dialog/%1.txt").arg(QString::number(currentChapter))));
    dialogFile.open(QIODevice::WriteOnly);
    QByteArray diaArr;
    for(QMap<int,Dialog*>::const_iterator it = dialog.constBegin();it!=dialog.constEnd();it++)
    {
        diaArr+=(QString::number(it.key())+':'+it.value()->getName()+':'+it.value()->getText()
                 +':'+QString::number(it.value()->getFontDelta())+";\n");
    }
    dialogFile.write(diaArr);
    dialogFile.close();

    QFile vocalFile(path+(QString("/res/command/vocal/%1.txt").arg(QString::number(currentChapter))));
    vocalFile.open(QIODevice::WriteOnly);
    QByteArray vocalArr;
    for(QMap<int,QString>::const_iterator it = vocal.constBegin();it!=vocal.constEnd();it++)
    {
        vocalArr+=(QString::number(it.key())+':'+it.value()+";\n");
    }
    vocalFile.write(vocalArr);
    vocalFile.close();

    QFile bgmFile(path+(QString("/res/command/bgm/%1.txt").arg(QString::number(currentChapter))));
    bgmFile.open(QIODevice::WriteOnly);
    QByteArray bgmArr;
    for(QMap<int,QString>::const_iterator it = bgm.constBegin();it!=bgm.constEnd();it++)
    {
        bgmArr+=(QString::number(it.key())+':'+it.value()+";\n");
    }
    bgmFile.write(bgmArr);
    bgmFile.close();



    QFile cgFile(path+(QString("/res/command/cg/%1.txt").arg(QString::number(currentChapter))));
    cgFile.open(QIODevice::WriteOnly);
    QByteArray cgArr;
    for(QMap<int,QString>::const_iterator it = cg.constBegin();it!=cg.constEnd();it++)
    {
        cgArr+=(QString::number(it.key())+':'+it.value()+";\n");
    }
    cgFile.write(cgArr);
    cgFile.close();


    QFile backFile(path+(QString("/res/command/background/%1.txt").arg(QString::number(currentChapter))));
    backFile.open(QIODevice::WriteOnly);
    QByteArray backArr;
    for(QMap<int,QString>::const_iterator it = background.constBegin();it!=background.constEnd();it++)
    {
        backArr+=(QString::number(it.key())+':'+it.value()+";\n");
    }
    backFile.write(backArr);
    backFile.close();





    QFile performFile(path+(QString("/res/command/perform/%1.txt").arg(QString::number(currentChapter))));
    performFile.open(QIODevice::WriteOnly);
    QByteArray performArr;
    for(QMap<int,QVector<Figure>>::const_iterator it = perform.constBegin();it!=perform.constEnd();it++)
    {
        QString line;
        for(QVector<Figure>::const_iterator vit = it.value().constBegin();vit!=it.value().constEnd();vit++)
        {
            line+=("("+QString(vit->getMainfig()
                               +':'+vit->getStatus()
                               +':'+QString::number(vit->m_pos.x())
                               +':'+QString::number(vit->m_pos.y())
                               +':'+QString::number(vit->m_size)
                               +':'+QString::number(vit->getStart())
                               +':'+QString::number(vit->getDuration())
                               +':'+QString::number(vit->m_jrSize)
                               +':'+vit->m_animation
                               +':'+QString::number(vit->m_ani_start)
                               +':'+QString::number(vit->m_ani_duration)
                               +':'+QString::number(vit->m_ani_range)
                               )+")");
        }
        performArr+=(QString::number(it.key())+':'+line+";\n");
    }
    performFile.write(performArr);
    performFile.close();



    QFile specialFile(path+(QString("/res/command/special/%1.txt").arg(QString::number(currentChapter))));
    specialFile.open(QIODevice::WriteOnly);
    QByteArray specialArr;
    for(QMap<int,QVector<Special>>::const_iterator it = special.constBegin();it!=special.constEnd();it++)
    {
        QString line;
        for(QVector<Special>::const_iterator vit = it.value().constBegin();vit!=it.value().constEnd();vit++)
        {
            line+=("("+QString(vit->getSpecial()
                               +':'+QString::number(vit->m_point.x())
                               +':'+QString::number(vit->m_point.y())
                               +':'+QString::number(vit->m_start)
                               )+")");
        }
        specialArr+=(QString::number(it.key())+':'+line+";\n");
    }
    specialFile.write(specialArr);
    specialFile.close();



    QFile soundFile(path+(QString("/res/command/sound/%1.txt").arg(QString::number(currentChapter))));
    soundFile.open(QIODevice::WriteOnly);
    QByteArray soundArr;
    for(QMap<int,QVector<Sound>>::const_iterator it = sound.constBegin();it!=sound.constEnd();it++)
    {
        QString line;
        for(QVector<Sound>::const_iterator vit = it.value().constBegin();vit!=it.value().constEnd();vit++)
        {
            line+=("("+QString(vit->m_soundPath
                               +':'+QString::number(vit->m_start)
                               )+")");
        }
        soundArr+=(QString::number(it.key())+':'+line+";\n");
    }
    soundFile.write(soundArr);
    soundFile.close();


    if(nextChapter!=-1)
    {
        QFile choiceFile_next(path+(QString("/res/command/choice/%1.txt").arg(QString::number(currentChapter))));
        choiceFile_next.open(QIODevice::WriteOnly);
        QString line = "0:"+QString::number(nextChapter)+";";
        QByteArray choiceArr ;
        choiceArr += line;
        choiceFile_next.write(choiceArr);
        choiceFile_next.close();
    }
    else
    {
        QFile choiceFile(path+(QString("/res/command/choice/%1.txt").arg(QString::number(currentChapter))));
        choiceFile.open(QIODevice::WriteOnly);
        QByteArray choiceArr;
        for(QMap<int,QVector<ChoicePushButton*>>::const_iterator it = choice.constBegin();it!=choice.constEnd();it++)
        {
            QString line;
            for(QVector<ChoicePushButton*>::const_iterator vit = it.value().constBegin();vit!=it.value().constEnd();vit++)
            {
                line+=("("+QString((*vit)->getText()
                                   +':'+QString::number((*vit)->getNext())

                                   +":"+(*vit)->normalImgPath
                                   +":"+(*vit)->enterImgPath
                                   +":"+(*vit)->pressImgPath
                                   +":"+(*vit)->clickSoundPath
                                   +":"+QString::number((*vit)->pos.x())
                                   +":"+QString::number((*vit)->pos.y())
                                   +":"+QString::number((*vit)->size.width())
                                   +":"+QString::number((*vit)->size.height())

                                   +":"+QString::number((*vit)->getTextPos().x())
                                   +":"+QString::number((*vit)->getTextPos().y())
                                   +":"+QString::number((*vit)->getTextSize().width())
                                   +":"+QString::number((*vit)->getTextSize().height())
                                   +":"+QString::number((*vit)->getfontDelta())
                                   +":"+(*vit)->getShowAfterChapter()
                                   )+")");
            }
            choiceArr+=(QString::number(it.key())+':'+line+";\n");
        }
        choiceFile.write(choiceArr);
        choiceFile.close();
    }

}
