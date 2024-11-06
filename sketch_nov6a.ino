// Define pins for Ultrasonic Sensor
const int trigPin = 9;
const int echoPin = 10;

// Define pins for LEDs
const int greenLED = 4;
const int yellowLED = 5;
const int redLED = 6;

// Define pins for Joystick
const int joyX = A0; // X-axis of joystick

// Distance thresholds
int maxDistance = 20;  // Upper threshold (cm)
int midDistance = 10;  // Middle threshold (cm)

// Variables for sensor data
long duration;
int distance;

void setup() {
  // Initialize pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(joyX, INPUT);

  // Start serial communication
  Serial.begin(9600);
}

void loop() {
  // Read joystick position
  int joyValue = analogRead(joyX);

  // Adjust distance thresholds based on joystick input
  // Map joystick range (0 to 1023) to an adjustment range
  int adjustment = map(joyValue, 0, 1023, -5, 5);
  maxDistance = 20 + adjustment;
  midDistance = 10 + adjustment / 2;

  // Measure distance using Ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Calculate distance in cm
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // Display distance and adjusted thresholds
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm, Max Distance: ");
  Serial.print(maxDistance);
  Serial.print(" cm, Mid Distance: ");
  Serial.println(midDistance);

  // Control LEDs based on distance
  if (distance > maxDistance) {
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);
  } 
  else if (distance > midDistance && distance <= maxDistance) {
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, LOW);
  } 
  else if (distance <= midDistance) {
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, HIGH);
  }

  // Add a small delay to stabilize readings
  delay(100);
}

