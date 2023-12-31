#include "buttoneditor.h"
#include "ui_buttoneditor.h"

ButtonEditor::ButtonEditor(QString name,NewPushButton* btn,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ButtonEditor)
{
    ui->setupUi(this);


    this->setWindowTitle(name);
    this->init(btn);
    connect(ui->saveBtn,&QPushButton::clicked,[=](){
        btn->setNormal(ui->normalLine->text());
        btn->setEnter(ui->enterLine->text());
        btn->setPress(ui->pressLine->text());
        btn->setSound(ui->soundLine->text());
        btn->setPos(QPoint(ui->X->value(),ui->Y->value()));
        btn->setSize(QSize(ui->W->value(),ui->H->value()));
        this->close();
    });

    connect(ui->normalBtn,&QPushButton::clicked,[=](){
        QString str=QFileDialog::getOpenFileName(this,"Open Image", "", "Image Files (*.png)");
        if(str!="")
        {
            ui->normalLine->setText(str.mid(str.lastIndexOf('/')+1));
        }
    });
    connect(ui->enterBtn,&QPushButton::clicked,[=](){
        QString str=QFileDialog::getOpenFileName(this,"Open Image", "", "Image Files (*.png)");
        if(str!="")
        {
            ui->enterLine->setText(str.mid(str.lastIndexOf('/')+1));
        }

    });
    connect(ui->pressBtn,&QPushButton::clicked,[=](){
        QString str=QFileDialog::getOpenFileName(this,"Open Image", "", "Image Files (*.png)");
        if(str!="")
        {
            ui->pressLine->setText(str.mid(str.lastIndexOf('/')+1));
        }

    });
    connect(ui->soundBtn,&QPushButton::clicked,[=](){
        QString str=QFileDialog::getOpenFileName(this,"Open Sound", "", "Sound Files (*.ogg)");
        if(str!="")
        {
            ui->soundLine->setText(str.mid(str.lastIndexOf('/')+1));
        }
    });
}

ButtonEditor::ButtonEditor(QString name, SwitchButton *btn, QWidget *parent):
    QWidget(parent),
    ui(new Ui::ButtonEditor)
{
    ui->setupUi(this);

    this->setWindowTitle(name);
    this->init(btn);
    connect(ui->saveBtn,&QPushButton::clicked,[=](){
        btn->setNormal(ui->normalLine->text());
        btn->setEnter(ui->enterLine->text());
        btn->setPress(ui->pressLine->text());
        btn->setSound(ui->soundLine->text());
        btn->setPos(QPoint(ui->X->value(),ui->Y->value()));
        btn->setSize(QSize(ui->W->value(),ui->H->value()));
        this->close();
    });

    connect(ui->normalBtn,&QPushButton::clicked,[=](){
        QString str=QFileDialog::getOpenFileName(this,"Open Image", "", "Image Files (*.png)");
        if(str!="")
        {
            ui->normalLine->setText(str.mid(str.lastIndexOf('/')+1));
        }
    });
    connect(ui->enterBtn,&QPushButton::clicked,[=](){
        QString str=QFileDialog::getOpenFileName(this,"Open Image", "", "Image Files (*.png)");
        if(str!="")
        {
            ui->enterLine->setText(str.mid(str.lastIndexOf('/')+1));
        }

    });
    connect(ui->pressBtn,&QPushButton::clicked,[=](){
        QString str=QFileDialog::getOpenFileName(this,"Open Image", "", "Image Files (*.png)");
        if(str!="")
        {
            ui->pressLine->setText(str.mid(str.lastIndexOf('/')+1));
        }

    });
    connect(ui->soundBtn,&QPushButton::clicked,[=](){
        QString str=QFileDialog::getOpenFileName(this,"Open Sound", "", "Sound Files (*.ogg)");
        if(str!="")
        {
            ui->soundLine->setText(str.mid(str.lastIndexOf('/')+1));
        }
    });



}

void ButtonEditor::init(NewPushButton *btn)
{
    ui->normalLine->setText(btn->normalImgPath);
    ui->enterLine->setText(btn->enterImgPath);
    ui->pressLine->setText(btn->pressImgPath);
    ui->soundLine->setText(btn->clickSoundPath);
    ui->X->setValue(btn->getPos().x());
    ui->Y->setValue(btn->getPos().y());
    ui->W->setValue(btn->size.width());
    ui->H->setValue(btn->size.height());

}

void ButtonEditor::init(SwitchButton *btn)
{
    ui->normalLine->setText(btn->normalImgPath);
    ui->enterLine->setText(btn->enterImgPath);
    ui->pressLine->setText(btn->pressImgPath);
    ui->soundLine->setText(btn->clickSoundPath);
    ui->X->setValue(btn->getPos().x());
    ui->Y->setValue(btn->getPos().y());
    ui->W->setValue(btn->size.width());
    ui->H->setValue(btn->size.height());

}

ButtonEditor::~ButtonEditor()
{
    delete ui;
}
