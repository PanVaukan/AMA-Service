#include "amasearch.h"
#include "ui_amasearch.h"

AMAsearch::AMAsearch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AMAsearch)
{
    ui->setupUi(this);
}

AMAsearch::~AMAsearch()
{
    delete ui;
}

void AMAsearch::CenterWidgets(){
//void AMAsearch::CenterWidgets(QWidget *widget, QWidget *host){

/*
    if (!host)
        host = widget->parentWidget();

    if (host) {
        QRect hostRect = host->geometry();
        widget->move(hostRect.center() - widget->rect().center());
    }
    else {

        QRect screenGeometry = QApplication::desktop()->screenGeometry();
        int x = (screenGeometry.width() - widget->width()) / 2;
        int y = (screenGeometry.height() - widget->height()) / 2;

        widget->move(x, y);
    }

*/

    QRect desktopRect = QApplication::desktop()->availableGeometry();
    QPoint center = desktopRect.center();

    this->move(center.x()-this->width()*0.5, center.y()-this->height()*0.5);

}
