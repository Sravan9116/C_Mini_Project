#include <Servo.h>

// === Servo motor objects ===
Servo hipFL;  // Front Left
Servo hipFR;  // Front Right
Servo hipBL;  // Back Left
Servo hipBR;  // Back Right

// === Pin Definitions ===
#define trigPin 12
#define echoPin 13
#define buzzerPin 11

// === Variables ===
long duration;
int distance;

void setup() {
  Serial.begin(9600);

  // Attach servo pins
  hipFL.attach(3);
  hipFR.attach(4);
  hipBL.attach(5);
  hipBR.attach(6);

  // Ultrasonic pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Buzzer pin
  pinMode(buzzerPin, OUTPUT);

  // Initial neutral position
  neutralPose();
  delay(500);
  Serial.println("System Ready!");
}

void loop() {
  distance = getDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > 2 && distance < 20) {
    // Object detected within 20 cm
    Serial.println("Object Detected!");
    meow();
    moveCatFast();
  } else {
    neutralPose();  // No object
  }

  delay(100);
}

// === Measure Distance ===
int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000); // Timeout 30ms
  if (duration == 0) return 999; // No reading (too far)

  int dist = duration * 0.034 / 2;
  return dist;
}

// === Neutral Pose ===
void neutralPose() {
  hipFL.write(90);
  hipFR.write(90);
  hipBL.write(90);
  hipBR.write(90);
}

// === Cat Movement ===
void moveCatFast() {
  hipFL.write(65);
  hipBR.write(65);
  hipFR.write(115);
  hipBL.write(115);
  delay(200);

  neutralPose();
  delay(100);

  hipFR.write(65);
  hipBL.write(65);
  hipFL.write(115);
  hipBR.write(115);
  delay(200);

  neutralPose();
}

// === Meow Sound ===
void meow() {
  digitalWrite(buzzerPin, HIGH);
  delay(100);
  digitalWrite(buzzerPin, LOW);
  delay(80);
  digitalWrite(buzzerPin, HIGH);
  delay(80);
  digitalWrite(buzzerPin, LOW);
}
