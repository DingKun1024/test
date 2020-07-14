#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "Thread.h"
#include <QPaintEvent>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void start();
    void getimage(cv::Mat image);
    void getResult(int);
    void getimage2(cv::Mat image);
private:
    Ui::Widget *ui;
    QThreadRead* A;
    QThreadDeal* B;
    cv::Mat Img;
    int m,n;
    void DrawImageByPixel();
    bool eventFilter(QObject *obj, QEvent *event); 
};
#endif // WIDGET_H
