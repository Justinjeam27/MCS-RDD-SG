#include <Servo.h>

const int trigPin = 9;
const int echoPin = 10;
const int ledPin1 = 2;
const int ledPin2 = 3;
const int ledPin3 = 4;
const int servoPin = 11;

Servo myServo;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  myServo.attach(servoPin);
  Serial.begin(9600);
}

void loop() {
  // Measure distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  
  Serial.print("Distance: ");
  Serial.println(distance);
  
  // Control LEDs based on distance
  if (distance < 25) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
  } else if (distance >= 25 && distance <= 100) {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, HIGH);
  } else {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
  }

  // Map the distance to a servo angle (0-180 degrees)
  int angle = map(distance, 25, 100, 0, 180);
  angle = constrain(angle, 0, 180); // Ensure the angle is within 0-180
  myServo.write(angle);
  
  delay(100); // Wait for 100 milliseconds before the next loop
}