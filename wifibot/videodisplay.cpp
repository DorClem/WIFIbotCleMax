#include "videodisplay.h"
#include <QPainter>
#include <QRect>
//mettre le screen pour visualiser
VideoDisplay::VideoDisplay(QWidget *parent) :
    QWidget(parent)
{
}

void VideoDisplay::displayImage(QImage newImage){
    imageToDisplay= newImage;
    repaint();
}

void VideoDisplay::paintEvent(QPaintEvent *){
    QPainter painter(this);

    painter.setBrush(Qt::black);
    painter.drawRect(QRect(0,0,this->width(),this->height()));

    float ratio = qMin(((float)this->width())/imageToDisplay.width(),((float)this->height())/imageToDisplay.height());
    int drawWidth = imageToDisplay.width()*ratio;
    int drawHeight = imageToDisplay.height()*ratio;
    int drawX = (this->width()-drawWidth)/2;
    int drawY = (this->height()-drawHeight)/2;
    painter.drawImage(QRect(drawX,drawY,drawWidth,drawHeight),imageToDisplay);
}
