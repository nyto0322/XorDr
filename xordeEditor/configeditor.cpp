#include "configeditor.h"
#include "ui_configeditor.h"
#include "mainbacklist.h"

void ConfigEditor::save()
{
    data->setTitle(ui->lineTitle->text());
    data->setSize(QSize(ui->spinSizeX->value(),ui->spinSizeY->value()));
    data->setIcon(ui->lineIcon->text());
    data->setMouse(ui->lineMouse->text());
    data->setBgm(ui->lineBgm->text());
    data->setLoad(ui->lineLoad->text());
    data->setSave(ui->lineSave->text());
    data->setGal(ui->lineGal->text());
    data->setCon(ui->lineCon->text());
    data->setIniBack(ui->lineBack->text());
}

ConfigEditor::ConfigEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigEditor)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);

    mbl = new MainBackList();
    mbl->hide();
    connect(ui->btnBackSp,&QPushButton::clicked,[=](){
        QMap<int,QString> m = data->getMainPic();
        m[0]=ui->lineBack->text();
        mbl->init(m);
        mbl->show();
    });


    connect(ui->btnIcon,&QPushButton::clicked,[=](){
        QString str=QFileDialog::getOpenFileName(this,"Open Icon", "", "Icon Files (*.ico)");
        if(str!="")
        {
            ui->lineIcon->setText(str.mid(str.lastIndexOf('/')+1));
        }

    });
    connect(ui->btnMouse,&QPushButton::clicked,[=](){
        QString str=QFileDialog::getOpenFileName(this,"Open Image", "", "Image Files (*.png)");
        if(str!="")
        {
            ui->lineMouse->setText(str.mid(str.lastIndexOf('/')+1));
        }

    });
    connect(ui->btnBack,&QPushButton::clicked,[=](){
        QString str=QFileDialog::getOpenFileName(this,"Open Image", "", "Image Files (*.png)");
        if(str!="")
        {
            ui->lineBack->setText(str.mid(str.lastIndexOf('/')+1));
        }

    });
    connect(ui->btnBgm,&QPushButton::clicked,[=](){
        QString str=QFileDialog::getOpenFileName(this,"Open Sound", "", "Sound Files (*.ogg *.mp3 *.wav)");
        if(str!="")
        {
            ui->lineBgm->setText(str.mid(str.lastIndexOf('/')+1));
        }

    });
    connect(ui->btnLoad,&QPushButton::clicked,[=](){
        QString str=QFileDialog::getOpenFileName(this,"Open Image", "", "Image Files (*.png)");
        if(str!="")
        {
            ui->lineLoad->setText(str.mid(str.lastIndexOf('/')+1));
        }

    });
    connect(ui->btnSave,&QPushButton::clicked,[=](){
        QString str=QFileDialog::getOpenFileName(this,"Open Image", "", "Image Files (*.png)");
        if(str!="")
        {
            ui->lineSave->setText(str.mid(str.lastIndexOf('/')+1));
        }

    });
    connect(ui->btnCon,&QPushButton::clicked,[=](){
        QString str=QFileDialog::getOpenFileName(this,"Open Image", "", "Image Files (*.png)");
        if(str!="")
        {
            ui->lineCon->setText(str.mid(str.lastIndexOf('/')+1));
        }

    });
    connect(ui->btnGal,&QPushButton::clicked,[=](){
        QString str=QFileDialog::getOpenFileName(this,"Open Image", "", "Image Files (*.png)");
        if(str!="")
        {
            ui->lineGal->setText(str.mid(str.lastIndexOf('/')+1));
        }

    });

}

void ConfigEditor::init(Data * data)
{
    this->data = data;
    ui->lineTitle->setText(data->getTitle());
    ui->spinSizeX->setValue(data->getSize().width());
    ui->spinSizeY->setValue(data->getSize().height());
    ui->lineIcon->setText(data->getIcon());
    ui->lineMouse->setText(data->getMouse());
    ui->lineBack->setText(data->getMainPic()[0]);
    ui->lineBgm->setText(data->getBgmPath());
    ui->lineLoad->setText(data->getLoadBackground());
    ui->lineSave->setText(data->getSaveBackground());
    ui->lineGal->setText(data->getGalleryBackground());
    ui->lineCon->setText(data->getConfigBackground());
    connect(mbl,&MainBackList::save,data,&Data::setBack);
    connect(ui->win_save,&QPushButton::clicked,this,&ConfigEditor::save);
    connect(data,&Data::dataSaveBegin,this,&ConfigEditor::save);

}

ConfigEditor::~ConfigEditor()
{
    delete ui;
}
