#include <MsTimer2.h>

#include <LiquidCrystal.h>

#include <Servo.h>

Servo myservo1;
Servo other;
LiquidCrystal lcd(12,11,5,4,3,2);

int pos=0;
int tpush;
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  Serial.begin(9600);
  myservo1.attach(9);
  other.attach(A3);
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(6,INPUT);
  digitalWrite(LED_BUILTIN,LOW);
  //  int tpush=check();
  tpush=300;
  MsTimer2::set(40,LED);
  MsTimer2::start();
}

void LED(){
  int bscore=analogRead(A1);
  int score=map(bscore,23,1018,2000,15000);
  //Serial.println(score);
  lcd.clear();
  lcd.print("auto s:");
  //lcd.print(score);
  lcd.setCursor(0,2);
  lcd.print("your s:");
  long yours=(long)30*score/tpush;
  //lcd.print(yours);
}

void servo(){
  int x=analogRead(A0);
  if (x>1000) {myservo1.write(0);
  delay();
  myservo1.write(90);
  delay(100);}
  Serial.println(x);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*
  int x=analogRead(A0);
  if (x>1000) {myservo1.write(0);
  delay(30);
  myservo1.write(90);
  delay(100);}
  Serial.println(x);
  */
  doublecheck();
    //Serial.println(digitalRead(2));
}

int doublecheck(){
  MsTimer2::stop();
  MsTimer2::set(20,servo);
  MsTimer2::start();
  if (pushbotton())
     {
      for (int i=0;i<60;i++)
      moveotherservo();
     }
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

void moveotherservo(){
  static int theta=25;
  other.write(theta);
  delay(170);
  servo();
  theta++;
}
