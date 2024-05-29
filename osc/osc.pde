/**
 * oscP5sendreceive by andreas schlegel
 * example shows how to send and receive osc messages.
 * oscP5 website at http://www.sojamo.de/oscP5
 */

import oscP5.*;
import netP5.*;

OscP5 oscP5;
NetAddress ableton;

void setup() {
  size(400, 400);
  frameRate(25);

  print(this);

  oscP5 = new OscP5(this, 8888); // Listening en puerto 8888

  //ableton = new NetAddress("127.0.0.1", 12000); // Definir puerto de Ableton con IP local
}


void draw() {
}

/* incoming osc message are forwarded to the oscEvent method. */
void oscEvent(OscMessage theOscMessage) {
  /* print the address pattern and the typetag of the received OscMessage */
  print("### received an osc message.");
  print(" addrpattern: "+theOscMessage.addrPattern());
  println(" typetag: "+theOscMessage.typetag());

  // if addrPattern()
  //OscMessage myMessage = new OscMessage("/test");
  //myMessage.add(123); /* add an int to the osc message */
  //oscP5.send(myMessage, arduinoSubenBajan);
}
