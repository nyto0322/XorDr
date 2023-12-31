#include "soundlist.h"
#include "ui_soundlist.h"

SoundList::SoundList(int c,int s,QVector<Sound> &v, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SoundList)
{
    ui->setupUi(this);
    currentChapter = c;
    currentSection = s;
    this->setWindowTitle(QString::number(c)+"-"+QString::number(s));


    int i = 0;
    for(QVector<Sound>::const_iterator it = v.constBegin();it!=v.constEnd();it++,i++)
    {
        ui->tableWidget->setRowCount(i+1);
        QTableWidgetItem* item1 = new QTableWidgetItem();
        item1->setText(it->m_soundPath);
        ui->tableWidget->setItem(i,0,item1);
        QTableWidgetItem* item2 = new QTableWidgetItem();
        item2->setText(QString::number(it->m_start));
        ui->tableWidget->setItem(i,1,item2);
        QPushButton* closebtn = new QPushButton(this);
        closebtn->setText("删除此项");
        ui->tableWidget->setCellWidget(i,2,closebtn);
        connect(closebtn,&QPushButton::clicked,[=](){
            ui->tableWidget->removeRow(i);
        });

    }

    connect(ui->pushButton,&QPushButton::clicked,[=](){
        QVector<Sound> temp;
        for(int i = 0;i<ui->tableWidget->rowCount();i++)
        {
            temp.push_back(Sound(ui->tableWidget->item(i,0)->text(),ui->tableWidget->item(i,1)->text().toInt()));
        }
        emit save(currentSection,temp);
        this->close();
    });

    connect(ui->btnAdd,&QPushButton::clicked,[=](){
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
        QPushButton* closebtn = new QPushButton(this);
        closebtn->setText("删除此项");
        ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,2,closebtn);
        connect(closebtn,&QPushButton::clicked,[=](){
            ui->tableWidget->removeRow(ui->tableWidget->rowCount()-1);
        });
    });

}



SoundList::~SoundList()
{
    delete ui;
}
