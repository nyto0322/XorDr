#ifndef TEXTLABEL_H
#define TEXTLABEL_H

#include <QLabel>
#include <QTimer>

class TextLabel : public QLabel
{
    Q_OBJECT
    QTimer m_time;
    QString m_text;
    int m_net;
public:
    explicit TextLabel(QWidget *parent = nullptr);
    void setGradualText(QString);
    void setNormalText(QString);
    void changed();
    void pressToNext();


signals:
    void isOver();

};

#endif // TEXTLABEL_H
