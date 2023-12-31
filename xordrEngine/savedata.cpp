#include "savedata.h"


SingleData::SingleData(int c, int s, int p, int n, QString time,QObject *parent,QString text,QPixmap* pix) : QObject(parent)
{
    currentChapter = c;
    currentSection  = s;
    previousChapter = p;
    nextChapter = n;
    dateTime = time;
    currentText = text;
    currentPix = pix;
}



SaveData::SaveData(QObject *parent) : QObject(parent)
{
    load();
}

void SaveData::save(const char *newParameter)
{
    QString currentPath = QCoreApplication::applicationDirPath();
    QString filePathC = QString("%1/res/savedata.txt").arg(currentPath);
    QFile fileSavedata(filePathC);
    fileSavedata.open(QIODevice::WriteOnly);

    QByteArray arr;
    QString aSavedata = "q:"
            + QString::number(this->qSaveData->currentChapter)+newParameter
            + QString::number(this->qSaveData->currentSection)+newParameter
            + QString::number(this->qSaveData->previousChapter)+newParameter
            + QString::number(this->qSaveData->nextChapter)+newParameter
            + this->qSaveData->dateTime
            + ";\n";
    arr+=aSavedata;



//    SaveThread* thread1 = new SaveThread;
//    thread1->inputData(saveData);
//    thread1->start();
    //进行普通存档的储存
//    connect(thread1,&SaveThread::isover,this,[&](){
//        qDebug()<<"!!!!";
//        arr+=thread1->getArr();
//        fileSavedata.write(arr);
//        thread1->exit();
//    });
    for(int i = 0;i<10;i++)
    {
        for(int j = 0;j<10;j++)
        {
            QString aNormalSaveData = "n:"
                    + QString::number(this->saveData[i][j]->currentChapter)+newParameter
                    + QString::number(this->saveData[i][j]->currentSection)+newParameter
                    + QString::number(this->saveData[i][j]->previousChapter)+newParameter
                    + QString::number(this->saveData[i][j]->nextChapter)+newParameter
                    + this->saveData[i][j]->dateTime+newParameter
                    + this->saveData[i][j]->currentText
                    + ";\n";
            arr+=aNormalSaveData;
            QString filename = QString("%1/res/savedata/%2%3.png").arg(currentPath).arg(i).arg(j);
            if(!this->saveData[i][j]->currentPix->isNull())
            {
                this->saveData[i][j]->currentPix->save(filename);
            }
        }
    }
    fileSavedata.write(arr);
    fileSavedata.close();

}

void SaveData::load()
{
    QString currentPath = QCoreApplication::applicationDirPath();
    QString filePathC = QString("%1/res/savedata.txt").arg(currentPath);
    QFile file(filePathC);
    file.open(QIODevice::ReadOnly);


    QString str=file.readLine();
    int p1 = str.indexOf(":");
    int p2 = str.indexOf(":",p1+1);
    int cC = str.mid(p1+1,p2-p1-1).toInt();

    int p3 = str.indexOf(":",p2+1);
    int cS = str.mid(p2+1,p3-p2-1).toInt();

    int p4 = str.indexOf(":",p3+1);
    int pC = str.mid(p3+1,p4-p3-1).toInt();

    int p5 = str.indexOf(":",p4+1);
    int nC = str.mid(p4+1,p5-p4-1).toInt();

    int pend = str.indexOf(";");
    QString time = str.mid(p5+1,pend-p5-1);

    qSaveData = new SingleData(cC,cS,pC,nC,time,this);


    for(int i = 0;i<10;i++)
    {
        for(int j = 0;j<10;j++)
        {
            str = file.readLine();
            int p1 = str.indexOf(":");
            int p2 = str.indexOf(":",p1+1);
            int cCn = str.mid(p1+1,p2-p1-1).toInt();

            int p3 = str.indexOf(":",p2+1);
            int cSn = str.mid(p2+1,p3-p2-1).toInt();

            int p4 = str.indexOf(":",p3+1);
            int pCn = str.mid(p3+1,p4-p3-1).toInt();

            int p5 = str.indexOf(":",p4+1);
            int nCn = str.mid(p4+1,p5-p4-1).toInt();

            int p6 = str.lastIndexOf(":");
            QString timen = str.mid(p5+1,p6-p5-1);

            int p7 = str.indexOf(";");
            QString text = str.mid(p6+1,p7-p6-1);

            QString filePath = QString("%1/res/savedata/%2%3.png").arg(currentPath).arg(i).arg(j);
            QPixmap* pix = new QPixmap(filePath);

            SingleData* aNormalData = new SingleData(cCn,cSn,pCn,nCn,timen,this,text,pix);
            saveData[i][j]=aNormalData;
        }
    }
    file.close();


    filePathC = QString("%1/res/haveread.txt").arg(currentPath);
    file.setFileName(filePathC);
    file.open(QIODevice::ReadOnly);

    str=file.readLine();
    int first = str.indexOf(":");
    int end = str.indexOf(";");
    QString str2 = str.mid(first+1,end-first-1);
    int pos1 = str2.indexOf("(");
    int pos2 = str2.indexOf(")");
    while(pos1!=-1)
    {
        QString strin = str2.mid(pos1+1,pos2-pos1-1);
        int p1 = strin.indexOf(":");
        int chapter = strin.mid(0,p1).toInt();
        int section = strin.mid(p1+1).toInt();
        haveRead.insert(chapter,section);
        pos1 = str2.indexOf("(",pos2+1);
        pos2 = str2.indexOf(")",pos2+1);
    }

    str=file.readLine();
    first = str.indexOf(":");
    end = str.indexOf(";");
    mainPicName=str.mid(first+1,end-first-1);
    QString mainpicPath = currentPath;
    mainpicPath+=QString("/res/resource/config/");
    mainpicPath+=mainPicName;
    this->mainPic = new QImage(mainpicPath);

    str=file.readLine();
    first = str.indexOf(":");
    end = str.indexOf(";");
    if(str.mid(first+1,end-first-1).toInt())
    {
        galleryIsOpen = true;
    }
    else
    {
        galleryIsOpen = false;
    }

//    qDebug()<<haveRead[1]<<haveRead[2]<<haveRead[3]<<haveRead[4];
//    qDebug()<<mainPic->size();
//    qDebug()<<galleryIsOpen;
    file.close();
}

void SaveData::saveHaveRead()
{
    QString currentPath = QCoreApplication::applicationDirPath();
    QString filePathC = QString("%1/res/haveread.txt").arg(currentPath);
    QFile file(filePathC);
    file.open(QIODevice::WriteOnly);

    QByteArray arr = "";
    QString havereadstr = QString("haveread:");
    for(QMap<int,int>::iterator it = haveRead.begin();it!=haveRead.end();it++)
    {
        havereadstr = havereadstr+ "(" + QString::number(it.key()) + ":" + QString::number(it.value()) + ")";
    }
    havereadstr+=";\n";
    arr+=havereadstr;

    QString mainpicstr = "mainpic:" + mainPicName + ";\n";
    arr+=mainpicstr;

    int isO = 0;
    if(galleryIsOpen)
    {
        isO = 1;
    }
    QString gallerystr = "gallery:" + QString::number(isO) + ";\n";
    arr+=gallerystr;


    file.write(arr);
    file.close();
}

