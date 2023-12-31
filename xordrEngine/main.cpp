#include "mainwindow.h"

#include <QApplication>
#include <QSharedMemory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    static QSharedMemory *shareMem = new QSharedMemory( "Single"); //创建“SingleApp”的共享内存块
    if ( !shareMem->create( 1 ) )//创建大小1b的内存
    {
        qApp->quit(); //创建失败，说明已经有一个程序运行，退出当前程序
        return -1;
    }
    MainWindow w;
    w.show();
    return a.exec();
}
