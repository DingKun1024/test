#ifndef CAMERA_H
#define CAMERA_H

#include "SI_sensor.h"
#include "SI_errors.h"


//char* wchar2char(const SI_WC* wchar);    //sdk中的函数返回宽字节，转换为char*用于显示
int selectDevice();
SI_H camera_init();



#endif // CAMERA_H
