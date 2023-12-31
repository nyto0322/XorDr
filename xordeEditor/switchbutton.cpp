#include "switchbutton.h"

SwitchButton::SwitchButton(QString normal, QString enter,QString press, QString click,QPoint p, QSize s)
    :normalImgPath(normal)
    ,enterImgPath(enter)
    ,pressImgPath(press)
    ,clickSoundPath(click)
    ,pos(p)
    ,size(s)
{
    QPixmap pix;
    pix.load(this->normalImgPath);
    if(pix.isNull())
    {
        loadError = QString("加载失败")+=normalImgPath;
    }
    this->setFixedSize(size);
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(QPixmap(pix));
    this->setIconSize(size);
}

SwitchButton::SwitchButton(const SwitchButton & s)
    :normalImgPath(s.normalImgPath)
    ,enterImgPath(s.enterImgPath)
    ,pressImgPath(s.pressImgPath)
    ,clickSoundPath(s.clickSoundPath)
    ,pos(s.pos)
    ,size(s.size)
{
    QPixmap pix;
    pix.load(this->normalImgPath);
    if(pix.isNull())
    {
        loadError = QString("加载失败")+=normalImgPath;
    }
    this->setFixedSize(size);
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(QPixmap(pix));
    this->setIconSize(size);
}

SwitchButton::SwitchButton(QWidget *parent):QPushButton(parent)
{

}

void SwitchButton::enterEvent(QEvent *)
{
    if(checked)
    {
        this->setIcon(QPixmap(this->pressImgPath));
    }
    else
    {
        this->setIcon(QPixmap(this->enterImgPath));
    }
}

void SwitchButton::leaveEvent(QEvent *)
{
    if(unlock)
    {
        this->setIcon(QIcon());
        return;
    }
    if(checked)
    {
        return;
    }
    this->setIcon(QPixmap(this->normalImgPath));
}



void SwitchButton::mousePressEvent(QMouseEvent *e)
{
    if(checked)
    {
        QPushButton::mousePressEvent(e);
        return;
    }
    this->setIcon(QPixmap(this->pressImgPath));
    QPushButton::mousePressEvent(e);
}

//切换状态、发射信号
void SwitchButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(!keep)
    {
        checked = !checked;
        emit toggled(checked);
        if(checked)
        {
            this->setIcon(QPixmap(pressImgPath));
        }
        else
        {
            this->setIcon(QPixmap(normalImgPath));
        }
    }
    QPushButton::mousePressEvent(e);
}

void SwitchButton::cancel()  //置按钮为false并发送信号
{
    init();
    emit toggled(checked);
}

void SwitchButton::init()
{
    if(unlock)
    {
        this->setIcon(QIcon());
    }
    else
    {
        this->setIcon(QPixmap(this->normalImgPath));
    }
    checked = false;
    keep = false;
}

QPoint SwitchButton::getPos()
{
    return pos;
}

bool SwitchButton::isToggled() const
{
    return checked;
}

void SwitchButton::setToggle(bool c)
{
    checked = c;
}

void SwitchButton::setKeep(bool e)
{
    keep = e;
}

void SwitchButton::light()
{
    this->setIcon(QPixmap(this->pressImgPath));
}

void SwitchButton::setUnlock(bool u)
{
    unlock = u;
    if(u)
    {
        this->setIcon(QIcon());
    }
    else
    {
        if(checked)
        {
            this->setIcon(QPixmap(this->pressImgPath));
        }
        else
        {
            this->setIcon(QPixmap(this->normalImgPath));
        }
    }
}



void SwitchButton::setNormal(QString s)
{
    normalImgPath = s;
}

void SwitchButton::setEnter(QString s)
{
    enterImgPath = s;
}

void SwitchButton::setPress(QString p)
{
    pressImgPath = p;
}

void SwitchButton::setSound(QString s)
{
    clickSoundPath = s;
}

void SwitchButton::setPos(QPoint p)
{
    pos = p;
}

void SwitchButton::setSize(QSize s)
{
    size = s;
}

