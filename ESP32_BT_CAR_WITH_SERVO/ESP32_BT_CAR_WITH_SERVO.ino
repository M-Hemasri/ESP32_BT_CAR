#include "BluetoothSerial.h"
#include "ESP32Servo.h"

BluetoothSerial SerialBT;

// MOTOR PINS
int IN3 = 26;
int IN4 = 27;
int ENB = 33;
int SERVOPIN = 13;

char command;
Servo myServo;

// PWM settings
int freq = 1000;
int resolution = 8;
int speed_val =255;
int motor_channel = 4;  

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_car"); // BLUETOOTH NAME

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // Servo setup (Automatically uses early LEDC channels like 0)
  myServo.attach(SERVOPIN, 500, 2400);
  myServo.write(90);

  // Motor PWM setup on an isolated channel
  ledcSetup(motor_channel, freq, resolution);
  ledcAttachPin(ENB, motor_channel);
}

void loop() {
  if (SerialBT.available()) {
    command = SerialBT.read();
    if (command == 'F') forward();
    else if (command == 'B') backward();
    else if (command == 'S') Stop();
    else if (command == 'L') {
      // Added delay so the servo has time to physically turn
      for (int angle = 90; angle >= 0; angle -= 10) {
        myServo.write(angle);
        delay(20); 
      }
    }
    else if (command == 'R') {
      // Added delay so the servo has time to physically turn
      for (int angle = 90; angle <= 170; angle += 10) {
        myServo.write(angle);
        delay(20);
      }
    }
    else if (command == 'C') {
      myServo.write(90);
    }
  }
}

// Movement functions updated to use motor_channel (4)
void forward() {
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  ledcWrite(motor_channel, speed_val);
}

void backward() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  ledcWrite(motor_channel, speed_val);
}

void Stop() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  ledcWrite(motor_channel, 0);
}
