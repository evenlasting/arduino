#include <LiquidCrystal.h>

#include <Servo.h>

Servo myservo1;
LiquidCrystal lcd(12,11,5,4,3,2);

int pos=0;
int tpush;
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  Serial.begin(9600);
  myservo1.attach(9);
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(6,INPUT);
  digitalWrite(LED_BUILTIN,LOW);
  //  int tpush=check();
  tpush=300;
}

void loop() {
  // put your main code here, to run repeatedly:
  int bscore=analogRead(A1);
  int score=map(bscore,23,1018,2000,15000);
  Serial.println(score);
  lcd.clear();
  lcd.print("auto s:");
  lcd.print(score);
  lcd.setCursor(0,2);
  lcd.print("your s:");
  long yours=(long)30*score/tpush;
  lcd.print(yours);
  int x=analogRead(A0);
  if (x>11110) myservo1.write(20);
  delay(30);
  myservo1.write(90);
  delay(100);
  //Serial.println(x);

    //Serial.println(digitalRead(2));
}

int check(){
  digitalWrite(LED_BUILTIN,HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN,LOW);
  delay(1000);
  digitalWrite(LED_BUILTIN,HIGH);
  int time=millis();
  while (digitalRead(6));
  return millis()-time;
}
