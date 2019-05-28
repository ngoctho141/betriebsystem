import java.awt.*;
import javax.swing.*;

// Der SteuerThread läuft in einer Endlosschleife
// und ruft periodisch die paint()-Methode des Applets auf.

class SteuerThread extends Thread {

 private JApplet applet; //  Applet, dessen paint()-Methode aufgerufen werden soll
 
 // Konstruktor
 SteuerThread(JApplet applet) {
  this.applet = applet; }
  
 // Aktionen des Threads
 public void run() {
  try {
   for (;;)
    { sleep(1000); // Periode: 1000 Millisekunden
      applet.repaint(); }
   } catch (InterruptedException e) { }
 }
 
}

// Applet mit Animation

public class AnimationsApplet extends JApplet {

 // start() wird von Browser bei Anzeige der Webseite aufgerufen.
 // Die Methode erzeugt und startet einen SteuerThread.
 
 public void start() {
  SteuerThread st = new SteuerThread(this);
  st.start(); }
  
 // paint() führt Zeichenoperationen auf der Bildschirmausgabe aus
 
 static boolean mundAuf = true;
 public void paint(Graphics g) {
  g.setColor(Color.red);
  g.fillRect(50,50,100,200);
  g.setColor(Color.blue);
  g.fillOval(0,0,200,80);
  g.setColor(Color.green);
  g.fillOval(70,100,20,20);
  g.fillOval(110,100,20,20);
  if (mundAuf) {
    g.setColor(Color.green);
    g.fillOval(75,150,50,20);
    g.setColor(Color.black);
    g.fillOval(75,105,10,10);
    g.fillOval(115,105,10,10);
    g.setFont(new Font("Roman",Font.BOLD,20));
    g.drawString("Hello World!",170,150);
    mundAuf = false; /* Das naechste Mal: Mund zu! */
   }
   else {
    g.setColor(Color.green);
    g.fillRect(75,150,50,5);
    g.setColor(Color.white);
    g.fillRect(170,150,80,20);
    mundAuf = true; /* Das naechste Mal: Mund auf! */
   }
 }
 
}