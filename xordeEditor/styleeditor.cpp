#include "styleeditor.h"
#include "ui_styleeditor.h"
#include "buttoneditor.h"

void StyleEditor::save()
{
    data->getNameFrame()->setPix(ui->lineNamePic->text());
    data->getNameFrame()->setBackPoint(QPoint(ui->spinNameBackX->value(),ui->spinNameBackY->value()));
    data->getNameFrame()->setBackSize(QSize(ui->spinNameBackW->value(),ui->spinNameBackH->value()));
    data->getNameFrame()->setTextPoint(QPoint(ui->spinNameContentX->value(),ui->spinNameContentY->value()));
    data->getNameFrame()->setTextSize(QSize(ui->spinNameContentW->value(),ui->spinNameContentH->value()));
    //data->getNameFrame()->setFont(ui->lineNamePic->text());

    data->getTextFrame()->setPix(ui->lineTextPic->text());
    data->getTextFrame()->setBackPoint(QPoint(ui->spinTextBackX->value(),ui->spinTextBackY->value()));
    data->getTextFrame()->setBackSize(QSize(ui->spinTextBackW->value(),ui->spinTextBackH->value()));
    data->getTextFrame()->setTextPoint(QPoint(ui->spinTextContentX->value(),ui->spinTextContentY->value()));
    data->getTextFrame()->setTextSize(QSize(ui->spinTextContentW->value(),ui->spinTextContentH->value()));
    //data->getTextFrame()->setFont(ui->lineTextPic->text());

    data->getConfigSlider()[0]->imgL = ui->skipSpeedLine->text();
    data->getConfigSlider()[1]->imgL = ui->autoSpeedLine->text();
    data->getConfigSlider()[2]->imgL = ui->textshowSpeedLine->text();
    data->getConfigSlider()[3]->imgL = ui->textsizeLine->text();
    data->getConfigSlider()[4]->imgL = ui->mainvolumeLine->text();
    data->getConfigSlider()[5]->imgL = ui->mainbgmvolumeLine->text();
    data->getConfigSlider()[6]->imgL = ui->vocalvolumeLine->text();
    data->getConfigSlider()[7]->imgL = ui->bgmvolumeLine->text();
    data->getConfigSlider()[8]->imgL = ui->bgmwhenvocalvolumeLine->text();
    data->getConfigSlider()[9]->imgL = ui->soundvolumeLine->text();

    data->getConfigSlider()[0]->posL = QPoint(ui->skipSpeedPicX->value(),ui->skipSpeedPicY->value());
    data->getConfigSlider()[1]->posL = QPoint(ui->autoSpeedPicX->value(),ui->autoSpeedPicY->value());
    data->getConfigSlider()[2]->posL = QPoint(ui->textshowSpeedPicX->value(),ui->textshowSpeedPicY->value());
    data->getConfigSlider()[3]->posL = QPoint(ui->textsizePicX->value(),ui->textsizePicY->value());
    data->getConfigSlider()[4]->posL = QPoint(ui->mainvolumePicX->value(),ui->mainvolumePicY->value());
    data->getConfigSlider()[5]->posL = QPoint(ui->mainbgmvolumePicX->value(),ui->mainbgmvolumePicY->value());
    data->getConfigSlider()[6]->posL = QPoint(ui->vocalvolumePicX->value(),ui->vocalvolumePicY->value());
    data->getConfigSlider()[7]->posL = QPoint(ui->bgmvolumePicX->value(),ui->bgmvolumePicY->value());
    data->getConfigSlider()[8]->posL = QPoint(ui->bgmwhenvocalvolumePicX->value(),ui->bgmwhenvocalvolumePicY->value());
    data->getConfigSlider()[9]->posL = QPoint(ui->soundvolumePicX->value(),ui->soundvolumePicY->value());

    data->getConfigSlider()[0]->sizeL = QSize(ui->skipSpeedPicW->value(),ui->skipSpeedPicH->value());
    data->getConfigSlider()[1]->sizeL = QSize(ui->autoSpeedPicW->value(),ui->autoSpeedPicH->value());
    data->getConfigSlider()[2]->sizeL = QSize(ui->textshowSpeedPicW->value(),ui->textshowSpeedPicH->value());
    data->getConfigSlider()[3]->sizeL = QSize(ui->textsizePicW->value(),ui->textsizePicH->value());
    data->getConfigSlider()[4]->sizeL = QSize(ui->mainvolumePicW->value(),ui->mainvolumePicH->value());
    data->getConfigSlider()[5]->sizeL = QSize(ui->mainbgmvolumePicW->value(),ui->mainbgmvolumePicH->value());
    data->getConfigSlider()[6]->sizeL = QSize(ui->vocalvolumePicW->value(),ui->vocalvolumePicH->value());
    data->getConfigSlider()[7]->sizeL = QSize(ui->bgmvolumePicW->value(),ui->bgmvolumePicH->value());
    data->getConfigSlider()[8]->sizeL = QSize(ui->bgmwhenvocalvolumePicW->value(),ui->bgmwhenvocalvolumePicH->value());
    data->getConfigSlider()[9]->sizeL = QSize(ui->soundvolumePicW->value(),ui->soundvolumePicH->value());

    data->getConfigSlider()[0]->posL = QPoint(ui->skipSpeedSliderX->value(),ui->skipSpeedSliderY->value());
    data->getConfigSlider()[1]->posS = QPoint(ui->autoSpeedSliderX->value(),ui->autoSpeedSliderY->value());
    data->getConfigSlider()[2]->posS = QPoint(ui->textshowSpeedSliderX->value(),ui->textshowSpeedSliderY->value());
    data->getConfigSlider()[3]->posS = QPoint(ui->textsizeSliderX->value(),ui->textsizeSliderY->value());
    data->getConfigSlider()[4]->posS = QPoint(ui->mainvolumeSliderX->value(),ui->mainvolumeSliderY->value());
    data->getConfigSlider()[5]->posS = QPoint(ui->mainbgmvolumeSliderX->value(),ui->mainbgmvolumeSliderY->value());
    data->getConfigSlider()[6]->posS = QPoint(ui->vocalvolumeSliderX->value(),ui->vocalvolumeSliderY->value());
    data->getConfigSlider()[7]->posS = QPoint(ui->bgmvolumeSliderX->value(),ui->bgmvolumeSliderY->value());
    data->getConfigSlider()[8]->posS = QPoint(ui->bgmwhenvocalvolumeSliderX->value(),ui->bgmwhenvocalvolumeSliderY->value());
    data->getConfigSlider()[9]->posS = QPoint(ui->soundvolumeSliderX->value(),ui->soundvolumeSliderY->value());

    data->getConfigSlider()[0]->sizeS = QSize(ui->skipSpeedSliderW->value(),ui->skipSpeedSliderH->value());
    data->getConfigSlider()[1]->sizeS = QSize(ui->autoSpeedSliderW->value(),ui->autoSpeedSliderH->value());
    data->getConfigSlider()[2]->sizeS = QSize(ui->textshowSpeedSliderW->value(),ui->textshowSpeedSliderH->value());
    data->getConfigSlider()[3]->sizeS = QSize(ui->textsizeSliderW->value(),ui->textsizeSliderH->value());
    data->getConfigSlider()[4]->sizeS = QSize(ui->mainvolumeSliderW->value(),ui->mainvolumeSliderH->value());
    data->getConfigSlider()[5]->sizeS = QSize(ui->mainbgmvolumeSliderW->value(),ui->mainbgmvolumeSliderH->value());
    data->getConfigSlider()[6]->sizeS = QSize(ui->vocalvolumeSliderW->value(),ui->vocalvolumeSliderH->value());
    data->getConfigSlider()[7]->sizeS = QSize(ui->bgmvolumeSliderW->value(),ui->bgmvolumeSliderH->value());
    data->getConfigSlider()[8]->sizeS = QSize(ui->bgmwhenvocalvolumeSliderW->value(),ui->bgmwhenvocalvolumeSliderH->value());
    data->getConfigSlider()[9]->sizeS = QSize(ui->soundvolumeSliderW->value(),ui->soundvolumeSliderH->value());

    data->setSliderStyleSheet(ui->sliderStyleSheetLine->text());
    data->setHistoryStyleSheet(ui->historyStyleSheetLine->text());
    data->setGallerycgStyleSheet(ui->galCgStyleSheetLine->text());
    data->setGallerymediaStyleSheet(ui->galMediaStyleSheetLine->text());

}

StyleEditor::StyleEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StyleEditor)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    connect(ui->btnNamePic,&QPushButton::clicked,[=](){
        QString str=QFileDialog::getOpenFileName(this,"Open Image", "", "Image Files (*.png)");
        if(str!="")
        {
            ui->lineNamePic->setText(str.mid(str.lastIndexOf('/')+1));
        }

    });
    connect(ui->btnTextPic,&QPushButton::clicked,[=](){
        QString str=QFileDialog::getOpenFileName(this,"Open Image", "", "Image Files (*.png)");
        if(str!="")
        {
            ui->lineTextPic->setText(str.mid(str.lastIndexOf('/')+1));
        }

    });
    connect(ui->skipSpeedLineBtn,&QPushButton::clicked,[=](){
        QString str=QFileDialog::getOpenFileName(this,"Open Image", "", "Image Files (*.png)");
        if(str!="")
        {
            ui->skipSpeedLine->setText(str.mid(str.lastIndexOf('/')+1));
        }

    });
    connect(ui->autoSpeedLineBtn,&QPushButton::clicked,[=](){
        QString str=QFileDialog::getOpenFileName(this,"Open Image", "", "Image Files (*.png)");
        if(str!="")
        {
            ui->autoSpeedLine->setText(str.mid(str.lastIndexOf('/')+1));
        }

    });
    connect(ui->textshowSpeedLineBtn,&QPushButton::clicked,[=](){
        QString str=QFileDialog::getOpenFileName(this,"Open Image", "", "Image Files (*.png)");
        if(str!="")
        {
            ui->textshowSpeedLine->setText(str.mid(str.lastIndexOf('/')+1));
        }

    });
    connect(ui->textsizeLineBtn,&QPushButton::clicked,[=](){
        QString str=QFileDialog::getOpenFileName(this,"Open Image", "", "Image Files (*.png)");
        if(str!="")
        {
            ui->textsizeLine->setText(str.mid(str.lastIndexOf('/')+1));
        }

    });
    connect(ui->mainvolumeLineBtn,&QPushButton::clicked,[=](){
        QString str=QFileDialog::getOpenFileName(this,"Open Image", "", "Image Files (*.png)");
        if(str!="")
        {
            ui->mainvolumeLine->setText(str.mid(str.lastIndexOf('/')+1));
        }

    });
    connect(ui->mainbgmvolumeLineBtn,&QPushButton::clicked,[=](){
        QString str=QFileDialog::getOpenFileName(this,"Open Image", "", "Image Files (*.png)");
        if(str!="")
        {
            ui->mainbgmvolumeLine->setText(str.mid(str.lastIndexOf('/')+1));
        }

    });
    connect(ui->vocalvolumeLineBtn,&QPushButton::clicked,[=](){
        QString str=QFileDialog::getOpenFileName(this,"Open Image", "", "Image Files (*.png)");
        if(str!="")
        {
            ui->vocalvolumeLine->setText(str.mid(str.lastIndexOf('/')+1));
        }

    });
    connect(ui->bgmvolumeLineBtn,&QPushButton::clicked,[=](){
        QString str=QFileDialog::getOpenFileName(this,"Open Image", "", "Image Files (*.png)");
        if(str!="")
        {
            ui->bgmvolumeLine->setText(str.mid(str.lastIndexOf('/')+1));
        }

    });
    connect(ui->bgmwhenvocalvolumeLineBtn,&QPushButton::clicked,[=](){
        QString str=QFileDialog::getOpenFileName(this,"Open Image", "", "Image Files (*.png)");
        if(str!="")
        {
            ui->bgmwhenvocalvolumeLine->setText(str.mid(str.lastIndexOf('/')+1));
        }

    });
    connect(ui->soundvolumeLineBtn,&QPushButton::clicked,[=](){
        QString str=QFileDialog::getOpenFileName(this,"Open Image", "", "Image Files (*.png)");
        if(str!="")
        {
            ui->soundvolumeLine->setText(str.mid(str.lastIndexOf('/')+1));
        }

    });



}

void StyleEditor::init(Data *d)
{
    data = d;

    ui->spinNameBackX->setValue(d->getNameFrame()->getBackPoint().x());
    ui->spinNameBackY->setValue(d->getNameFrame()->getBackPoint().y());
    ui->spinNameBackW->setValue(d->getNameFrame()->getBackSize().width());
    ui->spinNameBackH->setValue(d->getNameFrame()->getBackSize().height());

    ui->spinTextBackX->setValue(d->getTextFrame()->getBackPoint().x());
    ui->spinTextBackY->setValue(d->getTextFrame()->getBackPoint().y());
    ui->spinTextBackW->setValue(d->getTextFrame()->getBackSize().width());
    ui->spinTextBackH->setValue(d->getTextFrame()->getBackSize().height());

    ui->spinNameContentX->setValue(d->getNameFrame()->getTextPoint().x());
    ui->spinNameContentY->setValue(d->getNameFrame()->getTextPoint().y());
    ui->spinNameContentW->setValue(d->getNameFrame()->getTextSize().width());
    ui->spinNameContentH->setValue(d->getNameFrame()->getTextSize().height());

    ui->spinTextContentX->setValue(d->getTextFrame()->getTextPoint().x());
    ui->spinTextContentY->setValue(d->getTextFrame()->getTextPoint().y());
    ui->spinTextContentW->setValue(d->getTextFrame()->getTextSize().width());
    ui->spinTextContentH->setValue(d->getTextFrame()->getTextSize().height());

    ui->lineNamePic->setText(d->getNameFrame()->getPix());
    ui->lineTextPic->setText(d->getTextFrame()->getPix());


    //config界面
    ui->skipSpeedLine->setText(d->getConfigSlider()[0]->imgL);
    ui->skipSpeedPicX->setValue(d->getConfigSlider()[0]->posL.x());
    ui->skipSpeedPicY->setValue(d->getConfigSlider()[0]->posL.y());
    ui->skipSpeedPicW->setValue(d->getConfigSlider()[0]->sizeL.width());
    ui->skipSpeedPicH->setValue(d->getConfigSlider()[0]->sizeL.height());
    ui->skipSpeedSliderX->setValue(d->getConfigSlider()[0]->posS.x());
    ui->skipSpeedSliderY->setValue(d->getConfigSlider()[0]->posS.y());
    ui->skipSpeedSliderW->setValue(d->getConfigSlider()[0]->sizeS.width());
    ui->skipSpeedSliderH->setValue(d->getConfigSlider()[0]->sizeS.height());

    ui->autoSpeedLine->setText(d->getConfigSlider()[1]->imgL);
    ui->autoSpeedPicX->setValue(d->getConfigSlider()[1]->posL.x());
    ui->autoSpeedPicY->setValue(d->getConfigSlider()[1]->posL.y());
    ui->autoSpeedPicW->setValue(d->getConfigSlider()[1]->sizeL.width());
    ui->autoSpeedPicH->setValue(d->getConfigSlider()[1]->sizeL.height());
    ui->autoSpeedSliderX->setValue(d->getConfigSlider()[1]->posS.x());
    ui->autoSpeedSliderY->setValue(d->getConfigSlider()[1]->posS.y());
    ui->autoSpeedSliderW->setValue(d->getConfigSlider()[1]->sizeS.width());
    ui->autoSpeedSliderH->setValue(d->getConfigSlider()[1]->sizeS.height());

    ui->textshowSpeedLine->setText(d->getConfigSlider()[2]->imgL);
    ui->textshowSpeedPicX->setValue(d->getConfigSlider()[2]->posL.x());
    ui->textshowSpeedPicY->setValue(d->getConfigSlider()[2]->posL.y());
    ui->textshowSpeedPicW->setValue(d->getConfigSlider()[2]->sizeL.width());
    ui->textshowSpeedPicH->setValue(d->getConfigSlider()[2]->sizeL.height());
    ui->textshowSpeedSliderX->setValue(d->getConfigSlider()[2]->posS.x());
    ui->textshowSpeedSliderY->setValue(d->getConfigSlider()[2]->posS.y());
    ui->textshowSpeedSliderW->setValue(d->getConfigSlider()[2]->sizeS.width());
    ui->textshowSpeedSliderH->setValue(d->getConfigSlider()[2]->sizeS.height());

    ui->textsizeLine ->setText(d->getConfigSlider()[3]->imgL);
    ui->textsizePicX->setValue(d->getConfigSlider()[3]->posL.x());
    ui->textsizePicY->setValue(d->getConfigSlider()[3]->posL.y());
    ui->textsizePicW->setValue(d->getConfigSlider()[3]->sizeL.width());
    ui->textsizePicH->setValue(d->getConfigSlider()[3]->sizeL.height());
    ui->textsizeSliderX->setValue(d->getConfigSlider()[3]->posS.x());
    ui->textsizeSliderY->setValue(d->getConfigSlider()[3]->posS.y());
    ui->textsizeSliderW->setValue(d->getConfigSlider()[3]->sizeS.width());
    ui->textsizeSliderH->setValue(d->getConfigSlider()[3]->sizeS.height());

    ui->mainvolumeLine->setText(d->getConfigSlider()[4]->imgL);
    ui->mainvolumePicX->setValue(d->getConfigSlider()[4]->posL.x());
    ui->mainvolumePicY->setValue(d->getConfigSlider()[4]->posL.y());
    ui->mainvolumePicW->setValue(d->getConfigSlider()[4]->sizeL.width());
    ui->mainvolumePicH->setValue(d->getConfigSlider()[4]->sizeL.height());
    ui->mainvolumeSliderX->setValue(d->getConfigSlider()[4]->posS.x());
    ui->mainvolumeSliderY->setValue(d->getConfigSlider()[4]->posS.y());
    ui->mainvolumeSliderW->setValue(d->getConfigSlider()[4]->sizeS.width());
    ui->mainvolumeSliderH->setValue(d->getConfigSlider()[4]->sizeS.height());

    ui->mainbgmvolumeLine->setText(d->getConfigSlider()[5]->imgL);
    ui->mainbgmvolumePicX->setValue(d->getConfigSlider()[5]->posL.x());
    ui->mainbgmvolumePicY->setValue(d->getConfigSlider()[5]->posL.y());
    ui->mainbgmvolumePicW->setValue(d->getConfigSlider()[5]->sizeL.width());
    ui->mainbgmvolumePicH->setValue(d->getConfigSlider()[5]->sizeL.height());
    ui->mainbgmvolumeSliderX->setValue(d->getConfigSlider()[5]->posS.x());
    ui->mainbgmvolumeSliderY->setValue(d->getConfigSlider()[5]->posS.y());
    ui->mainbgmvolumeSliderW->setValue(d->getConfigSlider()[5]->sizeS.width());
    ui->mainbgmvolumeSliderH->setValue(d->getConfigSlider()[5]->sizeS.height());

    ui->vocalvolumeLine->setText(d->getConfigSlider()[6]->imgL);
    ui->vocalvolumePicX->setValue(d->getConfigSlider()[6]->posL.x());
    ui->vocalvolumePicY->setValue(d->getConfigSlider()[6]->posL.y());
    ui->vocalvolumePicW->setValue(d->getConfigSlider()[6]->sizeL.width());
    ui->vocalvolumePicH->setValue(d->getConfigSlider()[6]->sizeL.height());
    ui->vocalvolumeSliderX->setValue(d->getConfigSlider()[6]->posS.x());
    ui->vocalvolumeSliderY->setValue(d->getConfigSlider()[6]->posS.y());
    ui->vocalvolumeSliderW->setValue(d->getConfigSlider()[6]->sizeS.width());
    ui->vocalvolumeSliderH->setValue(d->getConfigSlider()[6]->sizeS.height());

    ui->bgmvolumeLine->setText(d->getConfigSlider()[7]->imgL);
    ui->bgmvolumePicX->setValue(d->getConfigSlider()[7]->posL.x());
    ui->bgmvolumePicY->setValue(d->getConfigSlider()[7]->posL.y());
    ui->bgmvolumePicW->setValue(d->getConfigSlider()[7]->sizeL.width());
    ui->bgmvolumePicH->setValue(d->getConfigSlider()[7]->sizeL.height());
    ui->bgmvolumeSliderX->setValue(d->getConfigSlider()[7]->posS.x());
    ui->bgmvolumeSliderY->setValue(d->getConfigSlider()[7]->posS.y());
    ui->bgmvolumeSliderW->setValue(d->getConfigSlider()[7]->sizeS.width());
    ui->bgmvolumeSliderH->setValue(d->getConfigSlider()[7]->sizeS.height());

    ui->bgmwhenvocalvolumeLine->setText(d->getConfigSlider()[8]->imgL);
    ui->bgmwhenvocalvolumePicX->setValue(d->getConfigSlider()[8]->posL.x());
    ui->bgmwhenvocalvolumePicY->setValue(d->getConfigSlider()[8]->posL.y());
    ui->bgmwhenvocalvolumePicW->setValue(d->getConfigSlider()[8]->sizeL.width());
    ui->bgmwhenvocalvolumePicH->setValue(d->getConfigSlider()[8]->sizeL.height());
    ui->bgmwhenvocalvolumeSliderX->setValue(d->getConfigSlider()[8]->posS.x());
    ui->bgmwhenvocalvolumeSliderY->setValue(d->getConfigSlider()[8]->posS.y());
    ui->bgmwhenvocalvolumeSliderW->setValue(d->getConfigSlider()[8]->sizeS.width());
    ui->bgmwhenvocalvolumeSliderH->setValue(d->getConfigSlider()[8]->sizeS.height());

    ui->soundvolumeLine->setText(d->getConfigSlider()[9]->imgL);
    ui->soundvolumePicX->setValue(d->getConfigSlider()[9]->posL.x());
    ui->soundvolumePicY->setValue(d->getConfigSlider()[9]->posL.y());
    ui->soundvolumePicW->setValue(d->getConfigSlider()[9]->sizeL.width());
    ui->soundvolumePicH->setValue(d->getConfigSlider()[9]->sizeL.height());
    ui->soundvolumeSliderX->setValue(d->getConfigSlider()[9]->posS.x());
    ui->soundvolumeSliderY->setValue(d->getConfigSlider()[9]->posS.y());
    ui->soundvolumeSliderW->setValue(d->getConfigSlider()[9]->sizeS.width());
    ui->soundvolumeSliderH->setValue(d->getConfigSlider()[9]->sizeS.height());

    ui->sliderStyleSheetLine->setText(d->getSliderStyleSheet());
    ui->historyStyleSheetLine->setText(d->getHistoryStyleSheet());
    ui->galCgStyleSheetLine->setText(d->getGallerycgStyleSheet());
    ui->galMediaStyleSheetLine->setText(d->getGallerymediaStyleSheet());



    //按钮
    connect(ui->newMainBtn,&QPushButton::clicked,[=](){
        ButtonEditor* btnEdt = new ButtonEditor(ui->newMainBtn->text(),d->getBeginBtn()[0]);
        btnEdt->show();
        btnEdt->setAttribute(Qt::WA_DeleteOnClose);
    });
    connect(ui->continueMainBtn,&QPushButton::clicked,[=](){
        ButtonEditor* btnEdt = new ButtonEditor(ui->continueMainBtn->text(),d->getBeginBtn()[1]);
        btnEdt->show();
        btnEdt->setAttribute(Qt::WA_DeleteOnClose);
    });
    connect(ui->loadMainBtn,&QPushButton::clicked,[=](){
        ButtonEditor* btnEdt = new ButtonEditor(ui->loadMainBtn->text(),d->getBeginBtn()[2]);
        btnEdt->show();
        btnEdt->setAttribute(Qt::WA_DeleteOnClose);
    });
    connect(ui->galMainBtn,&QPushButton::clicked,[=](){
        ButtonEditor* btnEdt = new ButtonEditor(ui->galMainBtn->text(),d->getBeginBtn()[3]);
        btnEdt->show();
        btnEdt->setAttribute(Qt::WA_DeleteOnClose);
    });
    connect(ui->configMainBtn,&QPushButton::clicked,[=](){
        ButtonEditor* btnEdt = new ButtonEditor(ui->configMainBtn->text(),d->getBeginBtn()[4]);
        btnEdt->show();
        btnEdt->setAttribute(Qt::WA_DeleteOnClose);
    });
    connect(ui->exitMainBtn,&QPushButton::clicked,[=](){
        ButtonEditor* btnEdt = new ButtonEditor(ui->exitMainBtn->text(),d->getBeginBtn()[5]);
        btnEdt->show();
        btnEdt->setAttribute(Qt::WA_DeleteOnClose);
    });
    connect(ui->lockBtn,&QPushButton::clicked,[=](){
        ButtonEditor* btnEdt = new ButtonEditor(ui->lockBtn->text(),d->getSceneSwitch()[0]);
        btnEdt->show();
        btnEdt->setAttribute(Qt::WA_DeleteOnClose);
    });
    connect(ui->autoBtn,&QPushButton::clicked,[=](){
        ButtonEditor* btnEdt = new ButtonEditor(ui->autoBtn->text(),d->getSceneSwitch()[1]);
        btnEdt->show();
        btnEdt->setAttribute(Qt::WA_DeleteOnClose);
    });
    connect(ui->skipBtn,&QPushButton::clicked,[=](){
        ButtonEditor* btnEdt = new ButtonEditor(ui->skipBtn->text(),d->getSceneSwitch()[2]);
        btnEdt->show();
        btnEdt->setAttribute(Qt::WA_DeleteOnClose);
    });
    connect(ui->qsaveBtn,&QPushButton::clicked,[=](){
        ButtonEditor* btnEdt = new ButtonEditor(ui->qsaveBtn->text(),d->getSceneBtn()[0]);
        btnEdt->show();
        btnEdt->setAttribute(Qt::WA_DeleteOnClose);
    });
    connect(ui->qloadBtn,&QPushButton::clicked,[=](){
        ButtonEditor* btnEdt = new ButtonEditor(ui->qloadBtn->text(),d->getSceneBtn()[1]);
        btnEdt->show();
        btnEdt->setAttribute(Qt::WA_DeleteOnClose);
    });
    connect(ui->saveBtn,&QPushButton::clicked,[=](){
        ButtonEditor* btnEdt = new ButtonEditor(ui->saveBtn->text(),d->getSceneBtn()[2]);
        btnEdt->show();
        btnEdt->setAttribute(Qt::WA_DeleteOnClose);
    });
    connect(ui->loadBtn,&QPushButton::clicked,[=](){
        ButtonEditor* btnEdt = new ButtonEditor(ui->loadBtn->text(),d->getSceneBtn()[3]);
        btnEdt->show();
        btnEdt->setAttribute(Qt::WA_DeleteOnClose);
    });
    connect(ui->preBtn,&QPushButton::clicked,[=](){
        ButtonEditor* btnEdt = new ButtonEditor(ui->preBtn->text(),d->getSceneBtn()[4]);
        btnEdt->show();
        btnEdt->setAttribute(Qt::WA_DeleteOnClose);
    });
    connect(ui->historyBtn,&QPushButton::clicked,[=](){
        ButtonEditor* btnEdt = new ButtonEditor(ui->historyBtn->text(),d->getSceneBtn()[5]);
        btnEdt->show();
        btnEdt->setAttribute(Qt::WA_DeleteOnClose);
    });
    connect(ui->nextBtn,&QPushButton::clicked,[=](){
        ButtonEditor* btnEdt = new ButtonEditor(ui->nextBtn->text(),d->getSceneBtn()[6]);
        btnEdt->show();
        btnEdt->setAttribute(Qt::WA_DeleteOnClose);
    });
    connect(ui->hideBtn,&QPushButton::clicked,[=](){
        ButtonEditor* btnEdt = new ButtonEditor(ui->hideBtn->text(),d->getSceneBtn()[7]);
        btnEdt->show();
        btnEdt->setAttribute(Qt::WA_DeleteOnClose);
    });
    connect(ui->configBtn,&QPushButton::clicked,[=](){
        ButtonEditor* btnEdt = new ButtonEditor(ui->configBtn->text(),d->getSceneBtn()[8]);
        btnEdt->show();
        btnEdt->setAttribute(Qt::WA_DeleteOnClose);
    });
    connect(ui->mainBtn,&QPushButton::clicked,[=](){
        ButtonEditor* btnEdt = new ButtonEditor(ui->mainBtn->text(),d->getSceneBtn()[9]);
        btnEdt->show();
        btnEdt->setAttribute(Qt::WA_DeleteOnClose);
    });
    connect(ui->toMainBtn,&QPushButton::clicked,[=](){
        ButtonEditor* btnEdt = new ButtonEditor(ui->toMainBtn->text(),d->getOtherPlayerBtn()[0]);
        btnEdt->show();
        btnEdt->setAttribute(Qt::WA_DeleteOnClose);
    });
    connect(ui->toSceneBtn,&QPushButton::clicked,[=](){
        ButtonEditor* btnEdt = new ButtonEditor(ui->toSceneBtn->text(),d->getOtherPlayerBtn()[1]);
        btnEdt->show();
        btnEdt->setAttribute(Qt::WA_DeleteOnClose);
    });
    connect(ui->toSaveBtn,&QPushButton::clicked,[=](){
        ButtonEditor* btnEdt = new ButtonEditor(ui->toSaveBtn->text(),d->getOtherPlayerBtn()[2]);
        btnEdt->show();
        btnEdt->setAttribute(Qt::WA_DeleteOnClose);
    });
    connect(ui->toLoadBtn,&QPushButton::clicked,[=](){
        ButtonEditor* btnEdt = new ButtonEditor(ui->toLoadBtn->text(),d->getOtherPlayerBtn()[3]);
        btnEdt->show();
        btnEdt->setAttribute(Qt::WA_DeleteOnClose);
    });

    for(int i = 1;i<=10;i++)
    {
        QPushButton* p = findChild<QPushButton*>("SLBtn"+QString::number(i));
        connect(p,&QPushButton::clicked,[=](){
            ButtonEditor* btnEdt = new ButtonEditor(p->text(),d->getDataPlayerBtn()[i-1]);
            btnEdt->show();
            btnEdt->setAttribute(Qt::WA_DeleteOnClose);
        });
        p = findChild<QPushButton*>("SLBtnIn"+QString::number(i));
        connect(p,&QPushButton::clicked,[=](){
            ButtonEditor* btnEdt = new ButtonEditor(p->text(),d->getDataPlayerIndexBtn()[i-1]);
            btnEdt->show();
            btnEdt->setAttribute(Qt::WA_DeleteOnClose);
        });
    }

    connect(ui->galMediapreBtn,&QPushButton::clicked,[=](){
        ButtonEditor* btnEdt = new ButtonEditor(ui->exitMainBtn->text(),d->getGallerymediaBtn()[0]);
        btnEdt->show();
        btnEdt->setAttribute(Qt::WA_DeleteOnClose);
    });
    connect(ui->galMediaNextBtn,&QPushButton::clicked,[=](){
        ButtonEditor* btnEdt = new ButtonEditor(ui->exitMainBtn->text(),d->getGallerymediaBtn()[1]);
        btnEdt->show();
        btnEdt->setAttribute(Qt::WA_DeleteOnClose);
    });
    connect(ui->galMediaPauseBtn,&QPushButton::clicked,[=](){
        ButtonEditor* btnEdt = new ButtonEditor(ui->exitMainBtn->text(),d->getGallerymediaSwitch()[0]);
        btnEdt->show();
        btnEdt->setAttribute(Qt::WA_DeleteOnClose);
    });
    connect(ui->galMediaModeBtn,&QPushButton::clicked,[=](){
        ButtonEditor* btnEdt = new ButtonEditor(ui->exitMainBtn->text(),d->getGallerymediaSwitch()[1]);
        btnEdt->show();
        btnEdt->setAttribute(Qt::WA_DeleteOnClose);
    });

    connect(ui->btnNameFont,&QPushButton::clicked,[=](){
        bool ok;
        QFontDialog::getFont(&ok);
        QFont font=QFontDialog::getFont(&ok,QFont("黑体",15));
        data->getNameFrame()->setFont(font);
    });
    connect(ui->btnTextFont,&QPushButton::clicked,[=](){
        bool ok;
        QFontDialog::getFont(&ok);
        QFont font=QFontDialog::getFont(&ok,QFont("黑体",15));
        data->getTextFrame()->setFont(font);
    });





    connect(data,&Data::dataSaveBegin,this,&StyleEditor::save);
    connect(ui->win_save,&QPushButton::clicked,this,&StyleEditor::save);

}

StyleEditor::~StyleEditor()
{
    delete ui;
}
