import java.rmi.*;
public interface ArithInterface extends Remote {
  public double mult(double x, double y) throws RemoteException;
}