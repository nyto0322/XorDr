#ifndef GALLERYPLAYER_H
#define GALLERYPLAYER_H

#include <QWidget>
#include "newpushbutton.h"
#include "data.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QListWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QMouseEvent>
#include <QMap>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QDir>
#include <QLabel>
#include <QImage>
#include <QPixmap>


class GalleryPlayer : public QWidget
{
    Q_OBJECT
    NewPushButton* toMainBtn;
    QMap<int,QMap<int,QImage*>> itemMap;
    QTableWidget* tableWidget;
    QLabel* cgShow;
    QWidget* mediaWidget;

    QListWidget* listWidget;
    QMediaPlaylist* playList;
    QMediaPlaylist* singlePlayList;
    QMediaPlayer* player;

    QMap<QListWidgetItem*,int> bgmItemMap;

    NewPushButton* preBtn;
    NewPushButton* nextBtn;
    SwitchButton* playBtn;
    SwitchButton* modeBtn;

    void previousBtnClicked();
    void nextBtnClicked();
    void playBtnClicked(bool);
    void modeBtnClicked(bool);
    void listBtnClicked(QListWidgetItem*);

    void mousePressEvent(QMouseEvent* );
public:
    explicit GalleryPlayer(Data* ,QWidget *parent = nullptr);

signals:
    void toMain();
    void stopMainBgm();

};

#endif // GALLERYPLAYER_H
