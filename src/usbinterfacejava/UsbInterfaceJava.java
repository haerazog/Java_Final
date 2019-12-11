
package usbinterfacejava;

/**
 *
 * @author haerazog
 */
public class UsbInterfaceJava {
     

     public static void main(String[] args) {
        System.loadLibrary("libLibreriaMela");
        //String result = new UsbInterfaceJava().sayHello("Hello from Java");
        //System.out.println("In Java, the returned string is: " + result);
        
        new UsbInterfaceJava().SerialPort("\\\\.\\COM14");
        int response = new UsbInterfaceJava().isconnected();
        System.out.println("Is connected: " + response);
    }
    
    private native String sayHello(String msg);
    private native void SerialPort(String port);
    private native int isconnected();
    
}
