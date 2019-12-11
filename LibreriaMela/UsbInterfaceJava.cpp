// Native methods implementation of
// C:/Users/haerazog/Documents/NetBeansProjects/UsbInterfaceJava/src/usbinterfacejava/UsbInterfaceJava.java

#include <jni.h>
#include <iostream>
#include <string>
#include <windows.h>
#include <stdlib.h>
#include "UsbInterfaceJava.h"
using namespace std;

#define ARDUINO_WAIT_TIME 2000

 HANDLE handler;
 int connected;
 COMSTAT status;
 DWORD errors;

jstring JNICALL Java_usbinterfacejava_UsbInterfaceJava_sayHello
  (JNIEnv * env, jobject object, jstring param1) {
    const char *caracter = env->GetStringUTFChars(param1, NULL);
    if (NULL == caracter) return NULL;
    
    cout << "In C++, the received string is: " << caracter << endl;
   env->ReleaseStringUTFChars(param1, caracter);
   
   string outCppStr;
   cout << "Enter a String: " << endl;
   cin >> outCppStr;
}

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
