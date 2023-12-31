#ifndef MAINBACKLIST_H
#define MAINBACKLIST_H

#include <QWidget>
#include <QMap>

namespace Ui {
class MainBackList;
}

class MainBackList : public QWidget
{
    Q_OBJECT

public:
    QMap<int,QString>m;
    explicit MainBackList(QWidget *parent = nullptr);
    void init(QMap<int, QString> &);
    ~MainBackList();

private:
    Ui::MainBackList *ui;
signals:
    void save(QMap<int, QString>);

};

#endif // MAINBACKLIST_H
