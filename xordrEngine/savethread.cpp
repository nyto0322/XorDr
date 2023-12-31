#include "savethread.h"


SaveThread::SaveThread(QObject *parent) : QThread(parent)
{

}

void SaveThread::inputData(QMap<int, QMap<int, SingleData *>> m)
{
    saveData = m;
}

QByteArray SaveThread::getArr()
{
    return arr;
}

//void SaveThread::setThreadName(QString name)
//{
//    threadName = name;
//}

//实现run函数
void SaveThread::run()
{

//    QMutex mutex;
//    mutex.lock();
    //
//    mutex.unlock();
    QString currentPath = QCoreApplication::applicationDirPath();

    QString newParameter = ":";
    arr = "";
    for(int i = 0;i<10;i++)
    {
        for(int j = 0;j<10;j++)
        {
            QString aNormalSaveData = "n:"
                    + QString::number(this->saveData[i][j]->currentChapter)+newParameter
                    + QString::number(this->saveData[i][j]->currentSection)+newParameter
                    + QString::number(this->saveData[i][j]->previousChapter)+newParameter
                    + QString::number(this->saveData[i][j]->nextChapter)+newParameter
                    + this->saveData[i][j]->dateTime+newParameter
                    + this->saveData[i][j]->currentText
                    + ";\n";
            arr+=aNormalSaveData;
            QString filename = QString("%1/res/savedata/%2%3.png").arg(currentPath).arg(i).arg(j);
            if(!this->saveData[i][j]->currentPix->isNull())
            {
                this->saveData[i][j]->currentPix->save(filename);
            }
        }
    }

    QThread::sleep(1);
    emit isover();

}

//执行线程
//MyThread thread1;
//thread1.setThreadName("thread1");
//thread1.start();

//MyThread thread1;
//thread1.setThreadName("thread2");
//thread1.start();
