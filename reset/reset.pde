/**
 * oscP5sendreceive by andreas schlegel
 * example shows how to send and receive osc messages.
 * oscP5 website at http://www.sojamo.de/oscP5
 */

import oscP5.*;
import netP5.*;

OscP5 oscP5;
NetAddress semilla;
NetAddress caracol;
NetAddress abejas;
NetAddress suben_bajan;
NetAddress audioIP;

void setup() {
  //size(400, 400);
  fullScreen();
  frameRate(25);
  
  oscP5 = new OscP5(this, 12000); // Initialize oscP5
  
  semilla = new NetAddress("192.168.0.121", 8881);
  caracol = new NetAddress("192.168.0.102", 8881);
  abejas = new NetAddress("192.168.0.111", 8881);
  suben_bajan = new NetAddress("192.168.0.113", 8881);
  
  audioIP = new NetAddress("192.168.0.119", 8000); // IP mariana innov
  //audioIP = new NetAddress("192.168.27.100", 8000); // IP mariana wifi bau
  //audioIP = new NetAddress("192.168.0.124", 8000); // IP daniela innov

  textSize(32);  // Set the text size for the "reset" text
  fill(255);  // Set the text color to white
}
 
void draw() {
  background(0);
  text("reset", width / 2 - textWidth("reset") / 2, height / 2);  // Display "reset" text in the center of the screen
}

void mousePressed() {
  OscMessage myMessage = new OscMessage("/reset");
  myMessage.add(123);
  oscP5.send(myMessage, semilla);
  oscP5.send(myMessage, caracol);
  oscP5.send(myMessage, abejas);
  oscP5.send(myMessage, suben_bajan);

  OscMessage audioReset = new OscMessage("/estado0");

  oscP5.send(audioReset, audioIP);
  println("reseteando");
}
