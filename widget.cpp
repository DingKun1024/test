#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>
#include <QPainter>
#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\imgproc\types_c.h>
//#include <opencv2\objdetect\objdetect_c.h>



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->label->move(100,30);
    qDebug()<<ui->label->x();
    ui->label->setStyleSheet("border:2px solid red;");
    ui->label_2->setStyleSheet("border:2px solid red;");
    ui->label_2->installEventFilter(this);   //label_2 安装事件过滤器

    A=new QThreadRead;
    B=new QThreadDeal;
    connect(ui->pushButton,&QPushButton::clicked,this,&Widget::start);
    connect(ui->pushButton_2,&QPushButton::clicked,this,
            [=]()
                {
                    A->m_stop=true;
                    B->m_stop=true;
                }
            );

   // connect(A,&QThreadRead::sendimage,this,&Widget::getimage,Qt::DirectConnection);
    connect(B,&QThreadDeal::sendResult,this,&Widget::getResult);
    connect(this,&Widget::destroyed,this,
            [=]()
                {
                    A->quit();
                    A->wait();
                    B->quit();
                    B->wait();
                }
            );

    //update();
    connect(A,&QThreadRead::sendimage,this,&Widget::getimage2,Qt::DirectConnection);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::start()
{
    A->m_stop=false;
    B->m_stop=false;
    B->start();
    A->start();
}


void Widget::getimage(cv::Mat mat)  //槽函数在子线程发送图像数据时调用，在gui上显示图片
{
//    cv::cvtColor(mat, mat, CV_BGR2RGB);

//    const uchar *pSrc = (const uchar*)mat.data;
//    // Create QImage with same dimensions as input Mat
//    QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
//    QImage img =image.rgbSwapped();

//    ui->label->setPixmap(QPixmap::fromImage(img));
//    // std::cout<<mat;
//    ui->label->show();
    qDebug()<<"-----main thread get image data-----";
}

void Widget::getimage2(cv::Mat image)
{
    Img=image;

    if(ui->label_2->width()>Img.cols)
    {
        n=Img.cols;
    }
    else
    {
        n=ui->label_2->width();
    }

    if(ui->label_2->height()>Img.rows)
    {
        m=Img.rows;
    }
    else
    {
        m=ui->label_2->height();
    }
    update();
}

void Widget::DrawImageByPixel()
{
    //cv::Mat mat=cv::imread("C:/Users/DELL/Desktop/a.png",1);
    static int a;
    QPainter paint(ui->label_2);
//    int m=Img.rows;
//    int n=Img.cols;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            QColor color(Img.at<cv::Vec3b>(i,j)[2],Img.at<cv::Vec3b>(i,j)[1],Img.at<cv::Vec3b>(i,j)[0]);
            paint.setPen(color);
            paint.drawPoint(j,i);
        }
    }
    qDebug()<<"窗口重绘"<<a++;
}

bool Widget::eventFilter(QObject *obj, QEvent *event)    //事件过滤器，label_2上绘图可在指定函数中绘图，不需要重写绘图函数，不指定则重写paintevent函数
{
    if(obj==ui->label_2 && event->type()==QEvent::Paint)
        DrawImageByPixel();

    return QWidget::eventFilter(obj,event);
}


void Widget::getResult(int)   //槽函数在子线程处理后拿到脚本文件返回结果时调用
{

}
