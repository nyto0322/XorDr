#include "singlesectioneditor.h"
#include "ui_singlesectioneditor.h"
#include "choicelist.h"
#include "performlist.h"
#include "speciallist.h"
#include "soundlist.h"

SingleSectionEditor::SingleSectionEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SingleSectionEditor)
{
    ui->setupUi(this);
    connect(ui->vocalBtn,&QPushButton::clicked,[=](){
        QString str=QFileDialog::getOpenFileName(this,"Open Sound", "", "Sound Files (*.mp3 *.ogg *.wav)");
        if(str!="")
        {
            ui->vocalLine->setText(str.mid(str.lastIndexOf('/')+1));
        }

    });
    connect(ui->bgmBtn,&QPushButton::clicked,[=](){
        QString str=QFileDialog::getOpenFileName(this,"Open Sound", "", "Sound Files (*.mp3 *.ogg *.wav)");
        if(str!="")
        {
            ui->bgmLine->setText(str.mid(str.lastIndexOf('/')+1));
        }

    });
    connect(ui->cgBtn,&QPushButton::clicked,[=](){
        QString str=QFileDialog::getOpenFileName(this,"Open Image", "", "Image Files (*.png)");
        if(str!="")
        {
            ui->cgLine->setText(str.mid(str.lastIndexOf('/')+1));
        }

    });
    connect(ui->backBtn,&QPushButton::clicked,[=](){
        QString str=QFileDialog::getOpenFileName(this,"Open Image", "", "Image Files (*.png)");
        if(str!="")
        {
            ui->backLine->setText(str.mid(str.lastIndexOf('/')+1));
        }

    });
}

void SingleSectionEditor::init(int cs, Chapter *c)
{
    chapter = c;
    currentSection = cs;
    ui->groupBox->setTitle(QString::number(cs));
    ui->dialogNameLine->setText(c->getDialog()[cs]->getName());
    ui->dialogTextLine->setText(c->getDialog()[cs]->getText());
    ui->dialogFontSize->setValue(c->getDialog()[cs]->getFontDelta());
    ui->bgmLine->setText(c->getBgm()[cs]);
    ui->vocalLine->setText(c->getVocal()[cs]);
    ui->cgLine->setText(c->getCg()[cs]);
    ui->backLine->setText(c->getBackground()[cs]);


    connect(ui->performBtn,&QPushButton::clicked,[=](){
        PerformList* pl = new PerformList(c->getCurrentChapter(),cs,c->getPerform()[cs]);
        pl->show();
        pl->setAttribute(Qt::WA_DeleteOnClose);
        connect(pl,&PerformList::save,c,&Chapter::setPerform);          //接受list的save信号
    });
    connect(ui->specialBtn,&QPushButton::clicked,[=](){
        SpecialList* sl = new SpecialList(c->getCurrentChapter(),cs,c->getSpecial()[cs]);
        sl->show();
        sl->setAttribute(Qt::WA_DeleteOnClose);
        connect(sl,&SpecialList::save,c,&Chapter::setSpecial);
    });
    connect(ui->soundBtn,&QPushButton::clicked,[=](){
        SoundList* sl = new SoundList(c->getCurrentChapter(),cs,c->getSound()[cs]);
        sl->show();
        sl->setAttribute(Qt::WA_DeleteOnClose);
        connect(sl,&SoundList::save,c,&Chapter::setSound);
    });
    connect(ui->choiceBtn,&QPushButton::clicked,[=](){
        ChoiceList* cl = new ChoiceList(c->getCurrentChapter(),cs,c->getChoice()[cs]);
        cl->show();
        cl->setAttribute(Qt::WA_DeleteOnClose);
        connect(cl,&ChoiceList::save,c,&Chapter::setChoice);
    });
    connect(ui->btnRemoveThis,&QPushButton::clicked,[=](){
        chapter->remove(currentSection);
        emit reInit();        //使得chaptereditor对界面进行更新
    });
    connect(ui->btnAddUp,&QPushButton::clicked,[=](){
        chapter->insert(currentSection);
        emit reInit();
    });
    connect(ui->btnAddDown,&QPushButton::clicked,[=](){
        chapter->insert(currentSection+1);
        emit reInit();
    });

}

SingleSectionEditor::~SingleSectionEditor()
{
    delete ui;
}

void SingleSectionEditor::save()
{
    chapter->setDialog(currentSection,new Dialog(ui->dialogNameLine->text()
                                                ,ui->dialogTextLine->text()
                                                ,ui->dialogFontSize->value()));
    chapter->setCg(currentSection,ui->cgLine->text());
    chapter->setBgm(currentSection,ui->bgmLine->text());
    chapter->setBackground(currentSection,ui->backLine->text());
    chapter->setVocal(currentSection,ui->vocalLine->text());
}
