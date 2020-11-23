#ifndef AMASEARCH_H
#define AMASEARCH_H

#include <QWidget>
#include <QStyle>
#include <QDesktopWidget>

namespace Ui {
    class AMAsearch;
}

class AMAsearch : public QWidget
{
    Q_OBJECT

public:
    explicit AMAsearch(QWidget *parent = 0);
    void CenterWidgets();
//  inline void CenterWidgets(QWidget *widget, QWidget *host = 0);
    ~AMAsearch();

private:
    Ui::AMAsearch *ui;
};

#endif // AMASEARCH_H
