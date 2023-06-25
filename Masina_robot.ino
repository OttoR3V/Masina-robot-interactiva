#include<NewPing.h>
#include<AFMotor.h>

#define TRIGGER_PIN A1
#define ECHO_PIN A0
#define MAX_DISTANCE 100
#define RIGHT A2
#define LEFT A3


NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);


AF_DCMotor m1(3,MOTOR12_1KHZ); 
AF_DCMotor m2(4,MOTOR12_1KHZ);
AF_DCMotor m3(1,MOTOR34_1KHZ);
AF_DCMotor m4(2,MOTOR34_1KHZ);

char comanda; 
int controlRemote=1; 
int counter=0; 

void setup() 
{
  Serial.begin(9600);
  pinMode(RIGHT, INPUT); 
  pinMode(LEFT, INPUT);
  pinMode(A4, OUTPUT); 
  pinMode(A5, OUTPUT); 
}


void loop(){
 
  if(Serial.available() > 0){ 
    comanda = Serial.read(); 
    Stop();
    
    if(comanda=='O'){
      controlRemote=0;
   
    }else if(comanda=='N'){
      controlRemote=1;
  
    }
  }
  
  if(controlRemote==1){
    manual();
  }else if(controlRemote==0){
    automat();
  }
} 


void forward()
{
  m1.setSpeed(255);
  m1.run(FORWARD);
  m2.setSpeed(255);
  m2.run(FORWARD);
  m3.setSpeed(255);
  m3.run(FORWARD);
  m4.setSpeed(255);
  m4.run(FORWARD);
}


void back()
{
  m1.setSpeed(255);
  m1.run(BACKWARD);
  m2.setSpeed(255);
  m2.run(BACKWARD);
  m3.setSpeed(255);
  m3.run(BACKWARD);
  m4.setSpeed(255);
  m4.run(BACKWARD);
}


void left()
{
  m1.setSpeed(255);
  m1.run(BACKWARD);
  m2.setSpeed(255);
  m2.run(BACKWARD);
  m3.setSpeed(255);
  m3.run(FORWARD);
  m4.setSpeed(255);
  m4.run(FORWARD);
}


void right()
{
  m1.setSpeed(255);
  m1.run(FORWARD);
  m2.setSpeed(255);
  m2.run(FORWARD);
  m3.setSpeed(255);
  m3.run(BACKWARD);
  m4.setSpeed(255);
  m4.run(BACKWARD);
} 


void Stop()
{
  m1.setSpeed(0);
  m1.run(RELEASE);
  m2.setSpeed(0);
  m2.run(RELEASE);
  m3.setSpeed(0);
  m3.run(RELEASE);
  m4.setSpeed(0);
  m4.run(RELEASE);
}

void manual(){
 
  switch(comanda){
      case 'F':
        digitalWrite(A4, LOW);
        digitalWrite(A5, HIGH);
        forward();
        break;
      case 'B':
        digitalWrite(A4, HIGH); 
        digitalWrite(A5, LOW); 
         back();
        break;
      case 'L':
        digitalWrite(A4, LOW);
        digitalWrite(A5, LOW);
        left();
        break;
      case 'R':
        digitalWrite(A4, LOW);
        digitalWrite(A5, LOW);
        right();
        break;
      case 'K':
        digitalWrite(A4, LOW);
        digitalWrite(A5, LOW);
        rutina();
        break;
      case 'S':
        digitalWrite(A4, LOW);
        digitalWrite(A5, LOW);
        Stop();
        break;
        }
}


void automat(){
  delay(70);
  unsigned int distance = sonar.ping_cm();

  if(counter<10){
    counter++;
  }else{
    Serial.println(distance); 
    counter=0; 
  }
  
  int senzorDreapta = digitalRead(RIGHT); 
  int senzorStanga = digitalRead(LEFT); 

  if((senzorDreapta==1) && (distance>=10 && distance<=40)&&(senzorStanga==1)){
    m1.setSpeed(120);
    m1.run(FORWARD);
    m2.setSpeed(120);
    m2.run(FORWARD);
    m3.setSpeed(120);
    m3.run(FORWARD);
    m4.setSpeed(120);
    m4.run(FORWARD);
  }else if((senzorDreapta==0) && (senzorStanga==1)) {
    m1.setSpeed(200);
    m1.run(FORWARD);
    m2.setSpeed(200);
    m2.run(FORWARD);
    m3.setSpeed(100);
    m3.run(BACKWARD);
    m4.setSpeed(100);
    m4.run(BACKWARD);
  }else if((senzorDreapta==1)&&(senzorStanga==0)) {
    m1.setSpeed(100);
    m1.run(BACKWARD);
    m2.setSpeed(100);
    m2.run(BACKWARD);
    m3.setSpeed(200);
    m3.run(FORWARD);
    m4.setSpeed(200);
    m4.run(FORWARD);
  }else if((senzorDreapta==1)&&(senzorStanga==1)) {
    m1.setSpeed(0);
    m1.run(RELEASE);
    m2.setSpeed(0);
    m2.run(RELEASE);
    m3.setSpeed(0);
    m3.run(RELEASE);
    m4.setSpeed(0);
    m4.run(RELEASE);
 } else {
  if (distance < 10) {
    m1.setSpeed(0);
    m1.run(RELEASE);
    m2.setSpeed(0);
    m2.run(RELEASE);
    m3.setSpeed(0);
    m3.run(RELEASE);
    m4.setSpeed(0);
    m4.run(RELEASE);
  }
}}
void rutina() {
  Stop();
  forward();
  delay(1000); 

  Stop();
  left();
  delay(550); 

  Stop();
  forward();
  delay(1000); 

  Stop();
  left();
  delay(550); 

  Stop();
}
