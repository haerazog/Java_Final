
package usbinterfacejava;

/**
 *
 * @author haerazog
 */
public class UsbInterfaceJava {
     

     public static void main(String[] args) {
        System.loadLibrary("libLibreriaMela");
        System.out.println(new UsbInterfaceJava().Suma(4, 5));
        System.out.println(new UsbInterfaceJava().Resta(4, 5));
    }
    
    private native double Suma(int num1, int num2);
    private native double Resta(int num1, int num2);
    
}
