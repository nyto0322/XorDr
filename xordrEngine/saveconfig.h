#ifndef SAVECONFIG_H
#define SAVECONFIG_H

#include <QObject>
#include <QCoreApplication>
#include <QFile>


extern int skipSpeed;
extern int autoSpeed;
extern int textShowSpeed;
extern int textSize;
extern int mainVolume;
extern int mainSceneBgmVolume;
extern int vocalVolume;
extern int bgmVolume;
extern int bgmVolumeWhenVocal;
extern int soundVolume;



class SaveConfig : public QObject
{
    Q_OBJECT
public:
    explicit SaveConfig(QObject *parent = nullptr);
    void load();
    void save(const char *newParameter = ";\n");

signals:

};

#endif // SAVECONFIG_H
