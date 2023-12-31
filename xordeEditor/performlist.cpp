#include "performlist.h"
#include "ui_performlist.h"

PerformList::PerformList(int c,int s,QVector<Figure> &f, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PerformList)
{
    ui->setupUi(this);
    currentChapter = c;
    currentSection = s;
    this->setWindowTitle(QString::number(c)+"-"+QString::number(s));


    int i = 0;
    ui->tableWidget->setRowCount(f.size());
    for(QVector<Figure>::const_iterator it = f.constBegin();it!=f.constEnd();it++,i++)
    {
        QTableWidgetItem* item1 = new QTableWidgetItem();
        item1->setText(it->m_mainfig);
        ui->tableWidget->setItem(i,0,item1);
        QTableWidgetItem* item2 = new QTableWidgetItem();
        item2->setText(it->m_status);
        ui->tableWidget->setItem(i,1,item2);
        QTableWidgetItem* item3 = new QTableWidgetItem();
        item3->setText(QString::number(it->m_pos.x()));
        ui->tableWidget->setItem(i,2,item3);
        QTableWidgetItem* item4 = new QTableWidgetItem();
        item4->setText(QString::number(it->m_pos.y()));
        ui->tableWidget->setItem(i,3,item4);
        QTableWidgetItem* item5 = new QTableWidgetItem();
        item5->setText(QString::number(it->m_size));
        ui->tableWidget->setItem(i,4,item5);
        QTableWidgetItem* item6 = new QTableWidgetItem();
        item6->setText(QString::number(it->m_start));
        ui->tableWidget->setItem(i,5,item6);
        QTableWidgetItem* item7 = new QTableWidgetItem();
        item7->setText(QString::number(it->m_duration));
        ui->tableWidget->setItem(i,6,item7);
        QTableWidgetItem* item8 = new QTableWidgetItem();
        item8->setText(QString::number(it->m_jrSize));
        ui->tableWidget->setItem(i,7,item8);
        QTableWidgetItem* item9 = new QTableWidgetItem();
        item9->setText(it->m_animation);
        ui->tableWidget->setItem(i,8,item9);
        QTableWidgetItem* item10 = new QTableWidgetItem();
        item10->setText(QString::number(it->m_ani_start));
        ui->tableWidget->setItem(i,9,item10);
        QTableWidgetItem* item11 = new QTableWidgetItem();
        item11->setText(QString::number(it->m_ani_duration));
        ui->tableWidget->setItem(i,10,item11);
        QTableWidgetItem* item12 = new QTableWidgetItem();
        item12->setText(QString::number(it->m_ani_range));
        ui->tableWidget->setItem(i,11,item12);
        QPushButton* closebtn = new QPushButton(this);
        closebtn->setText("删除此项");
        ui->tableWidget->setCellWidget(i,12,closebtn);
        connect(closebtn,&QPushButton::clicked,[=](){
            ui->tableWidget->removeRow(i);
        });

    }
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        QVector<Figure> temp;
        for(int i = 0;i<ui->tableWidget->rowCount();i++)
        {
            temp.push_back(Figure(ui->tableWidget->item(i,0)->text()
                                  ,ui->tableWidget->item(i,1)->text()
                                  ,QPoint(ui->tableWidget->item(i,2)->text().toInt()
                                          ,ui->tableWidget->item(i,3)->text().toInt())
                                  ,ui->tableWidget->item(i,4)->text().toDouble()
                                  ,ui->tableWidget->item(i,5)->text().toDouble()
                                  ,ui->tableWidget->item(i,6)->text().toDouble()
                                  ,ui->tableWidget->item(i,7)->text().toDouble()
                                  ,ui->tableWidget->item(i,8)->text()
                                  ,ui->tableWidget->item(i,9)->text().toDouble()
                                  ,ui->tableWidget->item(i,10)->text().toDouble()
                                  ,ui->tableWidget->item(i,11)->text().toInt()));
        }
        emit save(currentSection,temp);
        this->close();
    });

    connect(ui->btnAdd,&QPushButton::clicked,[=](){
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
        QPushButton* closebtn = new QPushButton(this);
        closebtn->setText("删除此项");
        ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,12,closebtn);
        connect(closebtn,&QPushButton::clicked,[=](){
            ui->tableWidget->removeRow(ui->tableWidget->rowCount()-1);
        });
    });

}


PerformList::~PerformList()
{
    delete ui;
}
