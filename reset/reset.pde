import oscP5.*;
import netP5.*;

OscP5 oscP5;
NetAddress semilla;
NetAddress caracol;
NetAddress abejas;
NetAddress suben_bajan;
NetAddress audioIP;

PImage bgImage;

void setup() {
  fullScreen();
  frameRate(25);

  bgImage = loadImage("Riset.png");

  oscP5 = new OscP5(this, 12000);

  // IPs fijos en router Flora
  semilla = new NetAddress("192.168.1.37", 8881);
  caracol = new NetAddress("192.168.1.40", 8881);
  abejas = new NetAddress("192.168.1.41", 8881);
  suben_bajan = new NetAddress("192.168.1.39", 8881);

  audioIP = new NetAddress("192.168.1.35", 8000);

  textAlign(CENTER, CENTER);
  textSize(24);
}

void draw() {
  image(bgImage, 0, 0, width, height);
}

void mousePressed() {
  OscMessage myMessage = new OscMessage("/reset");
  myMessage.add(123);
  oscP5.send(myMessage, semilla);
  oscP5.send(myMessage, caracol);
  oscP5.send(myMessage, abejas);
  oscP5.send(myMessage, suben_bajan);

  OscMessage audioReset = new OscMessage("/estado0");
  audioReset.add(0);
  oscP5.send(audioReset, audioIP);

  println("reseteando");
}
