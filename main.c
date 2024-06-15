const int leftMotorForwardPin = 2;
const int leftMotorBackwardPin = 3;
const int rightMotorForwardPin = 4;
const int rightMotorBackwardPin = 5;
const int leftMotorSpeedPin = 9;
const int rightMotorSpeedPin = 10;

const int mic1pin = A0;
const int mic2pin = A2;

const int sample_window = 3000;
int mic1, mic2;
int mic1_max, mic1_min, mic2_max, mic2_min;
int amp1, amp2, difference;
unsigned long start_time, current_time;

void setup() {
  pinMode(leftMotorForwardPin, OUTPUT);
  pinMode(leftMotorBackwardPin, OUTPUT);
  pinMode(rightMotorForwardPin, OUTPUT);
  pinMode(rightMotorBackwardPin, OUTPUT);
  pinMode(leftMotorSpeedPin, OUTPUT);
  pinMode(rightMotorSpeedPin, OUTPUT);

  digitalWrite(leftMotorSpeedPin, HIGH);
  digitalWrite(rightMotorSpeedPin, HIGH);

  Serial.begin(9600);
}

void loop() {
  sampleMicrophones();

  Serial.print("Mic 1 amplitude: ");
  Serial.print(amp1);
  Serial.print(" | Mic 2 amplitude: ");
  Serial.print(amp2);
  Serial.print(" | Difference = ");
  Serial.println(difference);

  if (difference > 20) {
  //  turnRight();
    driveBackward();
  } else if (difference < -20) {
   // turnLeft();
    driveForward();
  } //else {
    //driveForward();
  //}

  delay(50);
}

void sampleMicrophones() {
  mic1_min = 1023;
  mic1_max = 0;
  mic2_min = 1023;
  mic2_max = 0;

  start_time = millis();
  current_time = millis();
  
  while (millis() - start_time < sample_window) {
    mic1 = analogRead(mic1pin);
    mic2 = analogRead(mic2pin);

    mic1_min = min(mic1, mic1_min);
    mic1_max = max(mic1, mic1_max);
    mic2_min = min(mic2, mic2_min);
    mic2_max = max(mic2, mic2_max);

    current_time = millis();
  }

  amp1 = mic1_max - mic1_min;
  amp2 = mic2_max - mic2_min;
  difference = amp1 - amp2;
}

void driveForward() {
  digitalWrite(leftMotorForwardPin, HIGH);
  digitalWrite(leftMotorBackwardPin, LOW);
  digitalWrite(rightMotorForwardPin, HIGH);
  digitalWrite(rightMotorBackwardPin, LOW);
}

void driveBackward() {
  digitalWrite(leftMotorForwardPin, LOW);
  digitalWrite(leftMotorBackwardPin, HIGH);
  digitalWrite(rightMotorForwardPin, LOW);
  digitalWrite(rightMotorBackwardPin, HIGH);
}

void turnRight() {
  digitalWrite(leftMotorForwardPin, HIGH);
  digitalWrite(leftMotorBackwardPin, LOW);
  digitalWrite(rightMotorForwardPin, LOW);
  digitalWrite(rightMotorBackwardPin, HIGH);
}

void turnLeft() {
  digitalWrite(leftMotorForwardPin, LOW);
  digitalWrite(leftMotorBackwardPin, HIGH);
  digitalWrite(rightMotorForwardPin, HIGH);
  digitalWrite(rightMotorBackwardPin, LOW);
}