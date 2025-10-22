#include <Servo.h>
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

#define LEFT_MOTOR_A 21
#define LEFT_MOTOR_B 22
#define RIGHT_MOTOR_A 23
#define RIGHT_MOTOR_B 19
#define SERVO_PIN 16

Servo kicker;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("SnackCart"); // Bluetooth device name

  // Motor pins
  pinMode(LEFT_MOTOR_A, OUTPUT);
  pinMode(LEFT_MOTOR_B, OUTPUT);
  pinMode(RIGHT_MOTOR_A, OUTPUT);
  pinMode(RIGHT_MOTOR_B, OUTPUT);

  // Servo setup
  kicker.attach(SERVO_PIN);
  kicker.write(0); // Initial position
}

void loop() {
  if (SerialBT.available()) {
    char cmd = SerialBT.read();
    switch (cmd) {
      case 'F': forward(); break;
      case 'B': backward(); break;
      case 'L': left(); break;
      case 'R': right(); break;
      case 'S': stopMotors(); break;
      case 'K': kickSnack(); break;
    }
  }
}

void forward() {
  digitalWrite(LEFT_MOTOR_A, HIGH);
  digitalWrite(LEFT_MOTOR_B, LOW);
  digitalWrite(RIGHT_MOTOR_A, HIGH);
  digitalWrite(RIGHT_MOTOR_B, LOW);
}

void backward() {
  digitalWrite(LEFT_MOTOR_A, LOW);
  digitalWrite(LEFT_MOTOR_B, HIGH);
  digitalWrite(RIGHT_MOTOR_A, LOW);
  digitalWrite(RIGHT_MOTOR_B, HIGH);
}

void left() {
  digitalWrite(LEFT_MOTOR_A, LOW);
  digitalWrite(LEFT_MOTOR_B, HIGH);
  digitalWrite(RIGHT_MOTOR_A, HIGH);
  digitalWrite(RIGHT_MOTOR_B, LOW);
}

void right() {
  digitalWrite(LEFT_MOTOR_A, HIGH);
  digitalWrite(LEFT_MOTOR_B, LOW);
  digitalWrite(RIGHT_MOTOR_A, LOW);
  digitalWrite(RIGHT_MOTOR_B, HIGH);
}

void stopMotors() {
  digitalWrite(LEFT_MOTOR_A, LOW);
  digitalWrite(LEFT_MOTOR_B, LOW);
  digitalWrite(RIGHT_MOTOR_A, LOW);
  digitalWrite(RIGHT_MOTOR_B, LOW);
}

void kickSnack() {
  kicker.write(90);   // Rotate servo to “kick”
  delay(500);         // Hold position
  kicker.write(0);    // Return servo
}


