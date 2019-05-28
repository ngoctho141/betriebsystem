import java.net.*;
import java.rmi.*;
import java.rmi.server.UnicastRemoteObject;
public class ArithImpl
   extends UnicastRemoteObject
   implements ArithInterface {
 public ArithImpl() throws RemoteException {}
 public double mult(double x, double y) throws RemoteException {
   return x*y;
 }
}