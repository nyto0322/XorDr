#include "mainbacklist.h"
#include "ui_mainbacklist.h"
#include <QTableWidget>
#include <QDebug>

MainBackList::MainBackList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainBackList)
{
    ui->setupUi(this);

    connect(ui->pushButton,&QPushButton::clicked,[=](){
        QMap<int,QString> temp;
        for(int i = 0;i<ui->tableWidget->rowCount();i++)
        {
            temp.insert(ui->tableWidget->item(i,0)->text().toInt(),ui->tableWidget->item(i,1)->text());
        }
        emit save(temp);
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

void MainBackList::init(QMap<int, QString>& m)
{
    this->m = m;
    int i = 0;
    ui->tableWidget->setRowCount(m.size());
    for(QMap<int,QString>::const_iterator it = m.constBegin();it!=m.constEnd();it++,i++)
    {
        QTableWidgetItem* item1 = new QTableWidgetItem();
        item1->setText(QString::number(it.key()));
        ui->tableWidget->setItem(i,0,item1);
        QTableWidgetItem* item2 = new QTableWidgetItem();
        item2->setText(it.value());
        ui->tableWidget->setItem(i,1,item2);
        QPushButton* closebtn = new QPushButton(this);
        closebtn->setText("删除此项");
        ui->tableWidget->setCellWidget(i,2,closebtn);
        connect(closebtn,&QPushButton::clicked,[=](){
            ui->tableWidget->removeRow(i);
        });
    }
}

MainBackList::~MainBackList()
{
    delete ui;
}
