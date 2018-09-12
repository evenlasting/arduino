#include <Servo.h>

Servo myservo1;

int pos=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo1.attach(9);
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(2,INPUT);
  digitalWrite(LED_BUILTIN,LOW);
    Serial.println(check());
}

void loop() {
  // put your main code here, to run repeatedly:
  /*int x=analogRead(A0);
  if (x>1000) myservo1.write(20);
  delay(30);
  myservo1.write(90);
  delay(100);
  //Serial.println(x);*/

    //Serial.println(digitalRead(2));
}

int check(){ //my check is 330ms
  digitalWrite(LED_BUILTIN,HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN,LOW);
  delay(1000);
  digitalWrite(LED_BUILTIN,HIGH);
  int time=millis();
  while (digitalRead(2));
  return millis()-time;
}
