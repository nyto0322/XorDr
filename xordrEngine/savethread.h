#ifndef SAVETHREAD_H
#define SAVETHREAD_H

#include <QObject>
#include <QThread>
#include <QMap>
#include <QByteArray>
#include <QMutex>
#include <QString>
#include <QByteArray>
#include <QCoreApplication>
#include "sdata.h"

class SaveThread : public QThread
{
    Q_OBJECT
    //QThread* saveThread;
    //QString threadName;
    QMap<int,QMap<int,SingleData*>> saveData;
    QByteArray arr = "";


protected:
    virtual void run();



public:
    //void setThreadName(QString);
    explicit SaveThread(QObject *parent = nullptr);
    void inputData(QMap<int,QMap<int,SingleData*>>  );
    QByteArray getArr();



signals:
    void isover();




};

#endif // SAVETHREAD_H
