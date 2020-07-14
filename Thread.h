#pragma once

#ifndef THREAD_H
#define THREAD_H




#include <QThread>

#include <Python.h>
#include <QtDebug>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <numpy/arrayobject.h>

PyObject* PythonMoudleInit();


class QThreadDeal: public QThread
{   Q_OBJECT

private:


protected:
    void run() override;

public:
    explicit QThreadDeal(QObject *parent = nullptr);
    //void stopThread();
    bool m_stop=false;
    //void getpythonfunction(PyObject* a);

signals:
    void sendResult(int);
    void a();
};


class QThreadRead: public QThread
{   Q_OBJECT

private:


protected:
    void run() override;

public:
   explicit QThreadRead(QObject *parent = nullptr);
    //void stopThread();
    bool m_stop=false;



signals:
    void sendimage(cv::Mat image);

};


//class QThreadSend: public QThread
//{   Q_OBJECT

//private:


//protected:
//    void run() override;

//public:
//   explicit QThreadSend(QObject *parent = nullptr);
//    //void stopThread();
//    bool m_stop=false;
//    void getResult(int res);


//};
#endif  //THREAD_H
