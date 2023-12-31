#ifndef Chapter_H
#define Chapter_H

#include <QObject>

#include <QMap>
#include <QImage>
#include <QVector>
#include "figure.h"
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QString>
#include <QCoreApplication>
#include <QMovie>
#include "choicepushbutton.h"




class Dialog
{
    QString m_name;
    QString m_text;
    int m_size;

public:
    Dialog(QString,QString,int);
    QString getName();
    QString getText();
    int getFontDelta();

};




class Sound
{
    //friend Chapter;
    QString m_soundPath;
    int m_start;
public:
    Sound(QString,int);
    QString getSoundPath();
    int getStart();


};




class Special
{
    QMovie* m_special;
    QPoint m_point;
    int m_start;
public:
    Special(QMovie*,int,QPoint);
    QMovie* getSpecial()const;
    QPoint getPos();
    int getStart();

};





class Chapter : public QObject
{
    Q_OBJECT
    int currentChapter;
    int nextChapter;
    QMap<int,Dialog*> dialog;
    QMap<int,QString> vocal;
    QMap<int,QString> bgm;
    QMap<int,QVector<Figure>> perform;
    QMap<int,QString> cg;
    QMap<int,QImage*> background;
    QMap<int,QVector<Special>> special;
    QMap<int,QVector<Sound>> sound;
    QMap<int,QVector<ChoicePushButton*>> choice;
public:
    explicit Chapter(int,QObject *parent = nullptr);
    void loadChapter();
    QString loadError = "";

    QMap<int, Dialog *> getDialog();
    QMap<int,QString> getVocal();
    QMap<int,QString> getBgm();
    QMap<int,QVector<Figure>> getPerform();
    QMap<int, QString> getCg();
    QMap<int, QImage *> getBackground();
    QMap<int,QVector<Special>> getSpecial();
    QMap<int,QVector<Sound>> getSound();
    QMap<int,QVector<ChoicePushButton*>> getChoice();
    int getNextChapter();
    int getCurrentChapter();


signals:

};

#endif // Chapter_H
