#include <dht.h>
#include <Servo.h>
char command ;

dht DHT;

Servo myservo;

void setup() {
 pinMode(PIN_PB1,OUTPUT); //Motor1
 pinMode(PIN_PB2,OUTPUT); //Motor1
 pinMode(PIN_PB3,OUTPUT); //Motor2
 pinMode(PIN_PB4,OUTPUT); //Motor2
 pinMode(PIN_PC4,OUTPUT); //Buzzer
 myservo.attach(PIN_PD6); //Servo
 Serial.begin(9600);
 myservo.write(0);
 motor1_stop();
 motor2_stop();
 stop_tone();
}



void loop() {
  if(Serial.available () > 0 ){
    command = Serial.read();
    switch(command){
       case 'w':
        motor1_forward();
        motor2_forward();
        check();
        break;
       case 's':
        motor1_backward();
        motor2_backward();
        check();
        break;
       case 'a' :
        motor1_left();
        motor2_left();
        check();
        break;
       case 'd':
        motor1_right();
        motor2_right();
        check();
        break; 
       case 'n':
        motor1_stop();
        motor2_stop();
        check();
        break; 
       case 'j':
        print_temp_and_hum();
        break;
       case 'b' :
        stop_tone();
        break;
       case 'v':
         play_tone();
         break;
       case 'x' :
         touch();
         break;
       case 'c' :
         no_touch();
         break;
      } 
  }
}

void motor1_forward(){
  digitalWrite(PIN_PB1,HIGH);
  digitalWrite(PIN_PB2,LOW);
}

void motor2_forward(){
  digitalWrite(PIN_PB3,HIGH);
  digitalWrite(PIN_PB4,LOW);
}


void motor1_backward(){
  digitalWrite(PIN_PB1,LOW);
  digitalWrite(PIN_PB2,HIGH);
}

void motor2_backward(){
  digitalWrite(PIN_PB3,LOW);
  digitalWrite(PIN_PB4,HIGH);
}

void motor1_left(){
  digitalWrite(PIN_PB1,LOW);
  digitalWrite(PIN_PB2,LOW);
}

void motor2_left(){
  digitalWrite(PIN_PB3,HIGH);
  digitalWrite(PIN_PB4,LOW);
}

void motor1_right(){
  digitalWrite(PIN_PB1,HIGH);
  digitalWrite(PIN_PB2,LOW);
}


void motor2_right(){
  digitalWrite(PIN_PB3,LOW);
  digitalWrite(PIN_PB4,LOW);
}

void motor1_stop(){
  digitalWrite(PIN_PB1,LOW);
  digitalWrite(PIN_PB2,LOW);
}

void motor2_stop(){
  digitalWrite(PIN_PB3,LOW);
  digitalWrite(PIN_PB4,LOW);
}

void check(){
   int data = DHT.read11(PIN_PC5);
   float h = DHT.humidity;
   if(h > 80){
      Serial.println("WARNING");
      digitalWrite(PIN_PC4,LOW);
    }
}

void stop_tone(){
  digitalWrite(PIN_PC4,HIGH);
}

void play_tone(){
  digitalWrite(PIN_PC4,LOW);
}

void touch(){
  myservo.write(180);
  delay(2000);
}

void no_touch(){
  myservo.write(30);
  delay(2000);
}

void print_temp_and_hum(){
    int data = DHT.read11(PIN_PC5);
    Serial.print("Temperature = ");
    float t = DHT.temperature;
    Serial.print(t);
    Serial.print(" *C ");
    Serial.print("  Humidity = ");
    float h = DHT.humidity;
    Serial.print(h);
    Serial.println(" % ");
}
