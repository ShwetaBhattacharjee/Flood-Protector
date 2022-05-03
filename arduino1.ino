#include <Servo.h>
#include <LiquidCrystal.h>
#include <Keypad.h> 
#include <SPI.h>
#include <SD.h>

File myFile;
  const byte ROWS = 4; 
  const byte COLS = 4; 
  // Define the Keymap
  char keys[ROWS][COLS] = {
  {'7','8','9','/'},
  {'4','5','6','*'},
  {'1','2','3','-'},
  {'c','0','=','+'}
  };
  byte rowPins[ROWS] = { 25, 26, 27, 28 };   
  byte colPins[COLS] = { 29, 30, 31, 32 }; 
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); 
LiquidCrystal lcd(13,8,7,6,5,4);
LiquidCrystal lcd2(53,52,51,50,49,48);

Servo servoMotor1;
Servo servoMotor2;
int servoPositon1=0,servoPositon2=0;
int trigger=11;
int echo=12;
int buzzer=3;
long duration;
int distance;
int greenled=21;
int yellowled=20;
int redled=19;
String password="1234";
String text="";
int count=0;
int i=0;
void setup() {
   pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT);
   pinMode(greenled,OUTPUT);
   pinMode(yellowled,OUTPUT);
   pinMode(redled,OUTPUT);
  servoMotor1.attach(9);
  servoMotor2.attach(10);
 lcd.begin(16,2); 
  lcd.print("Enter Code");
  myFile = SD.open("test.txt", FILE_WRITE);
   if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("Test New");
    // close the file:
    myFile.close();
    Serial.println("done.");
  }
}
int alertShown=0;
void loop() {

char key=keypad.getKey();
if(key)
{
  count++;
   text+=key;
  if(count>4)
  {
     lcd.clear();
    lcd.print("Wrong Password");
      delay(100);
    lcd.clear();
    text="";
    count=0;
  }
 
  lcd.clear();
   lcd.print(text);
   delay(100);
}
if(text==password)
{
  if(alertShown==0)
  {
  lcd.clear();
  lcd.print("System  Started!");
  delay(1500);
  lcd.print("System Has Started!");
  alertShown=1;
  lcd.clear();
  }
  
 digitalWrite(trigger,LOW);
  delayMicroseconds(2);
  digitalWrite(trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);
  duration=pulseIn(echo,HIGH);
  distance=duration*0.034/2;

if(distance>=530)
{
  digitalWrite(greenled,HIGH);
  delay(500);
  digitalWrite(greenled,LOW);
  delay(200);
}
else if(distance>=500 && distance<=530)
{
   digitalWrite(yellowled,HIGH);
  delay(500);
  digitalWrite(yellowled,LOW);
  delay(200);
   
}
else{
   digitalWrite(redled,HIGH);
  delay(500);
  digitalWrite(redled,LOW);
  delay(200);
}
  lcd.print("Distance ");
  lcd.print(distance);
  lcd.print("cm");
  delay(500);
  lcd.clear();


if(i==0 && distance <=500)
{

lcd2.print("Warning!");
delay(1000); 
lcd2.clear();
lcd2.print("Water Level Risen!");
delay(2000); 
lcd2.clear();
lcd2.print("Gate Is Closing"); 
servoTurnOn();
servoMotor1.write(180);
servoMotor2.write(0);
i=2;
lcd2.clear();
noTone(buzzer);
}
if(i==2 && distance >=510)
{
lcd2.print("Water Level Normal");
delay(2000); 
lcd2.clear();
lcd2.print("Gate Is Opening"); 
servoTurnOff();
servoMotor1.write(0);
servoMotor2.write(180);
i=0;
lcd2.clear();
}
}
}
void servoTurnOn()
{
   for(servoPositon1=0,servoPositon2=180;servoPositon1<=180,servoPositon2>=0;servoPositon1+=5,servoPositon2-=5)
 {
   tone(buzzer,2000);
   delay(50);
   noTone(buzzer);
   delay(150);
  servoMotor1.write(servoPositon1);
  servoMotor2.write(servoPositon2);
  
 }
}
void servoTurnOff()
{
   for(servoPositon1=0,servoPositon2=180;servoPositon1<=180,servoPositon2>=0;servoPositon1+=1,servoPositon2-=1)
 {
  servoMotor1.write(servoPositon2);
  servoMotor2.write(servoPositon1);
  delay(50);
 }
}