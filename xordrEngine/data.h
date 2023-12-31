#ifndef DATA_H
#define DATA_H

#include <QObject>
#include "chapter.h"
#include <QString>
#include <QMap>
#include <QIcon>
#include <QSound>
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
    QPixmap* imgL;
    QPoint posS;
    QSize sizeS;
    ConfigSlider(QPoint,QSize,QPixmap*,QPoint,QSize);
};

class Data : public QObject
{
    Q_OBJECT

    QMap<int,Chapter*> chapterMap;//脚本
    QString title;
    QIcon icon;
    QString mouse;
    QMap<int,QString> mainPic;//主界面背景
    QString bgmPath;//主界面bgm
    int chapterNum;
    QImage* loadBackground;//其余界面背景
    QImage* saveBackground;
    QImage* galleryBackground;
    QImage* configBackground;

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




public:
    explicit Data(QObject *parent = nullptr);
    void loadData();
    QString loadError="";
    QString getMouse();
    QMap<int,QString> getMainPic();
    QIcon getIcon();
    QString getTitle();
    QString getBgmPath();
    QMap<int,NewPushButton*> getBeginBtn();
    QSize getSize();
    QMap<int,Chapter*> getChapterMap();
    FrameInfo* getNameFrame();
    FrameInfo* getTextFrame();
    QVector<NewPushButton*> getSceneBtn();
    QVector<SwitchButton *> getSceneSwitch();
    QImage* getLoadBackground();
    QImage* getSaveBackground();
    QImage* getGalleryBackground();
    QImage* getConfigBackground();
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





signals:

};

#endif // DATA_H
