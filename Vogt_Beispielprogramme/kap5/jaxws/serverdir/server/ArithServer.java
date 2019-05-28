package server;
import javax.xml.ws.Endpoint;
import service.Arith;
public class ArithServer {
 public static void main (String args[]) {
  Arith arithServer = new Arith();
  Endpoint endpoint = Endpoint.publish(
             "http://serveradresse:55555/arith", arithServer);
 }
}