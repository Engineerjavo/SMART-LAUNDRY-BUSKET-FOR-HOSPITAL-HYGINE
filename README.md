# Smart Laundry Basket For Hospital Hygiene
## 1. Project Overview
The Automatic Hygiene Laundry Basket is an intelligent, hands-free system designed to enhance hygiene and operational efficiency in hospitals, clinics, and professional laundry facilities. By integrating sensor-driven automation with disinfectant control, the system addresses the critical need for clean, safe, and odor-free handling of laundry in environments where contamination risks are high.

Using an ultrasonic sensor, the basket detects the presence of laundry items and automatically opens its lid, allowing users to deposit laundry without physical contact. Once the items are placed inside, the lid closes automatically, and a relay-controlled disinfectant spray is triggered to sanitize the contents and maintain a hygienic environment.

Key Benefits:
Hands-free operation minimizes direct contact with laundry, reducing the risk of cross-contamination.
Automated lid control ensures smooth, responsive operation.
Disinfectant activation maintains a clean and safe environment by neutralizing bacteria and odors immediately after laundry is deposited.
Ideal for hygiene-critical applications such as hospitals, clinics, and industrial laundry services.
This system combines automation, smart sensing, and hygiene maintenance to deliver a practical and reliable solution for handling laundry in professional settings, ensuring both efficiency and safety.

## 2. System Architecture
The Smart Laundry Basket is built as a sensor-actuator system that automates laundry handling and hygiene. The architecture is designed for hands-free operation in hospitals or hygiene-critical facilities.
Architecture Overview

[Laundry Item Approaches]
                   │
                   
          [Ultrasonic Sensor]
   (Detects presence of laundry)
                   │
                   ▼
     [Microcontroller / Arduino]
        ┌───────────────┐
       │                   │
           ▼               ▼
   [Servo Motor]       [Relay Module]
      Lid opens/         Activates
      closes            Disinfectant Spray

Component Roles
#Ultrasonic Sensor
Detects laundry items approaching or placed in the basket.
Sends a signal to the microcontroller to trigger lid operation.
#Microcontroller (Arduino/ESP32)
Receives sensor signals.
Controls the servo motor to open and close the lid automatically.
Activates the relay module to spray disinfectant after the lid closes.
#Servo Motor
Mechanically opens and closes the lid in response to the microcontroller.
#Relay Module + Disinfectant Pump
Controls the disinfectant spray system.
Ensures the basket remains sanitized after laundry is deposited.
#Operational Flow
Laundry approaches → detected by the ultrasonic sensor.
Microcontroller commands the servo motor → lid opens automatically.
Laundry deposited → lid closes automatically.
Relay triggers → disinfectant spray is released.

## 3. How It Works

The Smart Laundry Basket for Hospital Hygiene operates in a hands-free, automated sequence to ensure hygiene and efficiency:

Step 1: Detect Laundry
An ultrasonic sensor continuously measures the distance in front of the basket.
When laundry is placed near the basket (within a defined range, e.g., 15 cm), the sensor detects it.
The sensor sends a signal to the microcontroller (Arduino/ESP32).

Step 2: Open Lid
Upon detecting laundry, the microcontroller commands the servo motor to rotate and open the lid.
The lid remains open for a short duration to allow the user to deposit laundry safely.

Step 3: Close Lid
After the laundry is deposited (or after the preset time), the microcontroller commands the servo to close the lid automatically.

Step 4: Activate Disinfectant Spray
Once the lid is closed, the microcontroller triggers a relay module.
The relay powers a disinfectant pump, spraying sanitizer to maintain hygiene inside the basket.
After a few seconds, the relay turns off the pump, completing the cycle.

Step 5: Wait for Next Item
The system returns to its idle state, continuously monitoring for the next laundry item.
#Arduino Code
H
#include <Servo.h>

// Pins
Servo lidServo;          // Servo motor for lid
int trigPin = 2;         // Ultrasonic Trigger
int echoPin = 3;         // Ultrasonic Echo
int relayPin = 6;        // Relay controlling disinfectant

// Variables
long duration;
int distance;

void setup() {
  lidServo.attach(9);        // Servo signal pin
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Ensure relay is off
  lidServo.write(0);            // Lid closed initially
  Serial.begin(9600);
}

void loop() {
  // Measure distance using ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // Convert to cm

  Serial.print("Distance: ");
  Serial.println(distance);

  // Check if laundry is detected
  if(distance > 0 && distance <= 15){ // Threshold distance in cm
    lidServo.write(90);   // Open lid
    delay(2000);          // Wait for user to deposit laundry
    lidServo.write(0);    // Close lid
    delay(500);           // Short delay before spraying disinfectant
    digitalWrite(relayPin, HIGH); // Activate disinfectant
    delay(3000);                  // Spray duration
    digitalWrite(relayPin, LOW);  // Turn off spray
  }

  delay(500); // Wait before next measurement
}
#How the Code Works
 
Ultrasonic Sensor Measurement
Trigger sends a short pulse.
Echo measures the time taken for the signal to bounce back.
Distance is calculated in centimeters.
#Lid Control
If the measured distance is within the threshold, the servo opens the lid.
After a fixed delay, the servo closes the lid automatically.
#Disinfectant Control
Relay pin is activated after the lid closes, turning on the disinfectant pump for a fixed time.
Relay turns off automatically, completing the cycle.

## Collaborators
1. Javan Abondo otieno
2. Masika Stephanie- Supervisor
##features
-automatic lid opening
-automatic lead closing
disinfectant liquid contro
-sensor based detection

#technologies
-
arduino uno
ultrasonic sensor
servo motor 5V
relay module 5V
dc mini pump 3V

##installation

smart laundry busket
README.md
code
circuit
images
#future improvements
-
1.mobile app intergration
2.gas odour sensors
3.smart notifications
#AUTHOR
-
JAVAN ABONDO OTIENO

