#include <SPI.h>       
#include <SD.h>         
 
File myFile;

 int trigger=4;
int echo=7;
long duration;
int distance=0;
int windmeter=A0;
int windspeed=0;
int tempmeter=A3;
float tempValue=0;
void setup() {
  
 
  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT);
  Serial.begin(9600);
  while (!Serial) {
    ; 
  }
 
  Serial.print("Initializing SD card...");
 
  if (!SD.begin()) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
 
  
  myFile = SD.open("test.txt", FILE_WRITE);
 
  
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("measure");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
   
    Serial.println("error opening test.txt");
  }
 
  
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");
 
  
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
   
    myFile.close();
  } else {
    
    Serial.println("error opening test.txt");
  }
}
 
void loop() {
  windspeed=analogRead(windmeter);
  windspeed=windspeed/25;
  tempValue=analogRead(tempmeter);
  float milivolt=(tempValue/1024)*5*1000;
  float cel=milivolt/10;
  cel=cel/20;

  
  digitalWrite(trigger,LOW);
  delayMicroseconds(2);
  digitalWrite(trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);
  duration=pulseIn(echo,HIGH);
  distance=duration*0.034/2;
   myFile = SD.open("test.txt", FILE_WRITE);
   if (myFile) {
   myFile.print(distance);
   myFile.print(" ");
   myFile.print(windspeed);
    myFile.print(" ");
   myFile.print(cel);
   myFile.println();
    myFile.close();
   }
   delay(1000);
}