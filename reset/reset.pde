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

  bgImage = loadImage("instructions_qr.png"); // Make sure it's in the data folder

  oscP5 = new OscP5(this, 12000);

  semilla = new NetAddress("192.168.0.121", 8881);
  caracol = new NetAddress("192.168.0.102", 8881);
  abejas = new NetAddress("192.168.0.111", 8881);
  suben_bajan = new NetAddress("192.168.0.113", 8881);

  audioIP = new NetAddress("192.168.0.119", 8000);

  textAlign(CENTER, CENTER);
  textSize(24);
}

void draw() {
  background(200, 162, 200); // Lilac background

  // Draw title above image
  fill(100, 255, 180); // Pink color
  textSize(48);
  text("scan for instructions", width / 2, height * 0.1);

  // Draw image centered, keeping aspect ratio
  if (bgImage != null) {
    float imgAspect = (float) bgImage.width / bgImage.height;
    float maxHeight = height * 0.5;
    float displayWidth = maxHeight * imgAspect;
    float displayHeight = maxHeight;

    image(bgImage, (width - displayWidth) / 2, height * 0.2, displayWidth, displayHeight);
  }

  // Draw reset circle at bottom right
  float radius = 170;
  float x = width - radius - 40;
  float y = height - radius - 40;
  float cx = x + radius / 2 - 60;
  float cy = y + radius / 2;

  // Instruction above button
  fill(255);
  textSize(30);
  text("make sure to also\nphysically reset\nthe game before playing", cx, y - 60);

  // Red circle button
  fill(200, 0, 0);
  noStroke();
  ellipse(cx, cy, radius, radius);

  // Text inside button
  fill(255);
  textSize(30);
  text("click to reset", cx, cy);
}

void mousePressed() {
  float radius = 140;
  float x = width - radius - 40;
  float y = height - radius - 40;
  float cx = x + radius / 2;
  float cy = y + radius / 2;

  // Only trigger if click is inside reset button
  if (dist(mouseX, mouseY, cx, cy) < radius / 2) {
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
}
