const int trigPin = 6;
const int echoPin = 7;

float duration, distance;

unsigned long timerStart = 0;
const unsigned long timerLength = 90000; // 90 seconds

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.0343) / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  // If object is close, reset timer
  if (distance <= 20) {
    timerStart = millis();   // reset timer
    Serial.println("Timer reset to 90 seconds");
  }

  // Calculate time left
  unsigned long elapsed = millis() - timerStart;
  unsigned long timeLeft = (timerLength - elapsed) / 1000;

  if (distance > 20 && elapsed < timerLength) {
    Serial.print("Time left: ");
    Serial.print(timeLeft);
    Serial.println(" seconds");
  }

  if (elapsed >= timerLength) { //If statement that runs when the timer has reached 90 seconds of a distance above 20cm 
    Serial.println("Timer finished"); //prints a sentence that tells when timer has reached 90 seconds of a distance above 20cm
  }

  delay(200); //A small delay that ensures accuracy in the read values.
}

