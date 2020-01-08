
package usbinterfacejava;

/**
 *
 * @author haerazog
 */
public class UsbInterfaceJava {
     

     public static void main(String[] args) {
        //System.loadLibrary("libLibreriaMela");
                
       /*new UsbInterfaceJava().SerialPort("\\\\.\\COM14");
        int response = new UsbInterfaceJava().isconnected();
        System.out.println("Is connected: " + response);*/
    }
    
    private native void SerialPort(String port);
    private native int isconnected();
    private native int readSerialPort(String buffer, int buff_size);
    private native int writeSerialPort(String buffer, int buff_size);
    
}
