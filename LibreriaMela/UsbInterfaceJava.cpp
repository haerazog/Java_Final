// Native methods implementation of
// C:/Users/haerazog/Documents/NetBeansProjects/UsbInterfaceJava/src/usbinterfacejava/UsbInterfaceJava.java

#include <jni.h>
#include <iostream>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include "UsbInterfaceJava.h"
using namespace std;

#define ARDUINO_WAIT_TIME 2000

 HANDLE handler;
 int connected;
 COMSTAT status;
 DWORD errors;

void JNICALL Java_usbinterfacejava_UsbInterfaceJava_SerialPort
  (JNIEnv * env, jobject object, jstring param1) {
    
    const char *portName = env->GetStringUTFChars(param1, NULL);
    
    
    
    connected = 0;

    handler = CreateFileA(static_cast<LPCSTR>(portName),
                                GENERIC_READ | GENERIC_WRITE,
                                0,
                                NULL,
                                OPEN_EXISTING,
                                FILE_ATTRIBUTE_NORMAL,
                                NULL);
    if (handler == INVALID_HANDLE_VALUE){
        if (GetLastError() == ERROR_FILE_NOT_FOUND){
            printf("ERROR: Handle was not attached. Reason: %s not available\n", portName);
        }
    else
        {
            printf("ERROR!!!");
        }
    }
    else {
        DCB dcbSerialParameters = {0};

        if (!GetCommState(handler, &dcbSerialParameters)) {
            printf("failed to get current serial parameters");
        }
        else {
            dcbSerialParameters.BaudRate = CBR_9600;
            dcbSerialParameters.ByteSize = 8;
            dcbSerialParameters.StopBits = ONESTOPBIT;
            dcbSerialParameters.Parity = NOPARITY;
            dcbSerialParameters.fDtrControl = DTR_CONTROL_ENABLE;

            if (!SetCommState(handler, &dcbSerialParameters))
            {
                printf("ALERT: could not set Serial port parameters\n");
            }
            else {
                connected = 1;
                PurgeComm(handler, PURGE_RXCLEAR | PURGE_TXCLEAR);
                Sleep(ARDUINO_WAIT_TIME);
            }
        }
    }
}

jint JNICALL Java_usbinterfacejava_UsbInterfaceJava_isconnected
  (JNIEnv * env, jobject object) {
    
    if (!ClearCommError(handler, &errors, &status))
		connected = 0;
        
    return connected;
}

jint JNICALL Java_usbinterfacejava_UsbInterfaceJava_readSerialPort
  (JNIEnv * env, jobject object, jstring param1, jint param2) {
    const char *buffer = env->GetStringUTFChars(param1, NULL);
    int buf_size = param2;
    
     DWORD bytesRead;
    unsigned int toRead = 0;

    ClearCommError(handler, &errors, &status);

    if (status.cbInQue > 0){
        if (status.cbInQue > buf_size){
            toRead = buf_size;
        }
        else toRead = status.cbInQue;
    }
    
    void *memadrs=&buffer;

    memset(memadrs, 0, buf_size);

    if (ReadFile(handler, memadrs, toRead, &bytesRead, NULL)) return bytesRead;

    return 0;
}

jint JNICALL Java_usbinterfacejava_UsbInterfaceJava_writeSerialPort
  (JNIEnv * env, jobject object, jstring param1, jint param2) {
    const char *buffer = env->GetStringUTFChars(param1, NULL);
    int buf_size = param2;
    DWORD bytesSend;

    if (!WriteFile(handler, (void*) buffer, buf_size, &bytesSend, 0)){
        ClearCommError(handler, &errors, &status);
        return 0;
    }
    else return 1;
}
