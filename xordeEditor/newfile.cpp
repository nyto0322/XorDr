#include "newfile.h"
#include "ui_newfile.h"

NewFile::NewFile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewFile)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_DeleteOnClose);

    connect(ui->win_save,&QPushButton::clicked,[=](){
        if(ui->lineName->text()!=""&&ui->lineName->text()!="")
        {
            emit create(ui->lineName->text(),ui->linePath->text());
            this->close();
        }
    });

    connect(ui->win_cancel,&QPushButton::clicked,[=](){
        this->close();
    });

    connect(ui->btnFile,&QPushButton::clicked,[=](){
        QFileDialog* file = new QFileDialog(this);
        file->setFileMode(QFileDialog::Directory);
        ui->linePath->setText( file->getExistingDirectory());


    });
}

NewFile::~NewFile()
{
    delete ui;
}
