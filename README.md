# Ultrasonic Distance Sensor Trigger (Arduino)

مشروع أردوينو يستخدم حساس الموجات فوق الصوتية **HC-SR04** لقياس المسافة وتشغيل خرج (LED / Relay / أي حمل) عند اقتراب جسم لمسافة محددة.

---

## فكرة المشروع
- إرسال نبضة Ultrasonic
- استقبال الصدى
- حساب المسافة بالسنتيمتر
- تشغيل مخرج رقمي إذا كانت المسافة أقل من **20 سم**

المشروع آمن ومستقر لأنه يستخدم `pulseIn` مع **timeout** لمنع تعليق البرنامج.

---

## المتطلبات
### الهاردوير
- Arduino (Uno / Mega / Nano)
- حساس Ultrasonic HC-SR04
- LED أو Relay (اختياري)
- مقاومة 220Ω (لو LED)
- أسلاك توصيل

### السوفتوير
- Arduino IDE

---

## التوصيلات
| HC-SR04 | Arduino |
|-------|---------|
| VCC   | 5V      |
| GND   | GND     |
| TRIG  | Pin 2   |
| ECHO  | Pin 3   |

| Output | Arduino |
|-------|---------|
| LED / Relay | Pin 4 |

---

## الكود
```cpp
// تعريف المنافذ
const int trigPin = 2;
const int echoPin = 3;
const int outputPin = 4;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(outputPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  long duration;
  int distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);
  if (duration == 0) {
    digitalWrite(outputPin, LOW);
    return;
  }

  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance > 0 && distance < 20) {
    digitalWrite(outputPin, HIGH);
  } else {
    digitalWrite(outputPin, LOW);
  }

  delay(1000);
}
