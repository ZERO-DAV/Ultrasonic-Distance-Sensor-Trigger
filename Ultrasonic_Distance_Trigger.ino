// ================================
// Ultrasonic HC-SR04 Stable Trigger
// ================================

// المنافذ
const int trigPin   = 2;
const int echoPin   = 3;
const int outputPin = 4;

// الإعدادات
const int ON_DISTANCE  = 15;   // يشغّل عند أقل من 15 سم
const int OFF_DISTANCE = 25;   // يطفئ عند أكثر من 25 سم
const int TIMEOUT_US   = 30000; // 30ms ≈ 5m
const int SAMPLES      = 5;    // عدد القراءات للمتوسط

bool outputState = false;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(outputPin, OUTPUT);

  digitalWrite(trigPin, LOW);
  digitalWrite(outputPin, LOW);

  Serial.begin(9600);
}

long readDistanceCM() {
  long duration;
  long sum = 0;
  int valid = 0;

  for (int i = 0; i < SAMPLES; i++) {
    // تنظيف
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // نبضة
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH, TIMEOUT_US);

    if (duration > 0) {
      long d = duration * 0.0343 / 2;
      if (d > 2 && d < 400) { // تجاهل القيم الغريبة
        sum += d;
        valid++;
      }
    }

    delay(20);
  }

  if (valid == 0) return -1; // فشل قراءة
  return sum / valid;        // متوسط
}

void loop() {
  long distance = readDistanceCM();

  if (distance == -1) {
    // فشل الصدى → وضع آمن
    digitalWrite(outputPin, LOW);
    outputState = false;
    Serial.println("No echo");
    delay(100);
    return;
  }

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Hysteresis لمنع التذبذب
  if (!outputState && distance <= ON_DISTANCE) {
    digitalWrite(outputPin, HIGH);
    outputState = true;
  }
  else if (outputState && distance >= OFF_DISTANCE) {
    digitalWrite(outputPin, LOW);
    outputState = false;
  }

  delay(100);
}
