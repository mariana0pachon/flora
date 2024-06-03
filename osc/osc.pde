/**
 * oscP5sendreceive by andreas schlegel
 * example shows how to send and receive osc messages.
 * oscP5 website at http://www.sojamo.de/oscP5
 */

import oscP5.*;
import netP5.*;

OscP5 oscP5;
NetAddress myRemoteLocation;

void setup() {
  size(400, 400);
  frameRate(25);
  /* start oscP5, listening for incoming messages at port 12000 */
  oscP5 = new OscP5(this, 12000);

  /* myRemoteLocation is a NetAddress. a NetAddress takes 2 parameters,
   * an ip address and a port number. myRemoteLocation is used as parameter in
   * oscP5.send() when sending osc packets to another computer, device,
   * application. usage see below. for testing purposes the listening port
   * and the port of the remote location address are the same, hence you will
   * send messages back to this sketch.
   */
  myRemoteLocation = new NetAddress("192.168.0.106", 8000);
}


void draw() {
  background(0);
}

void keyPressed() {
  OscMessage myMessage;
  if (key == '0') {
    myMessage = new OscMessage("/estado0");
  } else if (key == 's') {
    myMessage = new OscMessage("/semilla");
  } else if (key == 'c') {
    myMessage = new OscMessage("/caracol");
  } else if (key == 'a') {
    myMessage = new OscMessage("/abejas");
  } else if (key == 'f') {
    myMessage = new OscMessage("/suben_bajan");
  } else {
    myMessage = new OscMessage("/otra_conexion");
  }

  myMessage.add(123);
  oscP5.send(myMessage, myRemoteLocation);
}


/* incoming osc message are forwarded to the oscEvent method. */
void oscEvent(OscMessage theOscMessage) {
  /* print the address pattern and the typetag of the received OscMessage */
  print("### received an osc message.");
  print(" addrpattern: "+theOscMessage.addrPattern());
  println(" typetag: "+theOscMessage.typetag());

  if (theOscMessage.addrPattern().equals("/semilla")) {
    println("sending to Purr Data");
    OscMessage myMessage = new OscMessage("/semilla");
    myMessage.add(123);
    oscP5.send(myMessage, myRemoteLocation);
  }
}
