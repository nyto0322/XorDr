#ifndef DIALOG_H
#define DIALOG_H


#include <QString>

class Dialog
{
    //friend Chapter;
    QString m_name;
    QString m_text;
    int m_size;

public:
    Dialog(QString,QString,int);
    QString getName();
    QString getText();
    int getFontDelta();

};

#endif // DIALOG_H
