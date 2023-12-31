#include "speciallist.h"
#include "ui_speciallist.h"

SpecialList::SpecialList(int c,int se,QVector<Special> &s, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpecialList)
{
    ui->setupUi(this);
    currentChapter = c;
    currentSection = se;
    this->setWindowTitle(QString::number(c)+"-"+QString::number(se));


    int i = 0;
    for(QVector<Special>::const_iterator it = s.constBegin();it!=s.constEnd();it++,i++)
    {
        ui->tableWidget->setRowCount(i+1);
        QTableWidgetItem* item1 = new QTableWidgetItem();
        item1->setText(it->m_special);
        ui->tableWidget->setItem(i,0,item1);
        QTableWidgetItem* item3 = new QTableWidgetItem();
        item3->setText(QString::number(it->m_point.x()));
        ui->tableWidget->setItem(i,1,item3);
        QTableWidgetItem* item4 = new QTableWidgetItem();
        item4->setText(QString::number(it->m_point.y()));
        ui->tableWidget->setItem(i,2,item4);
        QTableWidgetItem* item2 = new QTableWidgetItem();
        item2->setText(QString::number(it->m_start));
        ui->tableWidget->setItem(i,3,item2);
        QPushButton* closebtn = new QPushButton(this);
        closebtn->setText("删除此项");
        ui->tableWidget->setCellWidget(i,4,closebtn);
        connect(closebtn,&QPushButton::clicked,[=](){
            ui->tableWidget->removeRow(i);
        });

    }
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        QVector<Special> temp;
        for(int i = 0;i<ui->tableWidget->rowCount();i++)
        {
            temp.push_back(Special(ui->tableWidget->item(i,0)->text()
                                    ,ui->tableWidget->item(i,3)->text().toInt()
                                    ,QPoint(ui->tableWidget->item(i,1)->text().toInt()
                                            ,ui->tableWidget->item(i,2)->text().toInt())));
        }
        emit save(currentSection,temp);
        this->close();
    });


    connect(ui->btnAdd,&QPushButton::clicked,[=](){
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
        QPushButton* closebtn = new QPushButton(this);
        closebtn->setText("删除此项");
        ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,4,closebtn);
        connect(closebtn,&QPushButton::clicked,[=](){
            ui->tableWidget->removeRow(ui->tableWidget->rowCount()-1);
        });

    });




}

SpecialList::~SpecialList()
{
    delete ui;
}
