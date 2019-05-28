import java.rmi.*;
public class ArithClient  {
 public static void main(String args[]) {
  try {
   ArithInterface arith;
   String path;
   path = new String("rmi://" + args[0] + "/Arith");
   arith = (ArithInterface) Naming.lookup(path);
   double a = 4.5;
   double b = 1.2;
   double ergebnis = arith.mult(a,b);
   System.out.println("Ergebnis: "+ergebnis);
  } catch (Exception e) {
      System.out.println("Error: " + e.getMessage()); }
 }
}