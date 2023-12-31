#ifndef SAVEDATA_H
#define SAVEDATA_H

#include <QObject>
#include <QVector>
#include <singledata.h>
#include <QMap>
#include <QImage>
#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QPixmap>



class SingleData : public QObject
{
    Q_OBJECT
public:
    explicit SingleData(int = -1,int = -1,int = -1,int = -1,QString = "",QObject *parent = nullptr,QString = "",QPixmap* = nullptr);
    int previousChapter;
    int currentChapter;
    int currentSection;
    int nextChapter;
    QString dateTime;
    QString currentText;
    QPixmap* currentPix;


signals:

};


class SaveData : public QObject
{
    Q_OBJECT
public:
    SingleData* qSaveData;
    QMap<int,QMap<int,SingleData*>> saveData;
    QMap<int,int> haveRead;
    QString mainPicName;
    QImage* mainPic;
    bool galleryIsOpen;
    explicit SaveData(QObject *parent = nullptr);

    void save(const char *newParameter = ":");
    void load();
    void saveHaveRead();

signals:

};



#endif // SAVEDATA_H
