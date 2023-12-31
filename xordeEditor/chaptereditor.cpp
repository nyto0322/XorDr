#include "chaptereditor.h"
#include "ui_chaptereditor.h"
#include "singlesectioneditor.h"


ChapterEditor::ChapterEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChapterEditor)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

void ChapterEditor::reInit()
{
    ui->listWidget->clear();
    init(chapter);
}
void ChapterEditor::init(Chapter *c)
{
    chapter = c;
    ui->lineNext->setText(QString::number(c->getNextChapter()));
    ui->lineCurrent->setText(QString::number(c->getCurrentChapter()));
    QMap<int,Dialog*> dialog = c->getDialog();
    QMap<int,QString> vocal = c->getVocal();
    QMap<int,QString> bgm = c->getBgm();
    QMap<int,QVector<Figure>> perform = c->getPerform();
    QMap<int,QString> cg = c->getCg();
    QMap<int,QString> background = c->getBackground();
    QMap<int,QVector<Special>> special = c->getSpecial();
    QMap<int,QVector<Sound>> sound = c->getSound();
    QMap<int,QVector<ChoicePushButton*>> choice = c->getChoice();


    for(QMap<int,Dialog*>::const_iterator it = c->getDialog().constBegin();it != c->getDialog().constEnd();it++)
    {
        SingleSectionEditor* ssE = new SingleSectionEditor(ui->listWidget);
        ssE->init(it.key(),c);
        QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
        item->setSizeHint(ssE->size());
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item,ssE);
        connect(ui->win_save,&QPushButton::clicked,ssE,&SingleSectionEditor::save);
        connect(chapter,&Chapter::chapterSaveBegin,ssE,&SingleSectionEditor::save);

        connect(ssE,&SingleSectionEditor::reInit,this,&ChapterEditor::reInit);    //最好把ssE,item释放掉?以后再说
    }
    connect(ui->win_save,&QPushButton::clicked,[=](){
        chapter->setNextChapter(ui->lineNext->text().toInt());
        int pre = chapter->getCurrentChapter();
        chapter->setCurrentChapter(ui->lineCurrent->text().toInt());
        emit rename(pre,ui->lineCurrent->text());
    });
    connect(ui->btnRemove,&QPushButton::clicked,[=](){
        emit remove();
    });

}

ChapterEditor::~ChapterEditor()
{
    delete ui;
}
