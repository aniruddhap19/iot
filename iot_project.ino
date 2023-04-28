#include<Servo.h>
#define BLYNK_TEMPLATE_ID "TMPLA5wFzqNq"
#define BLYNK_DEVICE_NAME "IOOOOt"
#define BLYNK_AUTH_TOKEN "HFJRkBlj1-VoVI4ZT03ynORHqd1svNrP"

#define BLYNK_PRINT Serial

Servo servo;
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

void myTimerEvent();
char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "real";
char pass[] = "12345678";

BlynkTimer timer;

int temp(){
float temp_val;
temp_val=(analogRead(A0)*41.487);
temp_val=(temp_val/10);
Serial.println(temp_val);
return temp_val;
}

BLYNK_WRITE(V2){
  servo.write(param.asInt()); //emulating door movement using a servo
}
BLYNK_WRITE(V0){
  digitalWrite(16,param.asInt()); //light switch 
}
BLYNK_WRITE(V3){
  digitalWrite(0,param.asInt()); //fan switch 
}

void setup()
{
  Serial.begin(9600);
  servo.attach(5);
  servo.write(0);
  pinMode(16,OUTPUT);
  pinMode(0,OUTPUT);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L,myTimerEvent);
}
void myTimerEvent(){
  Blynk.virtualWrite(V1,temp()); 
}

void loop()
{
  Blynk.run();
  timer.run();
}
