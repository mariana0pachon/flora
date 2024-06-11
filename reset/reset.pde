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

void setup() {
  size(400, 400);
  frameRate(25);
  oscP5 = new OscP5(this, 12000); // Initialize oscP5
  semilla = new NetAddress("127.0.0.1", 12000);
  caracol = new NetAddress("127.0.0.1", 12000);
  abejas = new NetAddress("127.0.0.1", 12000);
  suben_bajan = new NetAddress("127.0.0.1", 12000);
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
  println("reseteando");
}
