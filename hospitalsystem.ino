#include <Servo.h>

Servo myServo;

// Pin definitions
const int trigPin = 10;
const int echoPin = 11;
const int servoPin = 9;
const int pumpRelay = 6;   // relay controlling the pump

long duration;
float distance;

const float threshold = 15.0;

bool cycleRunning = false;   // prevents repeated triggering

// Function to run pump in pulse mode
void runPumpPulse() {

  unsigned long startTime = millis();

  while (millis() - startTime < 10000) {   // run for 10 seconds

    digitalWrite(pumpRelay, LOW);   // Pump ON
    delay(300);

    digitalWrite(pumpRelay, HIGH);  // Pump OFF
    delay(300);
  }

  digitalWrite(pumpRelay, HIGH); // ensure pump is OFF
}

void setup() {

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pumpRelay, OUTPUT);

  digitalWrite(pumpRelay, HIGH); // relay OFF

  myServo.attach(servoPin);
  myServo.write(90); // initial position

  Serial.begin(9600);
}

void loop() {

  // Trigger ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance > 0 && distance <= threshold && !cycleRunning) {

    cycleRunning = true;

    // Open lid
    myServo.write(180);
    delay(4000);   // time to drop clothes

    // Close lid
    myServo.write(90);
    delay(1000);

    // Run disinfectant pump
    runPumpPulse();

    // Allow collection
    delay(5000);
  }

  // Reset system only when person leaves
  if (distance > threshold && cycleRunning) {
    cycleRunning = false;
    Serial.println("System Reset");
  }

  delay(200);
}