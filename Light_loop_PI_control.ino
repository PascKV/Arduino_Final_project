/*PI control
This program control the LED with OI control
*/
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
//defining float & int & long variables
float PV;
float setp;
float co;
float Pgain;
float error;
int lite = 9;

float Igain;
int integAct;
long interval;
unsigned long prevMillis = 0;
unsigned long curntMillis;

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

up = digitalRead(7);
down = digitalRead(8);
   
PV = analogRead(A0);
curntMillis = millis();

if((curntMillis - prevMillis) >= interval){

  prevMillis = curntMillis;
  error = setp-PV;
  integAct = (integAct+error);
  co = (Pgain*error)+(Igain*integAct);

if (co < 0){
  co = 0;
  delay(50);
  }
if (co > 255){
  co = 255;
  delay(50);
  }

}
analogWrite(lite,co);


//screen change with PB
nextP = digitalRead(10);
if (nextP == 1){
  screen=screen+1;
  lcd.clear();
  if (screen > 4){
    screen = 4;
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
    //Pgain up/down with PB
//page 2
if (up == 1){
  Pgain = Pgain+0.01;
  }

if (down == 1){
  Pgain = Pgain-0.01;
   if (Pgain < 0){
    Pgain = 0;
    }
  }
    lcd.setCursor(0,0);
    lcd.print("C.O.:");
    lcd.setCursor(6,0);
    lcd.print(co);
    lcd.setCursor(0,1);
    lcd.print("Pgain:");
    lcd.setCursor(6,1);
    lcd.print(Pgain);
    }
    break;

    case 3:{
   //Igain up/down with PB
//page 3
if (up == 1){
  Igain = Igain+0.01;
  }

if (down == 1){
  Igain = Igain-0.01;
   if (Igain < 0){
    Igain = 0;
    }
  }
    lcd.setCursor(0,0);
    lcd.print("Error:");
    lcd.setCursor(7,0);
    lcd.print(error);
    lcd.setCursor(0,1);
    lcd.print("Igain:");
    lcd.setCursor(7,1);
    lcd.print(Igain);
      }
     break;
     case 4:{
     //interval
//page 4
if (up == 1){
  interval = interval+10;
  }

if (down == 1){
  interval = interval-10;
   if (interval < 0){
    interval = 0;
    }
  }
    lcd.setCursor(0,0);
    lcd.print("Interval:");
    lcd.setCursor(0,1);
    lcd.print(interval);
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
Serial.print(" ,Pgain= ");
Serial.print(Pgain);
Serial.print(" ,Igain= ");
Serial.print(Igain);
Serial.print(" ,Interval= ");
Serial.print(interval);
Serial.print(" ,Error= ");
Serial.println(error);
delay(100);
  }
