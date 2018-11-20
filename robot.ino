#include "max6675.h"
#include <Stepper.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include<SoftwareSerial.h>
#define VREF 5
#define TxD A5
#define RxD A4
SoftwareSerial bluetoothSerial(TxD, RxD);
String c;
int ktcSO = 8;
int ktcCS = 7;
int ktcCLK = 6;
const int stepsPerRevolution = 300;  // change this to fit the number of steps per revolution
bool abierto = false;
bool modoManual = false;
double lecturaSensor;
MAX6675 ktc(ktcCLK, ktcCS, ktcSO);
Stepper myStepper(stepsPerRevolution, 9,10,11,12);
Stepper myStepper2(stepsPerRevolution, 2,3,4,5);
int temperature = 0;
String tempString = "";
String lluviaString ="";
String mensaje = "";
void setup() {
  Serial.begin(9600);
  bluetoothSerial.begin(9600);
  myStepper.setSpeed(30);
  myStepper2.setSpeed(30);
  InitADC();
  // give the MAX a little time to settle
  delay(500);
}


void InitADC()
{
 // Select Vref=AVcc
 ADMUX |= (1<<REFS0);
 //set prescaller to 128 and enable ADC 
 ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);    
}

uint16_t ReadADC(uint8_t ADCchannel)
{
 //select ADC channel with safety mask
 ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);
 //single conversion mode
 ADCSRA |= (1<<ADSC);
 // wait until ADC conversion is complete
 while( ADCSRA & (1<<ADSC) );
 return ADC;
}

void stopMotor(int entry1,int entry2,int entry3,int entry4){ // this function turns down the motor because it sets everything in LOW
  digitalWrite(entry1, LOW); // the entry is set LOW
  digitalWrite(entry2, LOW);  // the entry is set LOW
  digitalWrite(entry3, LOW); // the entry is set LOW
  digitalWrite(entry4, LOW);  // the entry is set LOW
  }

void loop() {
   
   if(bluetoothSerial.available()){
     c = bluetoothSerial.readString();
     Serial.print("******************");
     Serial.print(c);
     Serial.print("******************");
     if(c=="1"){
      modoManual = true;
      if (abierto == true){
        
        Serial.println("cerrando"); 
        myStepper.step(stepsPerRevolution);
        stopMotor(9,10,11,12);
        
        myStepper2.step(-stepsPerRevolution);
        stopMotor(2,3,4,5);
        abierto = false;
        }
        
     }
     if(c=="0"){
       modoManual = true;
       if (abierto == false){
        Serial.println("abriendo"); 
        myStepper.step(-stepsPerRevolution);
        stopMotor(9,10,11,12);
        
        myStepper2.step(stepsPerRevolution);
        stopMotor(2,3,4,5);
        abierto = true;
        }
     }
     if(c=="2"){
       modoManual = false;
     }
     if(c[0] == '4'){ // temperatura
      Serial.println("ghol");
      }
      if(c[0] == '3'){ // lluvia
      Serial.println("ghol");
      }
   }
  // basic readout test
   lecturaSensor=(double)ReadADC(0);
   Serial.println("medicion");
   Serial.println((uint16_t)lecturaSensor);
   
   Serial.println("Deg C = "); 
   temperature = ktc.readCelsius();
   Serial.println(temperature);
   mensaje = String(temperature);
   if(lecturaSensor >= 420 && lecturaSensor <= 700){
      lluviaString = "medio";
    }
    if(lecturaSensor < 420 ){
      lluviaString = "alto";
    }

   if(lecturaSensor > 700 ){
      lluviaString = "bajo";
    }
   mensaje.concat(","); 
   mensaje.concat(lluviaString);
   bluetoothSerial.println(mensaje);
   Serial.println(mensaje);
   
   if(temperature > 35 && abierto == true && modoManual == false){
     Serial.println("cerrando"); 
     myStepper.step(stepsPerRevolution);
     stopMotor(9,10,11,12);
     myStepper2.step(-stepsPerRevolution);
     stopMotor(2,3,4,5);
     abierto = false;
    
   }
   if(lecturaSensor <= 420 && abierto == true && modoManual == false){
     Serial.println("cerrando"); 
     myStepper.step(stepsPerRevolution);
     stopMotor(9,10,11,12);
     myStepper2.step(-stepsPerRevolution);
     stopMotor(2,3,4,5);
     abierto = false;
    
   }
   if((temperature <= 35 || lecturaSensor > 420) && abierto == true){
     Serial.println("permanece abierto"); 
    
   }
   if((temperature > 35 || lecturaSensor <= 420) && abierto == false){
     Serial.println("permanece cerrado"); 
    
   }
   if(lecturaSensor > 420 && abierto == false && temperature <= 35 && modoManual == false){
     Serial.println("abriendo"); 
     myStepper.step(-stepsPerRevolution);
     stopMotor(9,10,11,12);
     myStepper2.step(stepsPerRevolution);
     stopMotor(2,3,4,5);
     abierto = true;
   }
    
   if(temperature <= 35 && abierto == false && lecturaSensor > 420 && modoManual == false){
    Serial.println("abriendo"); 
     myStepper.step(-stepsPerRevolution);
     stopMotor(9,10,11,12);
     myStepper2.step(stepsPerRevolution);
     stopMotor(2,3,4,5);
     abierto = true; 
    
   }
 delay(500);
   
}
