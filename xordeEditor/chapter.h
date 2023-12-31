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
#include <QDir>




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
public:
    QString m_soundPath;
    int m_start;
public:
    Sound(QString,int);
    QString getSoundPath();
    int getStart();
};




class Special
{
public:
    QString m_special;
    QPoint m_point;
    int m_start;
public:
    Special(QString, int, QPoint);
    QString getSpecial()const;
    QPoint getPos();
    int getStart();

};





class Chapter : public QObject
{
    Q_OBJECT
    int currentChapter;
    int nextChapter;
    //QString
    QMap<int,Dialog*> dialog;
    QMap<int,QString> vocal;
    QMap<int,QString> bgm;
    QMap<int,QVector<Figure>> perform;
    QMap<int,QString> cg;
    QMap<int,QString> background;
    QMap<int,QVector<Special>> special;
    QMap<int,QVector<Sound>> sound;
    QMap<int,QVector<ChoicePushButton*>> choice;
public:
    explicit Chapter(QString, int, QObject *parent = nullptr);
    void loadChapter(QString filePath);
    QString loadError = "";

    QMap<int, Dialog *> getDialog();
    QMap<int,QString> getVocal();
    QMap<int,QString> getBgm();
    QMap<int,QVector<Figure>> getPerform();
    QMap<int, QString> getCg();
    QMap<int, QString> getBackground();
    QMap<int,QVector<Special>> getSpecial();
    QMap<int,QVector<Sound>> getSound();
    QMap<int,QVector<ChoicePushButton*>> getChoice();
    int getNextChapter();
    int getCurrentChapter();


    void setDialog(int, Dialog *);
    void setVocal(int,QString);
    void setBgm(int,QString);
    void setPerform(int,QVector<Figure>);
    void setCg(int, QString);
    void setBackground(int, QString);
    void setSpecial(int,QVector<Special>);
    void setSound(int,QVector<Sound>);
    void setChoice(int,QVector<ChoicePushButton*>);
    void setNextChapter(int);
    void setCurrentChapter(int);


    void remove(int);

    template<typename T>
    void removeM(QMap<int,T>& m,int currentSection);
    template<typename T>
    void insertM(QMap<int,T>& m,int currentSection);

    void insert(int);
    void save(QString);


signals:
    void chapterSaveBegin();

};



template<typename T>
void Chapter::removeM(QMap<int,T>& m,int currentSection)
{
    int m_net = currentSection;
    typename QMap<int,T>::const_iterator vit1 = m.constFind(currentSection);
    typename QMap<int,T>::const_iterator vit2;
    while(1)
    {
        if(!m.contains(m_net))
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
                vit2=m.constFind(m_net)+1;
            }
            else
            {
                vit2=m.constFind(m_net);
            }

            break;
        }
    }

    QMap<int,T> temp_m;
    bool t = false;
    for(typename QMap<int,T>::const_iterator it = m.constBegin();it!=m.constEnd();it++)
    {
        if(vit1!=m.constEnd()&&it==vit1)//vit1存在
        {
            t=true;//下一轮开始更改key
            continue;//自身不拷贝
        }
        else if(it==vit2)//vit1不存在
        {
            t=true;
        }


        if(!t)
        {
            temp_m.insert(it.key(),it.value());
        }
        else
        {
            temp_m.insert(it.key()-1,it.value());
        }
    }
    m.clear();
    m=temp_m;
}




template<typename T>
void Chapter::insertM(QMap<int,T>& mv,int currentSection)
{
    if(currentSection!=dialog.size()+1)
    {
        int mv_net = currentSection;
        typename QMap<int,T>::const_iterator vvit1 = mv.constFind(currentSection);
        typename QMap<int,T>::const_iterator vvit2;
        while(1)
        {
            if(!mv.contains(mv_net))
            {
                mv_net++;
                if(mv_net>dialog.size())
                {
                    break;
                }
            }
            else
            {
                if(currentSection==mv_net)
                {
                    vvit2=mv.constFind(mv_net)+1;
                }
                else
                {
                    vvit2=mv.constFind(mv_net);
                }

                break;
            }
        }

        QMap<int,T> temp_mv;
        bool tv = false;
        for(typename QMap<int,T>::const_iterator it = mv.constBegin();it!=mv.constEnd();it++)
        {
            if(vvit1!=mv.constEnd())//vit1存在
            {
                if(it==vvit1)
                {
                    tv=true;//下一轮开始更改key
                }
            }
            else//vit1不存在
            {
                if(it==vvit2)
                {
                    tv=true;
                }
            }


            if(!tv)
            {
                temp_mv.insert(it.key(),it.value());
            }
            else
            {
                temp_mv.insert(it.key()+1,it.value());
            }
        }
        mv.clear();
        mv=temp_mv;
    }

}



#endif // Chapter_H
