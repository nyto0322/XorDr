#include "choicelist.h"
#include "ui_choicelist.h"
#include "buttoneditor.h"

void ChoiceList::add()
{
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
    QPushButton* btn = new QPushButton(this);
    NewPushButton* nbtn = new NewPushButton();
    ChoicePushButton* cbtn = new ChoicePushButton(nbtn,"",1,QPoint(0,0),QSize(0,0),0,"0&");
    connect(btn,&QPushButton::clicked,[=](){
        ButtonEditor* ed = new ButtonEditor("",nbtn);
        ed->show();
        ed->setAttribute(Qt::WA_DeleteOnClose);
    });
    ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,2,btn);
    cbtnVec.push_back(cbtn);
    QPushButton* closebtn = new QPushButton(this);
    closebtn->setText("删除此项");
    ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,9,closebtn);
    connect(closebtn,&QPushButton::clicked,[=](){
        ui->tableWidget->removeRow(ui->tableWidget->rowCount()-1);
        cbtnVec.remove(ui->tableWidget->rowCount()-1);
    });

}

ChoiceList::ChoiceList(int c, int s, QVector<ChoicePushButton *> &v, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChoiceList)
{
    ui->setupUi(this);

    cbtnVec=v;

    currentChapter = c;
    currentSection = s;
    this->setWindowTitle(QString::number(c)+"-"+QString::number(s));

    int i = 0;
    for(QVector<ChoicePushButton*>::const_iterator it = v.constBegin();it!=v.constEnd();it++,i++)
    {
        ui->tableWidget->setRowCount(i+1);
        QTableWidgetItem* item1 = new QTableWidgetItem();
        item1->setText((*it)->text);
        ui->tableWidget->setItem(i,0,item1);
        QTableWidgetItem* item2 = new QTableWidgetItem();
        item2->setText(QString::number((*it)->next));
        ui->tableWidget->setItem(i,1,item2);


        QPushButton* btn = new QPushButton(this);
        connect(btn,&QPushButton::clicked,[=](){
            ButtonEditor* ed = new ButtonEditor((*it)->text,(NewPushButton*)(*it));
            ed->show();
            ed->setAttribute(Qt::WA_DeleteOnClose);
        });
        ui->tableWidget->setCellWidget(i,2,btn);



        QTableWidgetItem* item3 = new QTableWidgetItem();
        item3->setText(QString::number((*it)->getTextPos().x()));
        ui->tableWidget->setItem(i,3,item3);
        QTableWidgetItem* item4 = new QTableWidgetItem();
        item4->setText(QString::number((*it)->getTextPos().y()));
        ui->tableWidget->setItem(i,4,item4);
        QTableWidgetItem* item5 = new QTableWidgetItem();
        item5->setText(QString::number((*it)->size.width()));
        ui->tableWidget->setItem(i,5,item5);
        QTableWidgetItem* item6 = new QTableWidgetItem();
        item6->setText(QString::number((*it)->size.height()));
        ui->tableWidget->setItem(i,6,item6);
        QTableWidgetItem* item7 = new QTableWidgetItem();
        item7->setText(QString::number((*it)->fontDelta));
        ui->tableWidget->setItem(i,7,item7);
        QTableWidgetItem* item8 = new QTableWidgetItem();
        item8->setText((*it)->getShowAfterChapter());
        ui->tableWidget->setItem(i,8,item8);
        QPushButton* closebtn = new QPushButton(this);
        closebtn->setText("删除此项");
        ui->tableWidget->setCellWidget(i,9,closebtn);
        connect(closebtn,&QPushButton::clicked,[=](){
            ui->tableWidget->removeRow(i);
            cbtnVec.remove(i);
        });

    }



    connect(ui->pushButton,&QPushButton::clicked,[=](){
        QVector<ChoicePushButton*> temp;
        for(int i = 0;i<ui->tableWidget->rowCount();i++)
        {
            ChoicePushButton* c=new ChoicePushButton(*((NewPushButton*)(cbtnVec[i]))
                                                            ,ui->tableWidget->item(i,0)->text()
                                                            ,ui->tableWidget->item(i,1)->text().toInt()
                                                            ,QPoint(ui->tableWidget->item(i,3)->text().toInt()
                                                                    ,ui->tableWidget->item(i,4)->text().toInt())
                                                            ,QSize(ui->tableWidget->item(i,5)->text().toInt()
                                                                   ,ui->tableWidget->item(i,6)->text().toInt())
                                                            ,ui->tableWidget->item(i,7)->text().toInt()
                                                            ,ui->tableWidget->item(i,8)->text());
            temp.push_back(c);
        }
        emit save(currentSection,temp);
        this->close();
    });

    connect(ui->btnAdd,&QPushButton::clicked,this,&ChoiceList::add);
}

ChoiceList::~ChoiceList()
{
    delete ui;
}
