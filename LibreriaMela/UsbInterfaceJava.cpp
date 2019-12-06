// Native methods implementation of
// C:/Users/haerazog/Documents/NetBeansProjects/UsbInterfaceJava/src/usbinterfacejava/UsbInterfaceJava.java

#include "UsbInterfaceJava.h"

jdouble JNICALL Java_usbinterfacejava_UsbInterfaceJava_Suma
  (JNIEnv * env, jobject object, jint param1, jint param2) {
    jdouble result;
   printf("In C, the numbers are %d and %d\n", param1, param2);
   result = ((jdouble)param1 + param2);
   // jint is mapped to int, jdouble is mapped to double
   return result;
}

jdouble JNICALL Java_usbinterfacejava_UsbInterfaceJava_Resta
  (JNIEnv * env, jobject object, jint param1, jint param2) {
    jdouble result;
   printf("In C, the numbers are %d and %d\n", param1, param2);
   result = ((jdouble)param1 - param2);
   // jint is mapped to int, jdouble is mapped to double
   return result;
}
