#include "saveconfig.h"


int skipSpeed = 0;
int autoSpeed = 0;
int textShowSpeed = 0;
int textSize = 0;
int mainVolume = 100;
int mainSceneBgmVolume = 100;
int vocalVolume = 100;
int bgmVolume = 100;
int bgmVolumeWhenVocal = 100;
int soundVolume = 100;

SaveConfig::SaveConfig(QObject *parent) : QObject(parent)
{
    load();
}

void SaveConfig::load()
{
    QString currentPath = QCoreApplication::applicationDirPath();
    QString filePathC = QString("%1/res/saveconfig.txt").arg(currentPath);
    QFile fileConfig(filePathC);
    fileConfig.open(QIODevice::ReadOnly);

    QString str=fileConfig.readLine();
    int end = str.indexOf(";");
    skipSpeed = str.mid(0,end).toInt();
    str=fileConfig.readLine();
    end = str.indexOf(";");
    autoSpeed = str.mid(0,end).toInt();
    str=fileConfig.readLine();
    end = str.indexOf(";");
    textShowSpeed = str.mid(0,end).toInt();
    str=fileConfig.readLine();
    end = str.indexOf(";");
    textSize = str.mid(0,end).toInt();
    str=fileConfig.readLine();
    end = str.indexOf(";");
    mainVolume = str.mid(0,end).toInt();
    str=fileConfig.readLine();
    end = str.indexOf(";");
    mainSceneBgmVolume = str.mid(0,end).toInt();
    str=fileConfig.readLine();
    end = str.indexOf(";");
    vocalVolume = str.mid(0,end).toInt();
    str=fileConfig.readLine();
    end = str.indexOf(";");
    bgmVolume = str.mid(0,end).toInt();
    str=fileConfig.readLine();
    end = str.indexOf(";");
    bgmVolumeWhenVocal = str.mid(0,end).toInt();
    str=fileConfig.readLine();
    end = str.indexOf(";");
    soundVolume = str.mid(0,end).toInt();
    fileConfig.close();

}

void SaveConfig::save(const char *newParameter)
{
    QString currentPath = QCoreApplication::applicationDirPath();
    QString filePathC = QString("%1/res/saveconfig.txt").arg(currentPath);
    QFile fileConfig(filePathC);
    fileConfig.open(QIODevice::WriteOnly);

    QByteArray arr;
    arr += QString::number(skipSpeed)+newParameter;
    arr += QString::number(autoSpeed)+newParameter;
    arr += QString::number(textShowSpeed)+newParameter;
    arr += QString::number(textSize)+newParameter;
    arr += QString::number(mainVolume)+newParameter;
    arr += QString::number(mainSceneBgmVolume)+newParameter;
    arr += QString::number(vocalVolume)+newParameter;
    arr += QString::number(bgmVolume)+newParameter;
    arr += QString::number(bgmVolumeWhenVocal)+newParameter;
    arr += QString::number(soundVolume)+newParameter;




    fileConfig.write(arr);
    fileConfig.close();


}
