/*Manual Mode
This program  is designed to control the brightness of the LED with Push Button
*/
 #include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

float PV;
float co;
int up;
int down;

void setup() {
// defining pin intput/output, communications & initiate LCD
pinMode(9,OUTPUT);
pinMode(7,INPUT);
pinMode(8,INPUT);
Serial.begin(9600);
lcd.begin(16,2);
}

void loop() {

PV = analogRead(A0);      //read & store A0 value to PV

up = digitalRead(8);      //read & store pin 8 value to up
//controling co with pin 8 PB(add)
if (up == 1){
  co = co+1;
  }
//controling co with pin 7 PB(sub)
down = digitalRead(7);    //read & store pin 7 value to down
if (down == 1){
  co=co-1;
  }

analogWrite(9,co);        //write co value to pin 9
//print values into serial monitor
Serial.print("PV= ");
Serial.print(PV);
Serial.print(" ,co= ");
Serial.println(co);
//print values into LCD
lcd.setCursor(0,0);
lcd.print("PV : ");
lcd.setCursor(5,0);
lcd.print(PV);
lcd.setCursor(0,1);
lcd.print("C.O.: ");
lcd.setCursor(5,1);
lcd.print(co);
delay(100);

}
