#ifndef DATA_H
#define DATA_H

#include <QObject>
#include "chapter.h"
#include <QString>
#include <QMap>
#include <QIcon>
#include <QImage>
#include <QPixmap>
#include "newpushbutton.h"
#include <QSize>
#include <QLabel>
#include "frameinfo.h"
#include "switchbutton.h"
#include <QDir>



struct ConfigSlider
{
    QPoint posL;
    QSize sizeL;
    QString imgL;
    QPoint posS;
    QSize sizeS;
    ConfigSlider(QPoint,QSize,QString,QPoint,QSize);
};

class Data : public QObject
{
    Q_OBJECT
    QString currentPath;

    QMap<int,Chapter*> chapterMap;//脚本
    QString title;
    QString icon;
    QString mouse;
    QMap<int,QString> mainPic;//主界面背景
    QString bgmPath;//主界面bgm
    int chapterNum;
    QString loadBackground;//其余界面背景
    QString saveBackground;
    QString galleryBackground;
    QString configBackground;

    QMap<int,NewPushButton*> beginBtn;//主界面按钮
    QSize size;//窗体大小
    FrameInfo* nameFrame;
    FrameInfo* textFrame;
    QVector<SwitchButton*> sceneSwitch;//sceneplay界面开关
    QVector<NewPushButton*> sceneBtn;//sceneplay界面按钮
    QVector<NewPushButton*> otherPlayerBtn;
    QVector<ConfigSlider*> configSlider;//config界面
    QString sliderStyleSheet;
    QString historyStyleSheet;
    QVector<SwitchButton*> dataPlayerIndexBtn;//存档读档界面
    QVector<NewPushButton*> dataPlayerBtn;

    QPoint gallerycgPos;
    int gallerycgWidth;
    int gallerycgColumn;
    int gallerycgRow;
    QString gallerycgStyleSheet;

    QRect gallerymediaRect;
    QRect gallerymediaSliderRect;
    QVector<NewPushButton*> gallerymediaBtn;
    QVector<SwitchButton*> gallerymediaSwitch;
    QString gallerymediaStyleSheet;



    QString ssl(QString);
    QString ssl(NewPushButton*);
    QString ssl(SwitchButton*);
    QString ssl(QMap<int,QString>);
    QString ssl(FrameInfo);
    QString ssl(ConfigSlider *);

    void removeAllfile(QString);




public:
    explicit Data(QString,QObject *parent = nullptr);
    void loadData(QString);
    QString loadError="";
    QString getMouse();
    QMap<int,QString> getMainPic();
    QString getIcon();
    QString getTitle();
    QString getBgmPath();
    QMap<int,NewPushButton*> getBeginBtn();
    QSize getSize();
    QMap<int,Chapter*> getChapterMap();
    FrameInfo* getNameFrame();
    FrameInfo* getTextFrame();
    QVector<NewPushButton*> getSceneBtn();
    QVector<SwitchButton *> getSceneSwitch();
    QString getLoadBackground();
    QString getSaveBackground();
    QString getGalleryBackground();
    QString getConfigBackground();
    QVector<NewPushButton*> getOtherPlayerBtn();

    QVector<ConfigSlider*> getConfigSlider();
    QString getSliderStyleSheet();
    QString getHistoryStyleSheet();

    QVector<SwitchButton*> getDataPlayerIndexBtn();
    QVector<NewPushButton*> getDataPlayerBtn();

    QPoint getGallerycgPos();
    int getGallerycgWidth();
    int getGallerycgColumn();
    int getGallerycgRow();
    QString getGallerycgStyleSheet();

    QRect getGallerymediaRect();
    QRect getGallerymediaSliderRect();
    QVector<NewPushButton*> getGallerymediaBtn();
    QVector<SwitchButton*> getGallerymediaSwitch();
    QString getGallerymediaStyleSheet();

    QString getCurrentPath();



    void insertChapter(Chapter* );
    void setTitle(QString);
    void setSize(QSize);
    void setIcon(QString);
    void setMouse(QString);
    void setBack(QMap<int,QString>);
    void setIniBack(QString);
    void setBgm(QString);
    void setLoad(QString);
    void setSave(QString);
    void setGal(QString);
    void setCon(QString);
    void setNameFrame(FrameInfo*);
    void setTextFrame(FrameInfo*);
    void setSliderStyleSheet(QString);
    void setHistoryStyleSheet(QString);
    void setGallerycgStyleSheet(QString);
    void setGallerymediaStyleSheet(QString);

    void removeChapter(int);



    void save();



signals:
    void dataSaveBegin();
};

#endif // DATA_H
