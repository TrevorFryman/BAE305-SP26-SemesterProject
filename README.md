 # Semester Project Online Design File

 **Group Members:**
   * Gretchen Wahoff
   * Jasmyne Huynh
   * Emily Culver
   * Cole Crumbaker
   * Trevor Fryman
     
# Summary
Unattended cooking is the leading cause of house fires in the US. Roughly 70% of people admit to leaving the kitchen unattended while cooking. There is also a risk of harm to children, energy waste, accidental gas leaks, or electrical overheating. ​

The purpose of this project was to create a system with automatic detection and shut-off to reduce preventable hazards and unnecessary energy consumption. We decided that to achieve this, our system should detect whether a pan is on the stovetop and turn it off when it isn't, and also be capable of turning the stove off after a set timer runs out. To better allow the user to understand the system, a green LED will be on when a pan is detected, and a red LED will blink and stay on when the system has turned the stove off. 

The design objectives that were set for this project are as follows;
- The end user may set a timer to turn off the stove top burner after a period.
- The product can successfully turn off a stove top burner if no motion is detected for a certain period.
- The product can successfully turn off a stove top burner from any position its knob is set to.
- The product displays a visual indication of a pot/ pan being detected.
- The product displays a visual indication of the hot plate turning off.


This project allowed us to practice and demonstrate a variety of engineering skills, such as wiring, coding, scrum, and team collaboration. 

Project Video Description: 

# Design Description
Engineering Drawings, code, and assembly instructions are complete and correct

<p align="center">
<img width="800" height="600" alt="image" src="https://github.com/user-attachments/assets/1b114d6f-ee6c-4344-8506-00b20bf07833" /> <br>
<em>Figure 1. Circuit schematic.<em>
<p>

<p align="center">
<img width="800" height="600" alt="Screenshot 2026-04-16 at 4 32 32 PM" src="https://github.com/user-attachments/assets/bc0cc32b-d25f-4fbf-b44f-cc24b090dd3f" /> <br>
<em>Figure 2. Wiring Diagram <em>
<p>

``` cpp
#include <Servo.h>

// 1. PIN DEFINITIONS
const int trigPin = 9;
const int echoPin = 10;
const int buttonPin = 2;      // Select/Start Timer
const int drokTriggerPin = 7;  // Pulse to Drok Trigger High
const int drokDonePin = 3;     // Feedback from Drok Relay (COM/NO)
const int potPin = A0;
const int servoPin = 6;
const int panLed = 13;         // Green (Pan detected)
const int warningLed = 12;     // Red (Timer/Safety alert)

// 2. CONSTANTS & VARIABLES
const int panThreshold = 10;         // Distance in cm to detect pan
const unsigned long safetyTimeout = 90000; // 90 second safety cutoff
Servo knobServo;
unsigned long lastPanDetectedTime = 0;
bool isTimerActive = false;

float duration, distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(drokDonePin, INPUT_PULLUP); // LOW when Drok relay is active
  pinMode(drokTriggerPin, OUTPUT);
  pinMode(panLed, OUTPUT);
  pinMode(warningLed, OUTPUT);
  
  knobServo.attach(servoPin);
  knobServo.write(0); // Start in the OFF position
  Serial.begin(9600);
}

void loop() {
  // Read distance from ultrasonic sensor
  // 1. USE ONLY THE HELPER FUNCTION 
  long currentDistance = getDistance(); 
  
  // 2. IGNORE ZERO (Distance must be greater than 0 to be a real pan)
  bool panPresent = (currentDistance > 0 && currentDistance < panThreshold);

  // 3. CLEAN UP SERIAL PRINT
  Serial.print("Distance: ");
  Serial.print(currentDistance);
  Serial.println(" cm");
  
  // Read manual heat setting from potentiometer
  int potValue = analogRead(potPin);
  int targetAngle = map(potValue, 0, 1023, 0, 180);

  // Check if User starts the Drok Timer
  if (digitalRead(buttonPin) == LOW) {
    digitalWrite(drokTriggerPin, HIGH);
    delay(200); // Send trigger pulse
    digitalWrite(drokTriggerPin, LOW);
    isTimerActive = true;
  }

  // --- LOGIC HIERARCHY ---
  
  // Priority 1: Drok Timer finished
  if (isTimerActive && digitalRead(drokDonePin) == HIGH) {
    shutdownSequence();
    isTimerActive = false;
  } 
  // Priority 2: Pan is present (Normal Operation)
  else if (panPresent) {
    lastPanDetectedTime = millis(); // Reset safety clock
    digitalWrite(panLed, HIGH);
    digitalWrite(warningLed, LOW);
    knobServo.write(targetAngle);
  } 
  // Priority 3: Pan missing for > 90 seconds (Safety Cutoff)
  else if (!panPresent && (millis() - lastPanDetectedTime > safetyTimeout)) {
    shutdownSequence();
  } 
  // Priority 4: Pan missing but within the 90s grace period
  else {
    digitalWrite(panLed, LOW);
    knobServo.write(targetAngle);
  }
  delay(100);
}

// HELPER: Measure distance via HC-SR04
long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

// HELPER: Turn off heat and blink warning
void shutdownSequence() {
  knobServo.write(0);      // Force knob to OFF
  digitalWrite(panLed, LOW); 
  
  // 1. Blink the warning LED 10 times
  for (int i = 0; i < 10; i++) {
    digitalWrite(warningLed, HIGH);
    delay(200);
    digitalWrite(warningLed, LOW);
    delay(200);
  }

  // 2. HARD LOCKOUT: Wait here until the user resets the knob to zero
  // This prevents the hotplate from jumping back to life unexpectedly.
  while (analogRead(potPin) > 10) { 
    // Keep the red LED on solid to show it's waiting for a reset
    digitalWrite(warningLed, HIGH); 
    
    // Optional: Print to Serial so you can see what's happening on your computer
    Serial.println("SAFETY LOCK: Turn potentiometer to 0 to reset.");
    delay(100); 
  }
  
  // 3. Reset successful
  digitalWrite(warningLed, LOW); // Turn off the warning light
  lastPanDetectedTime = millis(); // Reset the safety clock for a fresh start
}
```
<p align="center">
<em>The code above is our fully integrated code for all of our system components. This code runs our timer, moves the servo according to the rotation of the potentiometer, and it activates the ultrasonic sensor detection.<em>
<p>

# Testing Description
All test equipment (model numbers) and procedures are fully described
Test equipment:
- Our system
- A pot or pan
- A phone timer
  
A series of tests was conducted to verify that our system works properly. To start off, we tested the timer mechanism by putting our pot in place and turning the knob on the front of the control board to turn the burner on. Once this was done, we set and started our timer. We also started a phone timer to see if our system timer is accurate. Once a series of ten tests is finished, we move on to the next set of tests. For these tests, we verified that the ultrasonic sensor worked properly. In order to do this, we set a pot on the burner for 10 seconds and then removed it and started a timer on a phone to verify that the burner would not turn off for 90 seconds. 


# Design Decision Discussion

We chose our design decisions based on the goals of reliability, user ease, and safety.

**Capabilities:**  We chose to focus on a single-burner to test and display the concept of our system. The system has four capabilities: manual heat control, a user-set timer, pan detection, and an automatic safety cutoff. The safety lockout feature (requiring the knob to be physically returned to zero) was a feature we added to prevent the stove from unexpectedly turning back on after a safety event and require the user to acknowledge the triggering of the safety system.

**Sensors:** We selected the ultrasonic sensor for the pan detection. We chose this over a weight sensor or an infrared sensor because it is non-contact, inexpensive, and unaffected by the heat or weight of the stovetop. The 10cm threshold was determined through testing to reliably detect a pan directly on the burner while ignoring objects farther away. We added a button for the user to start the timer to make it simple and intentional. 

**Displays:** We used a simple green and red LED system for user feedback. This decision was made to keep the interface simple and intuitive. A green light indicates that the system sees the pan and is active. A blinking red light is used as a warning signal, telling the user that the burner has been turned off for a safety reason.

**Wiring & Integration:** A single Arduino was enough for our system. The key design challenge was integrating all of the pieces of our system. We chose an external timer module rather than coding the timer to increase the ease for the end user, and add the visual indication of the timer. 


# Test Results Discussion 
Both tests were important for the correct function of our system. For the timer, we realized we needed to make the timer longer than the original 2.45 seconds we had it set for. We decided to change it to 15 seconds. For the ultrasonic sensor, we also realized that 90 seconds is a long wait for demonstration purposes, so we shortened that time to 15 seconds as well. We also ran into some issues with our code, wiring, and the battery pack providing a low voltage. Once all of these bugs were worked out, we had a successfully working system. 

# Testing Results
Proper test results were conducted, and the results were clearly documented
<img width="1420" height="486" alt="image" src="https://github.com/user-attachments/assets/a8a017c7-155a-44ed-b893-b589fe421ea3" />

_Figure 3: Test documentation with results and description of what was changed._ 

