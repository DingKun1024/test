#include "camera.h"
#include "camera_include/SI_errors.h"
#include <QDebug>
#include <QString>
#include <windows.h>



#define LICENSE_PATH L"C:/Users/Public/Documents/Specim/SpecSensor.lic"

int SI_IMPEXP_CONV onDataCallback(SI_U8* _pBuffer, SI_64 _nFrameSize, SI_64 _nFrameNumber, void* _pContext);

int selectDevice()
{
        int nError = siNoError;
        SI_64 nDeviceCount = 0;
        SI_WC szDeviceName[4096];
        int nIndex = -1;

        SI_GetInt(SI_SYSTEM, L"DeviceCount", &nDeviceCount);
        wprintf(L"Device count: %d\n", nDeviceCount);

        // Iterate through each devices to print their name
        for (int n = 0; n < nDeviceCount; n++)
        {
            SI_GetEnumStringByIndex(SI_SYSTEM, L"DeviceName", n, szDeviceName, 4096);
            wprintf(L"\t%d: %s\n", n, szDeviceName);
        }

        // Select a device
        wprintf(L"Select a device: ");
        scanf("%d", &nIndex);

        if ((nIndex >= nDeviceCount) || (nIndex == -1))
        {
            wprintf(L"Invalid index");
            return -1;
        }
    return 0;
}


SI_H camera_init()
{
    int error;
    int nError = siNoError;
    int nDeviceIndex = -1;
    SI_U8* pFrameBuffer = 0;
    SI_64 nBufferSize = 0;
    SI_64 nFrameSize = 0;
    SI_64 nFrameNumber = 0;
    SI_H g_hDevice = 0;

    // Loads SpecSensor and get the device count
    wprintf(L"Loading SpecSensor...\n");

    if((error=SI_Load(LICENSE_PATH))<0)
    {
        //qDebug()<<wchar2char(L"An error occurred:")<<wchar2char(SI_GetErrorString(error));
        wprintf(L"An error occurred: %s\n",SI_GetErrorString(error));
    }

    // Select a device
    nDeviceIndex = selectDevice();

    if (nDeviceIndex == -1)
    {
        return (SI_H)0;
    }

    // Opens the camera handle
    SI_Open(nDeviceIndex, &g_hDevice);
    SI_Command(g_hDevice, L"Initialize");

    // Sets frame rate and exposure
    SI_SetFloat(g_hDevice, L"Camera.FrameRate", 25.0);
    SI_SetFloat(g_hDevice, L"Camera.ExposureTime", 3.0);

    SI_RegisterDataCallback(g_hDevice, onDataCallback, 0);

    return g_hDevice;
}

int SI_IMPEXP_CONV onDataCallback(SI_U8* _pBuffer, SI_64 _nFrameSize, SI_64 _nFrameNumber, void* _pContext)
{

}

//char* wchar2char(const SI_WC* wchar)   //需包含头文件Windows.h
//{
//    char * m_char;
//    int len= WideCharToMultiByte( CP_ACP ,0,wchar ,wcslen(wchar), NULL,0, NULL ,NULL );
//    m_char= new char[len+1];
//    WideCharToMultiByte( CP_ACP ,0,wchar ,wcslen(wchar),m_char,len, NULL ,NULL );
//    m_char[len]= '\0';

//    qDebug()<<m_char;
//}
