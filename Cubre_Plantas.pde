import processing.serial.*;
Serial myPort;
String temperatura="numT";
String lluvia="numL";
String mensaje = "32,medio";
int valorTempLim = 35;
int valorLluviaLim = 420;
boolean doOnce;
void setup(){
  size(450, 600);
  myPort = new Serial(this, "COM4", 9600); // Starts the serial communication
  myPort.bufferUntil('\n'); // Defines up to which character the data from the serial port will be read. The character '\n' or 'New Line'
}
void serialEvent (Serial myPort){ // Checks for available data in the Serial Port
  mensaje = myPort.readStringUntil('\n'); //Reads the data sent from the Arduino (the String "LED: OFF/ON) and it puts into the "ledStatus" variable
  String[] list = split(mensaje, ',');
  temperatura = list[0];
  lluvia = list[1];
}

void draw(){
  background(59, 201, 71);
  fill(255, 201, 71); // orange Color
  stroke(33);
  strokeWeight(1);
  rect(50, 100, 150, 50, 10);  // Turn ON Button
  rect(250, 100, 150, 50, 10); // Turn OFF Button
  rect(53, 400, 350, 50, 10); // Turn OFF Button
  rect(357, 567, 25, 25, 10); // Turn OFF Button
  rect(357, 527, 25, 25, 10); // Turn OFF Button
  rect(387, 567, 25, 25, 10); // Turn OFF Button
  rect(387, 527, 25, 25, 10); // Turn OFF Button
  rect(417, 567, 25, 25, 10); // Turn OFF Button
  rect(417, 527, 25, 25, 10); // Turn OFF Button
  fill(255);
  
  textSize(32);
  text("   Abrir",60, 135);
  text("  Cerrar", 255, 135);
  text("Salir del modo manual", 55, 440);
  textSize(24);
  fill(33);
  text("Entra al modo manual para mover el", 20, 50);
  text("techo presionando:", 20, 80);
  text("Mediciones:", 10, 240);
  text("Temperatura:", 50, 280);
  text("Nivel de lluvia:", 50, 320);
  text("Cambiar valores limite:", 10, 500);
  text("Temperatura:", 50, 550);
  text("Lluvia:", 50, 590);
  text("+", 362, 586);
  text("+", 362, 546);
  text("-", 392, 586);
  text("-", 392, 546);
  text(">", 422, 586);
  text(">", 422, 546);  
  text(valorTempLim, 250, 550); // Prints the string comming from the Arduino
  text(valorLluviaLim, 250, 590); // Prints the string comming from the Arduino
  textSize(30);
  textSize(20);

  text(temperatura, 230, 280); // Prints the string comming from the Arduino
  text(lluvia, 230, 320); // Prints the string comming from the Arduino
  
  // If the button "cerrando" is pressed
  if(mousePressed && mouseX>50 && mouseX<200 && mouseY>100 && mouseY<150 && doOnce == false){
    myPort.write("0"); // Sends the character '1' and that will turn on the LED
    // Highlighs the buttons in red color when pressed
    stroke(255,0,0);
    strokeWeight(2);
    noFill();
    rect(50, 100, 150, 50, 10);
    doOnce = true;
  }
  // If the button "abriendo" is pressed
  if(mousePressed && mouseX>250 && mouseX<400 && mouseY>100 && mouseY<150 && doOnce == false){
    myPort.write("1"); // Sends the character '0' and that will turn on the LED
    stroke(255,0,0);
    strokeWeight(2);
    noFill();
    rect(250, 100, 150, 50, 10);
    doOnce = true;
  }
  if(mousePressed && mouseX>53 && mouseX<403 && mouseY>400 && mouseY<450 && doOnce == false){
    myPort.write("2"); // Sends the character '0' and that will turn on the LED
    stroke(255,0,0);
    strokeWeight(2);
    noFill();
    rect(53, 400, 350, 50, 10);
    doOnce = true;
  }
  
  if(mousePressed && mouseX>357 && mouseX<382 && mouseY>567 && mouseY<592 && doOnce == false){
    valorLluviaLim = valorLluviaLim + 1;
     doOnce = true;
  }
  if(mousePressed && mouseX>357 && mouseX<382 && mouseY>527 && mouseY<552 && doOnce == false){
    valorTempLim = valorTempLim + 1;
     doOnce = true;
  }
  if(mousePressed && mouseX>387 && mouseX<412 && mouseY>567 && mouseY<592 && doOnce == false){
    valorLluviaLim = valorLluviaLim - 1;
     doOnce = true;
  }
  if(mousePressed && mouseX>387 && mouseX<412 && mouseY>527 && mouseY<552 && doOnce == false){
    
    valorTempLim = valorTempLim - 1;
     doOnce = true;
  }
  if(mousePressed && mouseX>417 && mouseX<442 && mouseY>567 && mouseY<592 && doOnce == false){ //mandarlluvia
    String msj = str(valorLluviaLim);
    String msjFinal = "3" + msj;
    myPort.write(msjFinal); // Sends the character '0' and that will turn on the LED
     doOnce = true;
   
  }
  if(mousePressed && mouseX>417 && mouseX<442 && mouseY>527 && mouseY<552 && doOnce == false){ //mandar temo
    String msj = str(valorTempLim);
    String msjFinal = "4" + msj;
    myPort.write(msjFinal); // Sends the character '0' and that will turn on the LED
     doOnce = true;
  }
  if (!mousePressed) {
    doOnce = false;
  }
}