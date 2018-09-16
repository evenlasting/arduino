#include <MsTimer2.h>

#include <LiquidCrystal.h>

#include <Servo.h>


Servo myservo1;
Servo other;
LiquidCrystal lcd(12,11,5,4,3,2);
int INF=99999;
int change=30;
int pos=0;
int tpush;
int acce=0;

void setup() {                                    //init
  lcd.begin(16,2);
  Serial.begin(9600);
  myservo1.attach(9);
  other.attach(A3);
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(6,INPUT);
  digitalWrite(LED_BUILTIN,LOW);
  int tpush=check();
  MsTimer2::set(40,LED);
  MsTimer2::start();
}

void LED(){                                      //interrupt1
  int bscore=analogRead(A1);
  int score=map(bscore,23,1018,2000,15000);
  //Serial.println(score);
  lcd.clear();
  lcd.print("auto s:");
  lcd.print(score);
  lcd.setCursor(0,2);
  lcd.print("your s:");
  long yours=(long)change*score/tpush;
  lcd.print(yours);
}

void servo(){                                  //servo1
  int x=analogRead(A0);
  if (x>1000) {myservo1.write(0);
  delay(15);
  myservo1.write(90);
  delay(100);}
  //Serial.println(x);
}

void loop() {                                //check for the last mode
  // put your main code here, to run repeatedly:
  servo();
  doublecheck();
}

int doublecheck(){                              //check for the last mode
  
  if (begindoublecheck())
     {
        MsTimer2::stop();
        MsTimer2::set(20,servo);
        MsTimer2::start();
        moveotherservo();
     }
}

int begindoublecheck(){                        //check the A1
  static int rem=INF;
  int x=analogRead(A1);
  if (rem>change&&x>change) {acce=rem;rem=x;}
  if (rem<change&&x<change) return 1;
  return 0;
}

int check(){                               //check the reaction rate
  digitalWrite(LED_BUILTIN,HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN,LOW);
  delay(1000);
  digitalWrite(LED_BUILTIN,HIGH);
  int time=millis();
  while (digitalRead(6));
  return millis()-time;
}

void moveotherservo(){                    //move the other servo
  
for (int i=0;i<=60;i++)
{
  if (i<30)
  other.write((int)asin(((-30*acce*i+35)/70)*180/3.14));
  else
  other.write((int)(asin(30*acce*i-35)/70*180/3.14));
  delay(1);
}
}
