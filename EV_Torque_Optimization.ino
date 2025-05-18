// ////////////////// LCD /////////////////////////// 
#include <LiquidCrystal.h>
// Define the LCD connections
const int rs = PB13, en = PB14, d4 = PB15, d5 = PA8, d6 = PA7, d7 = PA6; LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#include <Servo.h>
Servo ESC;​// create servo object to control the ESC int potValue; // value from the analog pin
 
#define modeSwitch1 PA3 #define modeSwitch2 PA4
void setup() { Serial.begin(9600);
// Attach the ESC on pin 9
ESC.attach(PB7, 1000, 2000); // (pin, min pulse width, max pulse width in microseconds)
ESC.write(0);
// Setup switches
pinMode(modeSwitch1, INPUT_PULLUP); // Manual mode pinMode(modeSwitch2, INPUT_PULLUP); // Potentiometer mode
/////////// lcd ///////////////// lcd.begin(16, 2);
lcd.clear(); lcd.setCursor(0, 0); lcd.print("Control - BLDC"); lcd.setCursor(0, 1); lcd.print("motor with PWM"); delay(1000);
}
 
void loop() {  lcd.clear(); lcd.setCursor(0, 0);
lcd.print("1 - manual "); lcd.setCursor(0, 1); lcd.print("2 - pot"); delay(100);
if (digitalRead(modeSwitch1) == LOW) {
 
 
while (1) {
angle();
}
}
if (digitalRead(modeSwitch2) == LOW) { while (1) {
pot();
}
}
}
 
void pot() { lcd.clear(); lcd.setCursor(0, 0); lcd.print("SPEED"); lcd.setCursor(0, 1);
potValue = analogRead(PA5); // reads the value of the potentiometer (value between 0 and 1023)
lcd.print(potValue);
potValue = map(potValue, 0, 4095, 0, 180); // scale it to use it with the servo library (value between 0 and 180)
ESC.write(potValue);​// Send the signal to the ESC Serial.println(potValue);
lcd.setCursor(9, 0);
lcd.print("incline"); lcd.setCursor(9, 1);
potValue = map(potValue, 0, 180, 60, 0); lcd.print(potValue);
 
 
 
lcd.print("incline"); lcd.setCursor(9, 1);
potValue = map(potValue, 0, 180, 60, 0); lcd.print(potValue);
delay(200);
 
void angle() { potValue = 90; delay(1000); while (1) {
lcd.clear(); lcd.setCursor(0, 0); lcd.print("angle"); lcd.setCursor(0, 1);
if (digitalRead(modeSwitch1) == LOW) { potValue = potValue + 10; delay(500);
if (potValue >= 90) { potValue = 90;
}
}
if (digitalRead(modeSwitch2) == LOW) { potValue = potValue - 10; delay(500);
if (potValue <= 0) { potValue = 0;
}
}
lcd.print(potValue);
int speed = map(potValue, 0, 90, 90, 0); // scale it to use it with the servo library (value between 0 and 180)
ESC.write(speed);​// Send the signal to the ESC Serial.println(speed);
lcd.setCursor(9, 0);
speed = map(potValue, 0, 90, 4095, 0); // scale it to use it with the servo library (value between 0 and 180)
lcd.print("speed"); lcd.setCursor(9, 1); lcd.print(speed); delay(200);
}}

