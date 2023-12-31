#include "data.h"



Data::Data(QObject *parent) : QObject(parent)
{
    loadData();    
}

void Data::loadData()
{
    QString currentPath = QCoreApplication::applicationDirPath();
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
    QString iconName=str.mid(first+1,end-first-1);
    QString iconPath = currentPath;
    iconPath+=QString("/res/resource/config/");
    iconPath+=iconName;
    this->icon = QIcon(iconPath);
    if(this->icon.isNull())
    {
        loadError = QString("config_icon资源加载失败")+=iconPath;
    }


    str=fileConfig.readLine();
    first = str.indexOf(":");
    end = str.indexOf(";");
    QString name=str.mid(first+1,end-first-1);
    QString path = currentPath;
    path+=QString("/res/resource/config/");
    path+=name;
    mouse = path;

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
    QString bgmName=str.mid(first+1,end-first-1);
    QString soundPath = currentPath;
    soundPath+=QString("/res/resource/config/");
    soundPath+=bgmName;
    this->bgmPath = soundPath;


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
        Chapter* c = new Chapter(fileList[i].mid(0,fileList[i].indexOf('.')).toInt(),this);
        if(c->loadError != "")
        {
            this->loadError = c->loadError;
        }
        chapterMap.insert(c->getCurrentChapter(),c);
    }

//    for(int i=1;i<=this->chapterNum;i++)
//    {
//        Chapter* c = new Chapter(i,this);
//        if(c->loadError != "")
//        {
//            this->loadError = c->loadError;
//        }
//        chapterMap.insert(i,c);
//    }



    str=fileConfig.readLine();
    first = str.indexOf(":");
    end = str.indexOf(";");
    QString backName=str.mid(first+1,end-first-1);
    QString backPath = currentPath;
    backPath+=QString("/res/resource/config/");
    backPath+=backName;
    this->loadBackground = new QImage(backPath);
    if(this->loadBackground->isNull())
    {
        loadError = QString("config_background资源加载失败")+=backPath;
    }

    str=fileConfig.readLine();
    first = str.indexOf(":");
    end = str.indexOf(";");
    backName=str.mid(first+1,end-first-1);
    backPath = currentPath;
    backPath+=QString("/res/resource/config/");
    backPath+=backName;
    this->saveBackground = new QImage(backPath);
    if(this->saveBackground->isNull())
    {
        loadError = QString("config_background资源加载失败")+=backPath;
    }

    str=fileConfig.readLine();
    first = str.indexOf(":");
    end = str.indexOf(";");
    backName=str.mid(first+1,end-first-1);
    backPath = currentPath;
    backPath+=QString("/res/resource/config/");
    backPath+=backName;
    this->galleryBackground = new QImage(backPath);
    if(this->galleryBackground->isNull())
    {
        loadError = QString("config_background资源加载失败")+=backPath;
    }

    str=fileConfig.readLine();
    first = str.indexOf(":");
    end = str.indexOf(";");
    backName=str.mid(first+1,end-first-1);
    backPath = currentPath;
    backPath+=QString("/res/resource/config/");
    backPath+=backName;
    if(backName!="")
    {
            this->configBackground = new QImage(backPath);
            if(this->configBackground->isNull())
            {
                loadError = QString("config_background资源加载失败")+=backPath;
            }
    }


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
        QString nPath = currentPath;
        nPath+=QString("/res/resource/config/");
        nPath+=nName;

        int p3 = str.indexOf(":",p2+1);
        QString eName = str.mid(p2+1,p3-p2-1);
        QString ePath = currentPath;
        ePath+=QString("/res/resource/config/");
        ePath+=eName;

        int p4 = str.indexOf(":",p3+1);
        QString pName = str.mid(p3+1,p4-p3-1);
        QString pPath = currentPath;
        pPath+=QString("/res/resource/config/");
        pPath+=pName;

        int p5 = str.indexOf(":",p4+1);
        QString sName = str.mid(p4+1,p5-p4-1);
        QString sPath = currentPath;
        sPath+=QString("/res/resource/config/");
        sPath+=sName;

        int p6 = str.indexOf(":",p5+1);
        int x = str.mid(p5+1,p6-p5-1).toInt();
        int p7 = str.indexOf(":",p6+1);
        int y = str.mid(p6+1,p7-p6-1).toInt();
        int p8 = str.indexOf(":",p7+1);
        int w = str.mid(p7+1,p8-p7-1).toInt();
        int pend = str.indexOf(";");
        int h = str.mid(p8+1,pend-p8-1).toInt();

        NewPushButton* btn = new NewPushButton(nPath,ePath,pPath,sPath,QPoint(x,y),QSize(w,h));
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
    QString framePath = currentPath;
    framePath+=QString("/res/resource/config/");
    framePath+=frameName;
    QPixmap* name_pix = new QPixmap(framePath);
    if(name_pix->isNull())
    {
        loadError = QString("frame_name_pix加载失败")+=framePath;
    }

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
    nameFrame = new FrameInfo(name_pix,QPoint(fbX,fbY),QSize(fbW,fbH),QPoint(ftX,ftY),QSize(ftW,ftH),name_font);




    str=fileConfig.readLine();
    p1 = str.indexOf(":");
    p2 = str.indexOf(":",p1+1);
    frameName = str.mid(p1+1,p2-p1-1);
    framePath = currentPath;
    framePath+=QString("/res/resource/config/");
    framePath+=frameName;
    QPixmap* text_pix = new QPixmap(framePath);
    if(text_pix->isNull())
    {
        loadError = QString("frame_name_pix加载失败")+=framePath;
    }

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
    textFrame = new FrameInfo(text_pix,QPoint(fbX,fbY),QSize(fbW,fbH),QPoint(ftX,ftY),QSize(ftW,ftH),text_font);


    for(int i = 0;i<3;i++)
    {
        str=fileConfig.readLine();
        int p1 = str.indexOf(":");
        int p2 = str.indexOf(":",p1+1);
        QString nName = str.mid(p1+1,p2-p1-1);
        QString nPath = currentPath;
        nPath+=QString("/res/resource/config/");
        nPath+=nName;

        int p3 = str.indexOf(":",p2+1);
        QString eName = str.mid(p2+1,p3-p2-1);
        QString ePath = currentPath;
        ePath+=QString("/res/resource/config/");
        ePath+=eName;

        int p4 = str.indexOf(":",p3+1);
        QString pName = str.mid(p3+1,p4-p3-1);
        QString pPath = currentPath;
        pPath+=QString("/res/resource/config/");
        pPath+=pName;

        int p5 = str.indexOf(":",p4+1);
        QString sName = str.mid(p4+1,p5-p4-1);
        QString sPath = currentPath;
        sPath+=QString("/res/resource/config/");
        sPath+=sName;

        int p6 = str.indexOf(":",p5+1);
        int x = str.mid(p5+1,p6-p5-1).toInt();
        int p7 = str.indexOf(":",p6+1);
        int y = str.mid(p6+1,p7-p6-1).toInt();
        int p8 = str.indexOf(":",p7+1);
        int w = str.mid(p7+1,p8-p7-1).toInt();
        int pend = str.indexOf(";");
        int h = str.mid(p8+1,pend-p8-1).toInt();

        SwitchButton* btn = new SwitchButton(nPath,ePath,pPath,sPath,QPoint(x,y),QSize(w,h));
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
        QString nPath = currentPath;
        nPath+=QString("/res/resource/config/");
        nPath+=nName;

        int p3 = str.indexOf(":",p2+1);
        QString eName = str.mid(p2+1,p3-p2-1);
        QString ePath = currentPath;
        ePath+=QString("/res/resource/config/");
        ePath+=eName;

        int p4 = str.indexOf(":",p3+1);
        QString pName = str.mid(p3+1,p4-p3-1);
        QString pPath = currentPath;
        pPath+=QString("/res/resource/config/");
        pPath+=pName;

        int p5 = str.indexOf(":",p4+1);
        QString sName = str.mid(p4+1,p5-p4-1);
        QString sPath = currentPath;
        sPath+=QString("/res/resource/config/");
        sPath+=sName;

        int p6 = str.indexOf(":",p5+1);
        int x = str.mid(p5+1,p6-p5-1).toInt();
        int p7 = str.indexOf(":",p6+1);
        int y = str.mid(p6+1,p7-p6-1).toInt();
        int p8 = str.indexOf(":",p7+1);
        int w = str.mid(p7+1,p8-p7-1).toInt();
        int pend = str.indexOf(";");
        int h = str.mid(p8+1,pend-p8-1).toInt();

        NewPushButton* btn = new NewPushButton(nPath,ePath,pPath,sPath,QPoint(x,y),QSize(w,h));
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
        QString nPath = currentPath;
        nPath+=QString("/res/resource/config/");
        nPath+=nName;

        int p3 = str.indexOf(":",p2+1);
        QString eName = str.mid(p2+1,p3-p2-1);
        QString ePath = currentPath;
        ePath+=QString("/res/resource/config/");
        ePath+=eName;

        int p4 = str.indexOf(":",p3+1);
        QString pName = str.mid(p3+1,p4-p3-1);
        QString pPath = currentPath;
        pPath+=QString("/res/resource/config/");
        pPath+=pName;

        int p5 = str.indexOf(":",p4+1);
        QString sName = str.mid(p4+1,p5-p4-1);
        QString sPath = currentPath;
        sPath+=QString("/res/resource/config/");
        sPath+=sName;

        int p6 = str.indexOf(":",p5+1);
        int x = str.mid(p5+1,p6-p5-1).toInt();
        int p7 = str.indexOf(":",p6+1);
        int y = str.mid(p6+1,p7-p6-1).toInt();
        int p8 = str.indexOf(":",p7+1);
        int w = str.mid(p7+1,p8-p7-1).toInt();
        int pend = str.indexOf(";");
        int h = str.mid(p8+1,pend-p8-1).toInt();

        NewPushButton* btn = new NewPushButton(nPath,ePath,pPath,sPath,QPoint(x,y),QSize(w,h));
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
        QString path = currentPath;
        path+=QString("/res/resource/config/");
        path+=str.mid(p5+1,p6-p5-1);
        QPixmap* img = new QPixmap(path);

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
    sliderStyleSheet = str.mid(pbegins+1,pends-pbegins-1).arg(pixpath);
    //qDebug()<<sliderStyleSheet;


    //存档读档界面
    for(int i = 0;i<10;i++)
    {
        str=fileConfig.readLine();
        int p1 = str.indexOf(":");
        int p2 = str.indexOf(":",p1+1);
        QString nName = str.mid(p1+1,p2-p1-1);
        QString nPath = currentPath;
        nPath+=QString("/res/resource/config/");
        nPath+=nName;

        int p3 = str.indexOf(":",p2+1);
        QString eName = str.mid(p2+1,p3-p2-1);
        QString ePath = currentPath;
        ePath+=QString("/res/resource/config/");
        ePath+=eName;

        int p4 = str.indexOf(":",p3+1);
        QString pName = str.mid(p3+1,p4-p3-1);
        QString pPath = currentPath;
        pPath+=QString("/res/resource/config/");
        pPath+=pName;

        int p5 = str.indexOf(":",p4+1);
        QString sName = str.mid(p4+1,p5-p4-1);
        QString sPath = currentPath;
        sPath+=QString("/res/resource/config/");
        sPath+=sName;

        int p6 = str.indexOf(":",p5+1);
        int x = str.mid(p5+1,p6-p5-1).toInt();
        int p7 = str.indexOf(":",p6+1);
        int y = str.mid(p6+1,p7-p6-1).toInt();
        int p8 = str.indexOf(":",p7+1);
        int w = str.mid(p7+1,p8-p7-1).toInt();
        int pend = str.indexOf(";");
        int h = str.mid(p8+1,pend-p8-1).toInt();

        SwitchButton* btn = new SwitchButton(nPath,ePath,pPath,sPath,QPoint(x,y),QSize(w,h));
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
        QString nPath = currentPath;
        nPath+=QString("/res/resource/config/");
        nPath+=nName;

        int p3 = str.indexOf(":",p2+1);
        QString eName = str.mid(p2+1,p3-p2-1);
        QString ePath = currentPath;
        ePath+=QString("/res/resource/config/");
        ePath+=eName;

        int p4 = str.indexOf(":",p3+1);
        QString pName = str.mid(p3+1,p4-p3-1);
        QString pPath = currentPath;
        pPath+=QString("/res/resource/config/");
        pPath+=pName;

        int p5 = str.indexOf(":",p4+1);
        QString sName = str.mid(p4+1,p5-p4-1);
        QString sPath = currentPath;
        sPath+=QString("/res/resource/config/");
        sPath+=sName;

        int p6 = str.indexOf(":",p5+1);
        int x = str.mid(p5+1,p6-p5-1).toInt();
        int p7 = str.indexOf(":",p6+1);
        int y = str.mid(p6+1,p7-p6-1).toInt();
        int p8 = str.indexOf(":",p7+1);
        int w = str.mid(p7+1,p8-p7-1).toInt();
        int pend = str.indexOf(";");
        int h = str.mid(p8+1,pend-p8-1).toInt();

        NewPushButton* btn = new NewPushButton(nPath,ePath,pPath,sPath,QPoint(x,y),QSize(w,h));
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
        QString nPath = currentPath;
        nPath+=QString("/res/resource/config/");
        nPath+=nName;

        int p3 = str.indexOf(":",p2+1);
        QString eName = str.mid(p2+1,p3-p2-1);
        QString ePath = currentPath;
        ePath+=QString("/res/resource/config/");
        ePath+=eName;

        int p4 = str.indexOf(":",p3+1);
        QString pName = str.mid(p3+1,p4-p3-1);
        QString pPath = currentPath;
        pPath+=QString("/res/resource/config/");
        pPath+=pName;

        int p5 = str.indexOf(":",p4+1);
        QString sName = str.mid(p4+1,p5-p4-1);
        QString sPath = currentPath;
        sPath+=QString("/res/resource/config/");
        sPath+=sName;

        int p6 = str.indexOf(":",p5+1);
        int x = str.mid(p5+1,p6-p5-1).toInt();
        int p7 = str.indexOf(":",p6+1);
        int y = str.mid(p6+1,p7-p6-1).toInt();
        int p8 = str.indexOf(":",p7+1);
        int w = str.mid(p7+1,p8-p7-1).toInt();
        int pend = str.indexOf(";");
        int h = str.mid(p8+1,pend-p8-1).toInt();

        NewPushButton* btn = new NewPushButton(nPath,ePath,pPath,sPath,QPoint(x,y),QSize(w,h));
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
        QString nPath = currentPath;
        nPath+=QString("/res/resource/config/");
        nPath+=nName;

        int p3 = str.indexOf(":",p2+1);
        QString eName = str.mid(p2+1,p3-p2-1);
        QString ePath = currentPath;
        ePath+=QString("/res/resource/config/");
        ePath+=eName;

        int p4 = str.indexOf(":",p3+1);
        QString pName = str.mid(p3+1,p4-p3-1);
        QString pPath = currentPath;
        pPath+=QString("/res/resource/config/");
        pPath+=pName;

        int p5 = str.indexOf(":",p4+1);
        QString sName = str.mid(p4+1,p5-p4-1);
        QString sPath = currentPath;
        sPath+=QString("/res/resource/config/");
        sPath+=sName;

        int p6 = str.indexOf(":",p5+1);
        int x = str.mid(p5+1,p6-p5-1).toInt();
        int p7 = str.indexOf(":",p6+1);
        int y = str.mid(p6+1,p7-p6-1).toInt();
        int p8 = str.indexOf(":",p7+1);
        int w = str.mid(p7+1,p8-p7-1).toInt();
        int pend = str.indexOf(";");
        int h = str.mid(p8+1,pend-p8-1).toInt();

        SwitchButton* btn = new SwitchButton(nPath,ePath,pPath,sPath,QPoint(x,y),QSize(w,h));
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

QIcon Data::getIcon()
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

QImage *Data::getLoadBackground()
{
    return loadBackground;
}

QImage *Data::getSaveBackground()
{
    return saveBackground;
}

QImage *Data::getGalleryBackground()
{
    return galleryBackground;
}

QImage *Data::getConfigBackground()
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

ConfigSlider::ConfigSlider(QPoint pl, QSize sl, QPixmap *i, QPoint ps, QSize ss)
{
    posL = pl;
    sizeL = sl;
    imgL = i;
    posS = ps;
    sizeS = ss;
}
