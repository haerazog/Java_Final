// Native methods implementation of
// C:/Users/haerazog/Documents/NetBeansProjects/UsbInterfaceJava/src/usbinterfacejava/UsbInterfaceJava.java
#include <jni.h>
#include <iostream>
#include <string>
#include "UsbInterfaceJava.h"

using namespace std;

jdouble JNICALL Java_usbinterfacejava_UsbInterfaceJava_Suma
  (JNIEnv * env, jobject object, jint param1, jint param2) {
    jint result;
    result = param1 + param2 ;
    return result;
}

jdouble JNICALL Java_usbinterfacejava_UsbInterfaceJava_Resta
  (JNIEnv * env, jobject object, jint param1, jint param2) {
    jint result;
    result = param1 - param2 ;
    return result;
}

jstring JNICALL Java_usbinterfacejava_UsbInterfaceJava_sayHello
  (JNIEnv * env, jobject object, jstring param1) {
    const char *caracter = env->GetStringUTFChars(param1,NULL);
    if (NULL == caracter) return NULL;
    
    cout << "In C++, the received string is: " << caracter << endl;
    env->ReleaseStringUTFChars(param1, caracter);
   
    string outCppStr;
    cout << "Enter a String: "<<endl;
    cin >> outCppStr;
    
    return env->NewStringUTF(outCppStr.c_str());
}
