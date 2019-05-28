import java.rmi.*;
import java.rmi.server.*;
public class ArithServer {
 public static void main(String args[]) {
  try {
   ArithImpl serverobjekt = new ArithImpl();
   Naming.rebind("Arith",serverobjekt);
  } catch (Exception e) { }
 }
}