#include "Thread.h"
#include <QSemaphore>
#include <QMessageBox>
#include "camera.h"
#include <QVector>

PyObject* PFun=NULL;

int curbuf=1;
int bufNo=0;

int buffer1_cols,buffer1_rows,buffer2_cols,buffer2_rows;


unsigned char *buffer1;
unsigned char *buffer2;

QVector<unsigned char> vector1;
QVector<unsigned char> vector2;


QSemaphore emptybuff(2);
QSemaphore fullbuff;

QThreadRead::QThreadRead(QObject *parent) : QThread(parent)
{

}

QThreadDeal::QThreadDeal(QObject *parent) : QThread(parent)
{

}


void QThreadRead::run()
{
    qDebug()<<QThread::currentThreadId()<<"读取";
    m_stop=false;
    bufNo=0;

    int n=emptybuff.available();
    if(n<2)
    {
        emptybuff.release(2-n);
    }

    cv::VideoCapture  capture(0);
    cv::Mat image;

//    SI_H device=camera_init();
//    SI_Command(device, L"Acquisition.Stop");

    while (!m_stop)
    {
        emptybuff.acquire();
        if(curbuf==1)
        {
            //cv::Mat image=cv::imread("C:/Users/DELL/Desktop/a.png",1);
            //cv::imshow("123",image);

            capture>>image;

            buffer1_cols = image.cols*3;
            buffer1_rows = image.rows;
            qDebug()<<"buffer1_cols:"<<buffer1_cols<<",buffer1_rows:"<<buffer1_rows;

            for (int i = 0; i < buffer1_rows; i++)
            {
                for (int j = 0; j < buffer1_cols; j++)
                {
                    vector1 << (image.at<unsigned char>(i, j));
                }
            }
            qDebug()<<"-----buffer 1 get data-----";
            emit sendimage(image);
            fullbuff.release();
            msleep(100);
        }
        else
        {
            //cv::Mat image=cv::imread("C:/Users/DELL/Desktop/b.png",1);
            // cv::imshow("123",image);
            capture>>image;

            buffer2_cols = image.cols*3;
            buffer2_rows = image.rows;
            qDebug()<<"buffer2_cols:"<<buffer2_cols<<","<<"buffer2_rows:"<<buffer2_rows;

            for (int i = 0; i < buffer2_rows; i++)
            {
                for (int j = 0; j < buffer2_cols; j++)
                {
                    vector2 << (image.at<unsigned char>(i, j));
                }
            }
            qDebug()<<"-----buffer 2 get data-----";
            emit sendimage(image);
            fullbuff.release();
            msleep(100);
        }

        bufNo++;
        if(curbuf==1)
        {
            curbuf=2;
        }
        else
        {
            curbuf=1;
        }

        qDebug()<<"2.可用资源"<<emptybuff.available()<<","<<fullbuff.available();
    }
    qDebug()<<"线程结束1";
}



void QThreadDeal::run()
{
    qDebug()<<QThread::currentThreadId()<<"处理";
    qDebug()<<"1.可用资源"<<emptybuff.available()<<","<<fullbuff.available();
    int n=fullbuff.available();
    if(n>0)
    {
        fullbuff.acquire(n);
    }

    PFun=PythonMoudleInit();
    while (!m_stop)
    {
        fullbuff.acquire();
        int seq=bufNo;

        if(curbuf==1)
        {
            npy_intp Dims[2] = {buffer2_rows, buffer2_cols}; //给定维度信息
            buffer2=(unsigned char*)malloc(sizeof (unsigned char)*vector2.size());

            for(int i=0;i<vector2.size();i++)
            {
                buffer2[i]=vector2[i];
            }
            vector2.clear();
            emptybuff.release();

            PyObject *PyArray = PyArray_SimpleNewFromData(2, Dims, NPY_UBYTE, buffer2);
            //qDebug()<<PyArray;

            PyObject *ArgArray = PyTuple_New(1);
            PyTuple_SetItem(ArgArray, 0, PyArray);

            PyObject *pReturn=PyObject_CallObject(PFun,ArgArray);
            if(!pReturn)
                {
                    qDebug()<<"return failed";
                }
            int res = 0;
            PyArg_Parse(pReturn, "i", &res);//转换返回类型

            qDebug() << "res:" << res ;//输出结果
            emit sendResult(res);

            free(buffer2);
            qDebug()<<"-----buffer 2 has been freed-----";
        }
        else
        { 
             npy_intp Dims[2] = {buffer1_rows, buffer1_cols}; //给定维度信息
             buffer1=(unsigned char*)malloc(sizeof (unsigned char)*vector1.size());

             for(int i=0;i<vector1.size();i++)
             {
                 buffer1[i]=vector1[i];
             }
             vector1.clear();
             emptybuff.release();

             PyObject *PyArray = PyArray_SimpleNewFromData(2, Dims, NPY_UBYTE, buffer1);
             //qDebug()<<PyArray;

             PyObject *ArgArray = PyTuple_New(1);
             PyTuple_SetItem(ArgArray, 0, PyArray);

             PyObject *pReturn=PyObject_CallObject(PFun,ArgArray);

             if(!pReturn)
                 {
                     qDebug()<<"return failed";
                 }
             int res = 0;
             PyArg_Parse(pReturn, "i", &res);//转换返回类型
             qDebug() << "res:" << res ;//输出结果

             free(buffer1);
             vector1.clear();
             qDebug()<<"-----buffer 1 has been freed-----";
        }

        qDebug()<<"3.可用资源"<<emptybuff.available()<<","<<fullbuff.available();
        qDebug()<<seq;
    }
    qDebug()<<"线程结束2";
}

PyObject* PythonMoudleInit()
{
    qDebug()<<QThread::currentThreadId()<<"init python thread";
    Py_Initialize();
    if (!Py_IsInitialized())
    {
        qDebug() << "Python init failed";
    }

    import_array();
//    PyObject* sys = PyImport_ImportModule("sys");
//    PyRun_SimpleString("import sys"); // 执行 python 中的短语句
//    PyRun_SimpleString("sys.path.append('python文件所在路径')");

    PyObject *pModule(0);
    pModule = PyImport_ImportModule("hello1");//Python文件名
    if (!pModule)
    {
        qDebug() << "import moudle failed";
    }

    PyObject* pDict = PyModule_GetDict(pModule);
    if(!pDict)
    {
        qDebug()<<"import function failed";
    }

    PyObject *pFun=PyDict_GetItemString(pDict,"init");
    if(!pFun)
    {
        qDebug()<<"import init function failed";
    }
    return pFun;
}




