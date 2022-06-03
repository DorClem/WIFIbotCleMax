#ifndef VIDEODISPLAY_H
#define VIDEODISPLAY_H

#include <QWidget>
class QImage;


class VideoDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit VideoDisplay(QWidget *parent = 0);

signals:

public slots:
    void displayImage(QImage newImage);

protected:
    void paintEvent(QPaintEvent *);
private:
    QImage imageToDisplay;
};

#endif // VIDEODISPLAY_H
