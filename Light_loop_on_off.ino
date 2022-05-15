/*ON-OFF
This program will turn the LED on & off
*/
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
//defining float & int variables
float PV;
float setp;
float co;
float HYS;
int lite = 9;
int screen;
int up;
int down;

int nextP;
int prevP;

void setup() {
//defining input/output, communication & initiate LCD
pinMode(9,OUTPUT);
pinMode(7,INPUT);
pinMode(8,INPUT);
pinMode(10,INPUT);
pinMode(6,INPUT);
Serial.begin(9600);
lcd.begin(16,2);
}

void loop() {
  if(Serial.available()){
    HYS = Serial.parseInt();
    }

up = digitalRead(7);
down = digitalRead(8);
   
PV = analogRead(A0); 
if (PV < (setp-HYS)){
  co = 255;
  delay(50);
  }
if (PV > (setp+HYS)){
  co = 0;
  delay(50);
  }
  
analogWrite(lite,co);

//screen change with PB
nextP = digitalRead(10);
if (nextP == 1){
  screen=screen+1;
  lcd.clear();
  if (screen > 2){
    screen = 2;
    }
    delay(100);
  }
prevP = digitalRead(6);
if (prevP == 1){
  screen=screen-1;
  lcd.clear();
  if(screen < 0){
    screen = 0;
    }
    delay(100);
  }
switch(screen){
  case 1:{
      //SP up/down with PB
//page 1
if (up == 1){
  setp = setp+10;
    if(setp > 880){
     setp = 880;
    }
  }
  
if (down == 1){
  setp = setp-10;
   if(setp < 16){
     setp = 16;
  }
}
    lcd.setCursor(0,0);
    lcd.print("SP:");
    lcd.setCursor(4,0);
    lcd.print(setp);
    lcd.setCursor(0,1);
    lcd.print("PV:");
    lcd.setCursor(4,1);
    lcd.print(PV);
    }
    break;
    
  case 2:{
      //HYS up/down with PB
//page 2
if (up == 1){
  HYS = HYS+1;
  }

if (down == 1){
  HYS = HYS-1;
  }
  
    lcd.setCursor(0,0);
    lcd.print("C.O.:");
    lcd.setCursor(6,0);
    lcd.print(co);
    lcd.setCursor(0,1);
    lcd.print("HYS:");
    lcd.setCursor(6,1);
    lcd.print(HYS);
    }
    break;
  default:{
    //initial page
    lcd.setCursor(5,0);
    lcd.print("HOME");
    lcd.setCursor(5,1);
    lcd.print("PAGE");
    }
    break;
  }
//print in serial monitor
Serial.print("SP= ");
Serial.print(setp);
Serial.print(" ,PV= ");
Serial.print(PV);
Serial.print(" ,co= ");
Serial.print(co);
Serial.print(" ,HYS= ");
Serial.println(HYS);
delay(100);
}
