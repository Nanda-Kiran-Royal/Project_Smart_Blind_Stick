const int waterSensorPin = A0; // Analog input pin for the water sensor
const int trigPin1 = 2;       // Ultrasonic sensor 1 trig pin
const int echoPin1 = 3;       // Ultrasonic sensor 1 echo pin
const int trigPin2 = 4;       // Ultrasonic sensor 2 trig pin
const int echoPin2 = 5;       // Ultrasonic sensor 2 echo pin
const int buzzerPin = 6;      // Digital output pin for the buzzer

const int thresholdDistance = 75; // Threshold distance in centimeters (2 meters = 200 centimeters)

void setup() {
  pinMode(waterSensorPin, INPUT); // Set the water sensor pin as input
  pinMode(trigPin1, OUTPUT);     // Set the ultrasonic sensor 1 trig pin as output
  pinMode(echoPin1, INPUT);      // Set the ultrasonic sensor 1 echo pin as input
  pinMode(trigPin2, OUTPUT);     // Set the ultrasonic sensor 2 trig pin as output
  pinMode(echoPin2, INPUT);      // Set the ultrasonic sensor 2 echo pin as input
  pinMode(buzzerPin, OUTPUT);    // Set the buzzer pin as output
  
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  // Read the analog value from the water sensor
  int waterSensorValue = analogRead(waterSensorPin);

  // Check if water is detected
  if (waterSensorValue < 500) { // Adjust this threshold value according to your sensor
    digitalWrite(buzzerPin, LOW); // Activate the buzzer
    Serial.println("Water detected!"); // Print a message to the Serial Monitor
  } else {
    digitalWrite(buzzerPin, HIGH); // Deactivate the buzzer
  }

  // Measure distance from ultrasonic sensor 1
  long duration1, distance1;
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 * 0.034 / 2;

  // Measure distance from ultrasonic sensor 2
  long duration2, distance2;
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2 * 0.034 / 2;

  // Print the distances on the serial monitor
  Serial.print("Distance 1: ");
  Serial.print(distance1);
  Serial.print(" cm\t");
  Serial.print("Distance 2: ");
  Serial.print(distance2);
  Serial.println(" cm");

  // Check if any of the distances cross the threshold
  if (distance1 < thresholdDistance || distance2 < thresholdDistance) {
    // If threshold is crossed, activate the buzzer
    digitalWrite(buzzerPin, HIGH);
  } else {
    // Otherwise, turn off the buzzer
    digitalWrite(buzzerPin, LOW);
  }

  // Delay before taking the next reading
  delay(100);
}