#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H

#include <QPushButton>
#include <QMouseEvent>
#include <QEvent>




class SwitchButton : public QPushButton
{
    Q_OBJECT
public:
    QString normalImgPath;
    QString enterImgPath;
    QString pressImgPath;
    QString clickSoundPath;
    QPoint pos;
    QSize size;
    bool checked = false;         // 是否执行作用
    bool unlock = false;
    bool keep = false;
public:
    explicit SwitchButton(QString,QString,QString,QString,QPoint,QSize);
    SwitchButton(SwitchButton  const &);
    SwitchButton(QWidget *parent = nullptr);
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);
    void mousePressEvent(QMouseEvent*);
    // 鼠标释放事件 - 切换开关状态、发射toggled()信号
    void mouseReleaseEvent(QMouseEvent *event);

    void cancel();
    void init();


    QPoint getPos();
    bool isToggled() const;
    void setToggle(bool);
    QString loadError = "";
    void setKeep(bool);
    void light();


    void setUnlock(bool);


    void setNormal(QString);
    void setEnter(QString);
    void setPress(QString);
    void setSound(QString);
    void setPos(QPoint);
    void setSize(QSize);



signals:
    // 状态改变时，发射信号
    void toggled(bool checked);

};

#endif // SWITCHBUTTON_H
