package client;
import service.Arith;
import service.ArithService;
public class ArithClient {
 public static void main(String args[]) {
  ArithService service = new ArithService();
  Arith arith = service.getArithPort();
  double a = 4.5;
  double b = 1.2;
  double ergebnis = arith.mult(a,b);
  System.out.println("Ergebnis: "+ergebnis);
 }
}