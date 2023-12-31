#include "data.h"



QString Data::ssl(QString s)
{
    return ":"+s+";\n";
}

QString Data::ssl(NewPushButton *b)
{
    return ":"+b->normalImgPath
            +":"+b->enterImgPath
            +":"+b->pressImgPath
            +":"+b->clickSoundPath
            +":"+QString::number(b->pos.x())
            +":"+QString::number(b->pos.y())
            +":"+QString::number(b->size.width())
            +":"+QString::number(b->size.height())+";\n";
}

QString Data::ssl(SwitchButton *b)
{
    return ":"+b->normalImgPath
            +":"+b->enterImgPath
            +":"+b->pressImgPath
            +":"+b->clickSoundPath
            +":"+QString::number(b->pos.x())
            +":"+QString::number(b->pos.y())
            +":"+QString::number(b->size.width())
            +":"+QString::number(b->size.height())+";\n";
}

QString Data::ssl(QMap<int, QString> m)
{
    QString s = ":";
    for(QMap<int,QString>::const_iterator it = m.constBegin();it!=m.constEnd();it++)
    {
        s+=("("+it.value()+":"+QString::number(it.key())+")");
    }
    return s+";\n";
}

QString Data::ssl(FrameInfo f)
{
    QString s;
    s+=(":"+f.getPix()
        +":"+QString::number(f.getBackPoint().x())+":"+QString::number(f.getBackPoint().y())
        +":"+QString::number(f.getBackSize().width())+":"+QString::number(f.getBackSize().height())
        +":"+QString::number(f.getTextPoint().x()) +":"+QString::number(f.getTextPoint().y())
        +":"+QString::number(f.getTextSize().width())+":"+QString::number(f.getTextSize().height())
        +":"+f.getFont().family()
        +":"+QString::number(f.getFont().pointSize())
        +";\n"
        );
    return s;
}

QString Data::ssl(ConfigSlider* f)
{
    QString s;
    s+=(":"+QString::number(f->posL.x())+":"+QString::number(f->posL.y())
        +":"+QString::number(f->sizeL.width())+":"+QString::number(f->sizeL.height())
        +":"+f->imgL
        +":"+QString::number(f->posS.x()) +":"+QString::number(f->posS.y())
        +":"+QString::number(f->sizeS.width())+":"+QString::number(f->sizeS.height())
        +";\n"
        );
    return s;
}

void Data::removeAllfile(QString path)
{
    QDir dir(path);
    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();
    foreach (QFileInfo file, fileList)
    {
        if (file.isFile())// 文件删除
        {
           file.dir().remove(file.fileName());
        }
        else// 文件夹内递归删除
        {
            removeAllfile(file.absoluteFilePath());
        }
    }
}



Data::Data(QString path, QObject *parent) : QObject(parent)
{
    loadData(path);
}

void Data::loadData(QString filePath)
{
    currentPath = filePath;
    //加载config资源
    QString filePathC = QString("%1/res/config.txt").arg(currentPath);
    QFile fileConfig(filePathC);
    fileConfig.open(QIODevice::ReadOnly);
    if(!fileConfig.isOpen())
    {
        this->loadError = QString("config脚本加载失败")+=filePathC;
    }

    QString str=fileConfig.readLine();
    int first = str.indexOf(":");
    int end = str.indexOf(";");
    this->title = str.mid(first+1,end-first-1);

    str=fileConfig.readLine();
    first = str.indexOf(":");
    end = str.indexOf(";");
    this->icon=str.mid(first+1,end-first-1);


    str=fileConfig.readLine();
    first = str.indexOf(":");
    end = str.indexOf(";");
    this->mouse=str.mid(first+1,end-first-1);

    str=fileConfig.readLine();
    first = str.indexOf(":");
    end = str.indexOf(";");

    QString strVal = str.mid(first+1,end-first-1);
    int pos1 = strVal.indexOf("(");
    int pos2 = strVal.indexOf(")");
    //qDebug()<<strVal;

    while(pos1!=-1)
    {
        QString strin = strVal.mid(pos1+1,pos2-pos1-1);
        int p1 = strin.indexOf(":");

        QString mainpicName = strin.mid(0,p1);
        int afterChapter = strin.mid(p1+1).toInt();
        //qDebug()<<mainpicName;
        //qDebug()<<afterChapter;

//        QString mainpicPath = currentPath;
//        mainpicPath+=QString("/res/resource/config/");
//        mainpicPath+=mainpicName;
//        QImage* img = new QImage(mainpicPath);
//        if(img->isNull())
//        {
//            loadError = QString("config_mainpic资源加载失败")+=mainpicPath;
//        }
        this->mainPic.insert(afterChapter,mainpicName);


        pos1 = strVal.indexOf("(",pos2+1);
        pos2 = strVal.indexOf(")",pos2+1);
    }



    str=fileConfig.readLine();
    first = str.indexOf(":");
    end = str.indexOf(";");
    this->bgmPath=str.mid(first+1,end-first-1);


    str=fileConfig.readLine();
    first = str.indexOf(":");
    end = str.indexOf(";");
    this->chapterNum = str.mid(first+1,end-first-1).toInt();

    QDir dir(QString("%1/res/command/dialog").arg(currentPath));
    QStringList filename ;
    filename << "*.txt";
    QStringList fileList = dir.entryList(filename,QDir::Files | QDir::Readable,QDir::Name);


    for(int i=0;i<fileList.size();i++)
    {
        Chapter* c = new Chapter(filePath,fileList[i].mid(0,fileList[i].indexOf('.')).toInt(),this);
        if(c->loadError != "")
        {
            this->loadError = c->loadError;
        }
        chapterMap.insert(c->getCurrentChapter(),c);
    }



    str=fileConfig.readLine();
    first = str.indexOf(":");
    end = str.indexOf(";");
    this->loadBackground=str.mid(first+1,end-first-1);

    str=fileConfig.readLine();
    first = str.indexOf(":");
    end = str.indexOf(";");
    this->saveBackground=str.mid(first+1,end-first-1);

    str=fileConfig.readLine();
    first = str.indexOf(":");
    end = str.indexOf(";");
    this->galleryBackground=str.mid(first+1,end-first-1);

    str=fileConfig.readLine();
    first = str.indexOf(":");
    end = str.indexOf(";");
    this->configBackground=str.mid(first+1,end-first-1);


    str=fileConfig.readLine();
    first = str.indexOf(":");
    int second = str.indexOf(":",first+1);
    end = str.indexOf(";");
    int x = str.mid(first+1,second-first-1).toInt();
    int y = str.mid(second+1,end-second-1).toInt();
    this->size = QSize(x,y);




    for(int i=0;i<6;i++)
    {
        str=fileConfig.readLine();
        int p1 = str.indexOf(":");
        int p2 = str.indexOf(":",p1+1);
        QString nName = str.mid(p1+1,p2-p1-1);

        int p3 = str.indexOf(":",p2+1);
        QString eName = str.mid(p2+1,p3-p2-1);

        int p4 = str.indexOf(":",p3+1);
        QString pName = str.mid(p3+1,p4-p3-1);

        int p5 = str.indexOf(":",p4+1);
        QString sName = str.mid(p4+1,p5-p4-1);

        int p6 = str.indexOf(":",p5+1);
        int x = str.mid(p5+1,p6-p5-1).toInt();
        int p7 = str.indexOf(":",p6+1);
        int y = str.mid(p6+1,p7-p6-1).toInt();
        int p8 = str.indexOf(":",p7+1);
        int w = str.mid(p7+1,p8-p7-1).toInt();
        int pend = str.indexOf(";");
        int h = str.mid(p8+1,pend-p8-1).toInt();

        NewPushButton* btn = new NewPushButton(nName,eName,pName,sName,QPoint(x,y),QSize(w,h));
        this->beginBtn.insert(i,btn);
        if(btn->loadError!="")
        {
            this->loadError = btn->loadError;
        }
    }


    str=fileConfig.readLine();
    int p1 = str.indexOf(":");
    int p2 = str.indexOf(":",p1+1);
    QString frameName = str.mid(p1+1,p2-p1-1);

    int p3 = str.indexOf(":",p2+1);
    int fbX = str.mid(p2+1,p3-p2-1).toInt();
    int p4 = str.indexOf(":",p3+1);
    int fbY = str.mid(p3+1,p4-p3-1).toInt();
    int p5 = str.indexOf(":",p4+1);
    int fbW = str.mid(p4+1,p5-p4-1).toInt();
    int p6 = str.indexOf(":",p5+1);
    int fbH = str.mid(p5+1,p6-p5-1).toInt();

    int p7 = str.indexOf(":",p6+1);
    int ftX = str.mid(p6+1,p7-p6-1).toInt();
    int p8 = str.indexOf(":",p7+1);
    int ftY = str.mid(p7+1,p8-p7-1).toInt();
    int p9 = str.indexOf(":",p8+1);
    int ftW = str.mid(p8+1,p9-p8-1).toInt();
    int p10 = str.indexOf(":",p9+1);
    int ftH = str.mid(p9+1,p10-p9-1).toInt();

    int p11 = str.indexOf(":",p10+1);
    QString style = str.mid(p10+1,p11-p10-1);
    int pend = str.indexOf(";");
    int size = str.mid(p11+1,pend-p11-1).toInt();

    QFont name_font;
    name_font.setFamily(style);
    name_font.setPointSize(size);
    nameFrame = new FrameInfo(frameName,QPoint(fbX,fbY),QSize(fbW,fbH),QPoint(ftX,ftY),QSize(ftW,ftH),name_font);




    str=fileConfig.readLine();
    p1 = str.indexOf(":");
    p2 = str.indexOf(":",p1+1);
    frameName = str.mid(p1+1,p2-p1-1);

    p3 = str.indexOf(":",p2+1);
    fbX = str.mid(p2+1,p3-p2-1).toInt();
    p4 = str.indexOf(":",p3+1);
    fbY = str.mid(p3+1,p4-p3-1).toInt();
    p5 = str.indexOf(":",p4+1);
    fbW = str.mid(p4+1,p5-p4-1).toInt();
    p6 = str.indexOf(":",p5+1);
    fbH = str.mid(p5+1,p6-p5-1).toInt();

    p7 = str.indexOf(":",p6+1);
    ftX = str.mid(p6+1,p7-p6-1).toInt();
    p8 = str.indexOf(":",p7+1);
    ftY = str.mid(p7+1,p8-p7-1).toInt();
    p9 = str.indexOf(":",p8+1);
    ftW = str.mid(p8+1,p9-p8-1).toInt();
    p10 = str.indexOf(":",p9+1);
    ftH = str.mid(p9+1,p10-p9-1).toInt();


    p11 = str.indexOf(":",p10+1);
    style = str.mid(p10+1,p11-p10-1);
    pend = str.indexOf(";");
    size = str.mid(p11+1,pend-p11-1).toInt();

    QFont text_font;
    text_font.setFamily(style);
    text_font.setPointSize(size);
    textFrame = new FrameInfo(frameName,QPoint(fbX,fbY),QSize(fbW,fbH),QPoint(ftX,ftY),QSize(ftW,ftH),text_font);


    for(int i = 0;i<3;i++)
    {
        str=fileConfig.readLine();
        int p1 = str.indexOf(":");
        int p2 = str.indexOf(":",p1+1);
        QString nName = str.mid(p1+1,p2-p1-1);

        int p3 = str.indexOf(":",p2+1);
        QString eName = str.mid(p2+1,p3-p2-1);

        int p4 = str.indexOf(":",p3+1);
        QString pName = str.mid(p3+1,p4-p3-1);

        int p5 = str.indexOf(":",p4+1);
        QString sName = str.mid(p4+1,p5-p4-1);

        int p6 = str.indexOf(":",p5+1);
        int x = str.mid(p5+1,p6-p5-1).toInt();
        int p7 = str.indexOf(":",p6+1);
        int y = str.mid(p6+1,p7-p6-1).toInt();
        int p8 = str.indexOf(":",p7+1);
        int w = str.mid(p7+1,p8-p7-1).toInt();
        int pend = str.indexOf(";");
        int h = str.mid(p8+1,pend-p8-1).toInt();

        SwitchButton* btn = new SwitchButton(nName,eName,pName,sName,QPoint(x,y),QSize(w,h));
        this->sceneSwitch.push_back(btn);
        if(btn->loadError!="")
        {
            this->loadError = btn->loadError;
        }

    }
    for(int i = 0;i<10;i++)
    {
        str=fileConfig.readLine();
        int p1 = str.indexOf(":");
        int p2 = str.indexOf(":",p1+1);
        QString nName = str.mid(p1+1,p2-p1-1);

        int p3 = str.indexOf(":",p2+1);
        QString eName = str.mid(p2+1,p3-p2-1);

        int p4 = str.indexOf(":",p3+1);
        QString pName = str.mid(p3+1,p4-p3-1);
        int p5 = str.indexOf(":",p4+1);
        QString sName = str.mid(p4+1,p5-p4-1);

        int p6 = str.indexOf(":",p5+1);
        int x = str.mid(p5+1,p6-p5-1).toInt();
        int p7 = str.indexOf(":",p6+1);
        int y = str.mid(p6+1,p7-p6-1).toInt();
        int p8 = str.indexOf(":",p7+1);
        int w = str.mid(p7+1,p8-p7-1).toInt();
        int pend = str.indexOf(";");
        int h = str.mid(p8+1,pend-p8-1).toInt();

        NewPushButton* btn = new NewPushButton(nName,eName,pName,sName,QPoint(x,y),QSize(w,h));
        this->sceneBtn.push_back(btn);
        if(btn->loadError!="")
        {
            this->loadError = btn->loadError;
        }
    }

    for(int i = 0;i<4;i++)
    {
        str=fileConfig.readLine();
        int p1 = str.indexOf(":");
        int p2 = str.indexOf(":",p1+1);
        QString nName = str.mid(p1+1,p2-p1-1);

        int p3 = str.indexOf(":",p2+1);
        QString eName = str.mid(p2+1,p3-p2-1);

        int p4 = str.indexOf(":",p3+1);
        QString pName = str.mid(p3+1,p4-p3-1);

        int p5 = str.indexOf(":",p4+1);
        QString sName = str.mid(p4+1,p5-p4-1);

        int p6 = str.indexOf(":",p5+1);
        int x = str.mid(p5+1,p6-p5-1).toInt();
        int p7 = str.indexOf(":",p6+1);
        int y = str.mid(p6+1,p7-p6-1).toInt();
        int p8 = str.indexOf(":",p7+1);
        int w = str.mid(p7+1,p8-p7-1).toInt();
        int pend = str.indexOf(";");
        int h = str.mid(p8+1,pend-p8-1).toInt();

        NewPushButton* btn = new NewPushButton(nName,eName,pName,sName,QPoint(x,y),QSize(w,h));
        this->otherPlayerBtn.push_back(btn);
        if(btn->loadError!="")
        {
            this->loadError = btn->loadError;
        }
    }



    //CONFIG界面
    for(int i = 0;i<10;i++)
    {
        str=fileConfig.readLine();
        int p1 = str.indexOf(":");
        int p2 = str.indexOf(":",p1+1);
        int xL = str.mid(p1+1,p2-p1-1).toInt();

        int p3 = str.indexOf(":",p2+1);
        int yL = str.mid(p2+1,p3-p2-1).toInt();

        int p4 = str.indexOf(":",p3+1);
        int wL = str.mid(p3+1,p4-p3-1).toInt();

        int p5 = str.indexOf(":",p4+1);
        int hL = str.mid(p4+1,p5-p4-1).toInt();

        int p6 = str.indexOf(":",p5+1);
        QString img = str.mid(p5+1,p6-p5-1);

        int p7 = str.indexOf(":",p6+1);
        int xS = str.mid(p6+1,p7-p6-1).toInt();
        int p8 = str.indexOf(":",p7+1);
        int yS = str.mid(p7+1,p8-p7-1).toInt();
        int p9 = str.indexOf(":",p8+1);
        int wS = str.mid(p8+1,p9-p8-1).toInt();
        int pend = str.indexOf(";");
        int hS = str.mid(p9+1,pend-p9-1).toInt();

        ConfigSlider* c = new ConfigSlider(QPoint(xL,yL),QSize(wL,hL),img,QPoint(xS,yS),QSize(wS,hS));
        configSlider.push_back(c);
    }

    str=fileConfig.readLine();
    int pbegins = str.indexOf(":");
    int pends = str.indexOf(";");
    QString pixpath = currentPath;
    pixpath+=QString("/res/resource/config/");
    pixpath+=str.mid(pbegins+1,pends-pbegins-1);


    str=fileConfig.readLine();
    pbegins = str.indexOf(":");
    pends = str.lastIndexOf(";");
    sliderStyleSheet = str.mid(pbegins+1,pends-pbegins-1);
    //qDebug()<<sliderStyleSheet;


    //存档读档界面
    for(int i = 0;i<10;i++)
    {
        str=fileConfig.readLine();
        int p1 = str.indexOf(":");
        int p2 = str.indexOf(":",p1+1);
        QString nName = str.mid(p1+1,p2-p1-1);

        int p3 = str.indexOf(":",p2+1);
        QString eName = str.mid(p2+1,p3-p2-1);

        int p4 = str.indexOf(":",p3+1);
        QString pName = str.mid(p3+1,p4-p3-1);

        int p5 = str.indexOf(":",p4+1);
        QString sName = str.mid(p4+1,p5-p4-1);

        int p6 = str.indexOf(":",p5+1);
        int x = str.mid(p5+1,p6-p5-1).toInt();
        int p7 = str.indexOf(":",p6+1);
        int y = str.mid(p6+1,p7-p6-1).toInt();
        int p8 = str.indexOf(":",p7+1);
        int w = str.mid(p7+1,p8-p7-1).toInt();
        int pend = str.indexOf(";");
        int h = str.mid(p8+1,pend-p8-1).toInt();

        SwitchButton* btn = new SwitchButton(nName,eName,pName,sName,QPoint(x,y),QSize(w,h));
        this->dataPlayerIndexBtn.push_back(btn);
        if(btn->loadError!="")
        {
            this->loadError = btn->loadError;
        }
    }


    for(int i = 0;i<10;i++)
    {
        str=fileConfig.readLine();
        int p1 = str.indexOf(":");
        int p2 = str.indexOf(":",p1+1);
        QString nName = str.mid(p1+1,p2-p1-1);

        int p3 = str.indexOf(":",p2+1);
        QString eName = str.mid(p2+1,p3-p2-1);

        int p4 = str.indexOf(":",p3+1);
        QString pName = str.mid(p3+1,p4-p3-1);

        int p5 = str.indexOf(":",p4+1);
        QString sName = str.mid(p4+1,p5-p4-1);

        int p6 = str.indexOf(":",p5+1);
        int x = str.mid(p5+1,p6-p5-1).toInt();
        int p7 = str.indexOf(":",p6+1);
        int y = str.mid(p6+1,p7-p6-1).toInt();
        int p8 = str.indexOf(":",p7+1);
        int w = str.mid(p7+1,p8-p7-1).toInt();
        int pend = str.indexOf(";");
        int h = str.mid(p8+1,pend-p8-1).toInt();

        NewPushButton* btn = new NewPushButton(nName,eName,pName,sName,QPoint(x,y),QSize(w,h));
        this->dataPlayerBtn.push_back(btn);
        if(btn->loadError!="")
        {
            this->loadError = btn->loadError;
        }
    }


    str=fileConfig.readLine();
    pbegins = str.indexOf(":");
    pends = str.lastIndexOf(";");
    historyStyleSheet = str.mid(pbegins+1,pends-pbegins-1);



    //gallery界面
    str=fileConfig.readLine();
    p1 = str.indexOf(":");
    p2 = str.indexOf(":",p1+1);
    int xL = str.mid(p1+1,p2-p1-1).toInt();
    p3 = str.indexOf(":",p2+1);
    int yL = str.mid(p2+1,p3-p2-1).toInt();
    this->gallerycgPos = QPoint(xL,yL);
    p4 = str.indexOf(":",p3+1);
    this->gallerycgWidth = str.mid(p3+1,p4-p3-1).toInt();
    p5 = str.indexOf(":",p4+1);
    this->gallerycgColumn = str.mid(p4+1,p5-p4-1).toInt();
    p6 = str.indexOf(":",p5+1);
    this->gallerycgRow = str.mid(p5+1,p6-p5-1).toInt();
    pend = str.lastIndexOf(";");
    this->gallerycgStyleSheet = str.mid(p6+1,pend-p6-1);



    str=fileConfig.readLine();
    p1 = str.indexOf(":");
    p2 = str.indexOf(":",p1+1);
    x = str.mid(p1+1,p2-p1-1).toInt();
    p3 = str.indexOf(":",p2+1);
    y = str.mid(p2+1,p3-p2-1).toInt();
    p4 = str.indexOf(":",p3+1);
    int w = str.mid(p3+1,p4-p3-1).toInt();
    p5 = str.indexOf(":",p4+1);
    int h = str.mid(p4+1,p5-p4-1).toInt();
    p6 = str.indexOf(":",p5+1);
    int xS = str.mid(p5+1,p6-p5-1).toInt();
    p7 = str.indexOf(":",p6+1);
    int yS = str.mid(p6+1,p7-p6-1).toInt();
    p8 = str.indexOf(":",p7+1);
    int wS = str.mid(p7+1,p8-p7-1).toInt();
    p9 = str.indexOf(":",p8+1);
    int hS = str.mid(p8+1,p9-p8-1).toInt();
    pend = str.lastIndexOf(";");
    gallerymediaStyleSheet = str.mid(p9+1,pend-p9-1);
    gallerymediaRect = QRect(x,y,w,h);
    gallerymediaSliderRect = QRect(xS,yS,wS,hS);


    for(int i = 0;i<2;i++)
    {
        str=fileConfig.readLine();
        int p1 = str.indexOf(":");
        int p2 = str.indexOf(":",p1+1);
        QString nName = str.mid(p1+1,p2-p1-1);

        int p3 = str.indexOf(":",p2+1);
        QString eName = str.mid(p2+1,p3-p2-1);

        int p4 = str.indexOf(":",p3+1);
        QString pName = str.mid(p3+1,p4-p3-1);

        int p5 = str.indexOf(":",p4+1);
        QString sName = str.mid(p4+1,p5-p4-1);

        int p6 = str.indexOf(":",p5+1);
        int x = str.mid(p5+1,p6-p5-1).toInt();
        int p7 = str.indexOf(":",p6+1);
        int y = str.mid(p6+1,p7-p6-1).toInt();
        int p8 = str.indexOf(":",p7+1);
        int w = str.mid(p7+1,p8-p7-1).toInt();
        int pend = str.indexOf(";");
        int h = str.mid(p8+1,pend-p8-1).toInt();

        NewPushButton* btn = new NewPushButton(nName,eName,pName,sName,QPoint(x,y),QSize(w,h));
        this->gallerymediaBtn.push_back(btn);
        if(btn->loadError!="")
        {
            this->loadError = btn->loadError;
        }
    }

    for(int i = 0;i<2;i++)
    {
        str=fileConfig.readLine();
        int p1 = str.indexOf(":");
        int p2 = str.indexOf(":",p1+1);
        QString nName = str.mid(p1+1,p2-p1-1);

        int p3 = str.indexOf(":",p2+1);
        QString eName = str.mid(p2+1,p3-p2-1);

        int p4 = str.indexOf(":",p3+1);
        QString pName = str.mid(p3+1,p4-p3-1);

        int p5 = str.indexOf(":",p4+1);
        QString sName = str.mid(p4+1,p5-p4-1);

        int p6 = str.indexOf(":",p5+1);
        int x = str.mid(p5+1,p6-p5-1).toInt();
        int p7 = str.indexOf(":",p6+1);
        int y = str.mid(p6+1,p7-p6-1).toInt();
        int p8 = str.indexOf(":",p7+1);
        int w = str.mid(p7+1,p8-p7-1).toInt();
        int pend = str.indexOf(";");
        int h = str.mid(p8+1,pend-p8-1).toInt();

        SwitchButton* btn = new SwitchButton(nName,eName,pName,sName,QPoint(x,y),QSize(w,h));
        this->gallerymediaSwitch.push_back(btn);
        if(btn->loadError!="")
        {
            this->loadError = btn->loadError;
        }
    }














    fileConfig.close();
}

QString Data::getMouse()
{
    return mouse;
}

QMap<int,QString> Data::getMainPic()
{
    return mainPic;
}

QString Data::getIcon()
{
    return icon;
}

QString Data::getTitle()
{
    return title;
}

QString Data::getBgmPath()
{
    return bgmPath;
}

QMap<int, NewPushButton *> Data::getBeginBtn()
{
    return beginBtn;
}

QSize Data::getSize()
{
    return size;
}

QMap<int, Chapter *> Data::getChapterMap()
{
    return chapterMap;
}

FrameInfo *Data::getNameFrame()
{
    return nameFrame;
}

FrameInfo *Data::getTextFrame()
{
    return textFrame;
}

QVector<NewPushButton *> Data::getSceneBtn()
{
    return sceneBtn;
}

QVector<SwitchButton *> Data::getSceneSwitch()
{
    return sceneSwitch;
}

QString Data::getLoadBackground()
{
    return loadBackground;
}

QString Data::getSaveBackground()
{
    return saveBackground;
}

QString Data::getGalleryBackground()
{
    return galleryBackground;
}

QString Data::getConfigBackground()
{
    return configBackground;
}

QVector<NewPushButton *> Data::getOtherPlayerBtn()
{
    return otherPlayerBtn;
}

QVector<ConfigSlider *> Data::getConfigSlider()
{
    return configSlider;
}

QString Data::getSliderStyleSheet()
{
    return sliderStyleSheet;
}

QString Data::getHistoryStyleSheet()
{
    return historyStyleSheet;
}

QVector<SwitchButton *> Data::getDataPlayerIndexBtn()
{
    return dataPlayerIndexBtn;
}

QVector<NewPushButton *> Data::getDataPlayerBtn()
{
    return dataPlayerBtn;
}

QPoint Data::getGallerycgPos()
{
    return gallerycgPos;
}

int Data::getGallerycgWidth()
{
    return gallerycgWidth;
}

int Data::getGallerycgColumn()
{
    return gallerycgColumn;
}

int Data::getGallerycgRow()
{
    return gallerycgRow;
}

QString Data::getGallerycgStyleSheet()
{
    return gallerycgStyleSheet;
}

QRect Data::getGallerymediaRect()
{
    return gallerymediaRect;
}

QRect Data::getGallerymediaSliderRect()
{
    return gallerymediaSliderRect;
}

QVector<NewPushButton *> Data::getGallerymediaBtn()
{
    return gallerymediaBtn;
}

QVector<SwitchButton *> Data::getGallerymediaSwitch()
{
    return gallerymediaSwitch;
}

QString Data::getGallerymediaStyleSheet()
{
    return  gallerymediaStyleSheet;
}

QString Data::getCurrentPath()
{
    return currentPath;
}

void Data::insertChapter( Chapter* c)
{
    chapterMap.insert(c->getCurrentChapter(),c);
}





void Data::setTitle(QString t)
{
    title = t;
}

void Data::setSize(QSize s)
{
    size = s;
}

void Data::setIcon(QString i)
{
    icon = i;
}

void Data::setMouse(QString m)
{
    mouse = m;
}

void Data::setBack(QMap<int, QString> m)
{
    mainPic = m;
}

void Data::setIniBack(QString s)
{
    if(s!="")
        mainPic.insert(0,s);
}

void Data::setBgm(QString b)
{
    bgmPath = b;
}

void Data::setLoad(QString l)
{
    loadBackground = l;
}

void Data::setSave(QString s)
{
    saveBackground = s;
}

void Data::setGal(QString g)
{
    galleryBackground = g;
}

void Data::setCon(QString c)
{
    configBackground = c;
}

void Data::setNameFrame(FrameInfo *f)
{
    nameFrame = f;
}

void Data::setTextFrame(FrameInfo *f)
{
    textFrame = f;
}

void Data::setSliderStyleSheet(QString s)
{
    sliderStyleSheet = s;
}

void Data::setHistoryStyleSheet(QString s)
{
    historyStyleSheet = s;
}

void Data::setGallerycgStyleSheet(QString s)
{
    gallerycgStyleSheet = s;
}

void Data::setGallerymediaStyleSheet(QString s)
{
    gallerymediaStyleSheet = s;
}

void Data::removeChapter(int i)
{
    chapterMap.remove(i);
}

void Data::save()
{
    emit dataSaveBegin();
    //chapter保存
    removeAllfile(currentPath+"/res/command");     //删除原有的脚本
    for(QMap<int,Chapter*>::const_iterator it = chapterMap.constBegin();it!=chapterMap.constEnd();it++)
    {
        it.value()->save(currentPath);
    }



    //config写入文件！
    QFile config(currentPath+"/res/config.txt");
    config.open(QIODevice::WriteOnly);



    QByteArray arr;
    QString t = ";\n";
    arr+=ssl(title);
    arr+=ssl(icon);
    arr+=ssl(mouse);
    arr+=ssl(mainPic);
    arr+=ssl(bgmPath);
    arr+=ssl(QString::number(chapterMap.size()));
    arr+=ssl(loadBackground);
    arr+=ssl(saveBackground);
    arr+=ssl(galleryBackground);
    arr+=ssl(configBackground);
    arr+=ssl(QString::number(size.width())+":"+QString::number(size.height()));
    for(QMap<int,NewPushButton*>::const_iterator it = beginBtn.constBegin();it!=beginBtn.constEnd();it++)
    {
        arr+=ssl(it.value());
    }
    arr+=ssl(*nameFrame);
    arr+=ssl(*textFrame);
    for(QVector<SwitchButton*>::const_iterator it = sceneSwitch.constBegin();it!=sceneSwitch.constEnd();it++)
    {
        arr+=ssl(*it);
    }
    for(QVector<NewPushButton*>::const_iterator it = sceneBtn.constBegin();it!=sceneBtn.constEnd();it++)
    {
        arr+=ssl(*it);
    }
    for(QVector<NewPushButton*>::const_iterator it = otherPlayerBtn.constBegin();it!=otherPlayerBtn.constEnd();it++)
    {
        arr+=ssl(*it);
    }
    for(QVector<ConfigSlider*>::const_iterator it = configSlider.constBegin();it!=configSlider.constEnd();it++)
    {
        arr+=ssl(*it);
    }
    arr+="%1:btn.png;\n";      //应该处理掉，，，
    arr+=ssl(sliderStyleSheet);
    for(QVector<SwitchButton*>::const_iterator it = dataPlayerIndexBtn.constBegin();it!=dataPlayerIndexBtn.constEnd();it++)
    {
        arr+=ssl(*it);
    }
    for(QVector<NewPushButton*>::const_iterator it = dataPlayerBtn.constBegin();it!=dataPlayerBtn.constEnd();it++)
    {
        arr+=ssl(*it);
    }
    arr+=ssl(historyStyleSheet);
    arr+=ssl("360:70:580:4:5:"+gallerycgStyleSheet);
    arr+=ssl("30:130:250:380:5:360:245:20:"+gallerymediaStyleSheet);
    for(QVector<NewPushButton*>::const_iterator it = gallerymediaBtn.constBegin();it!=gallerymediaBtn.constEnd();it++)
    {
        arr+=ssl(*it);
    }
    for(QVector<SwitchButton*>::const_iterator it = gallerymediaSwitch.constBegin();it!=gallerymediaSwitch.constEnd();it++)
    {
        arr+=ssl(*it);
    }
    config.write(arr);
    config.close();


    //haveread初始化
    QFile haveread(currentPath+"/res/haveread.txt");
    haveread.open(QIODevice::WriteOnly);
    QByteArray arrH;
    arrH+="haveread:";
    for(QMap<int,Chapter*>::const_iterator it = chapterMap.constBegin();it!=chapterMap.constEnd();it++)
    {
        arrH+='('+QString::number(it.value()->getCurrentChapter())+":0)";
    }
    arrH+=";\n";
    arrH+="mainpic:"+mainPic[0]+";\n";
    arrH+="gallery:0;";
    haveread.write(arrH);
    haveread.close();


}

ConfigSlider::ConfigSlider(QPoint pl, QSize sl, QString i, QPoint ps, QSize ss)
{
    posL = pl;
    sizeL = sl;
    imgL = i;
    posS = ps;
    sizeS = ss;
}
