// Motor control pins
#define IN1 7  // Left motor
#define IN2 6
#define IN3 5  // Right motor
#define IN4 4

void setup() {
  Serial.begin(9600);  // For receiving BLE commands from ESP32-C3

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();
    Serial.println(cmd);  // Debugging (optional)

    switch (cmd) {
      case 'F':  // Forward
        analogWrite(IN1, 255); analogWrite(IN2, 0);   // Full left
        analogWrite(IN3, 255); analogWrite(IN4, 0);   // Full right
        break;

      case 'B':  // Backward
        analogWrite(IN1, 0); analogWrite(IN2, 255);   // Full left
        analogWrite(IN3, 0); analogWrite(IN4, 255);   // Full right
        break;

      case 'L':  // Gentle Left Turn (left motor slower)
        analogWrite(IN1, 100); analogWrite(IN2, 0);   // Slow left
        analogWrite(IN3, 255); analogWrite(IN4, 0);   // Full right
        break;

      case 'R':  // Gentle Right Turn (right motor slower)
        analogWrite(IN1, 255); analogWrite(IN2, 0);   // Full left
        analogWrite(IN3, 100); analogWrite(IN4, 0);   // Slow right
        break;

      default:  // Stop
        digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
        break;
    }
  }
}
