#include <Servo.h>
//#include <NewPing.h>
#include <SoftwareSerial.h>
#define trigPin 8   
#define echoPin 9
#define trigPin1 12
#define echoPin1 13 
#define servoPin 10

Servo servo;  
SoftwareSerial mySerial(3,2);
  
long duration,duration1,distance,level;

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());
  }
}

void test ()
{
  Serial.println("Initializing...");
  delay(500);
  mySerial.println("AT");
  updateSerial();
  mySerial.println("AT+CSQ");
  updateSerial();
  mySerial.println("AT+CCID");
  updateSerial();
  mySerial.println("AT+CREG?");
  updateSerial();
  mySerial.println("AT+CUSD=1");
  updateSerial();

  }
   
 void GSM_SMS()
{
  mySerial.println("AT+CMGF=1");
  updateSerial();
  mySerial.println("AT+CMGS=\"+256779126410\"");
  updateSerial();
  mySerial.print("Please Come and Empty the Dustbin...");
  updateSerial();
  mySerial.write(26);
  }


void setup() {  
    Serial.begin(9600);   
    mySerial.begin(9600);  
    
    servo.attach(servoPin);  
    
    pinMode(trigPin, OUTPUT);  
    pinMode(echoPin, INPUT); 
     
    servo.write(0);         
    delay(1000);
    servo.detach();

    test();
   
 if (level<10)
  {
    GSM_SMS();
    }
} 

void measure_distance() {  
digitalWrite(trigPin, LOW);
delayMicroseconds(5);
digitalWrite(trigPin, HIGH);
delayMicroseconds(15);
digitalWrite(trigPin,LOW);
pinMode(echoPin, INPUT);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 30;  
Serial.print("Distance = ");
Serial.println(distance);  
}

void measure_level() {  
digitalWrite(trigPin1, LOW);
delayMicroseconds(5);
digitalWrite(trigPin1, HIGH);
delayMicroseconds(15);
digitalWrite(trigPin1,LOW);
pinMode(echoPin1, INPUT);
duration1 = pulseIn(echoPin1, HIGH);
level = (duration1/2) / 30;
Serial.print("Level = ");
Serial.println(level);
Serial.println();
}
void loop() 
{ 
     measure_distance();
     measure_level(); 
     updateSerial();
                 
if (level<10) {
 servo.attach(servoPin);
  servo.write(0);    
  delay(500);       
}
else if( distance<50 ){
   servo.attach(servoPin);
  servo.write(180);  
  //delay(500);
  
  }
else{
  servo.write(0);    
  delay(1000);
  servo.detach();
  }
}
