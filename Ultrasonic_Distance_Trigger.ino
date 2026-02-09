// تعريف المنافذ
const int trigPin = 2;    // إرسال النبضة
const int echoPin = 3;    // استقبال النبضة
const int outputPin = 4;  // المخرج (الذي سيتم تفعيله)

void setup() {
  pinMode(trigPin, OUTPUT); // ضبط الـ Trig كمخرج
  pinMode(echoPin, INPUT);  // ضبط الـ Echo كمدخل
  pinMode(outputPin, OUTPUT);
  Serial.begin(9600);       // لمراقبة المسافة عبر الكمبيوتر
}

void loop() {
  long duration;
  int distance;

  // تنظيف الـ trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // إرسال نبضة صوتية لمدة 10 ميكروثانية
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // قراءة وقت وصول الصدى بالمايكروثانية
duration = pulseIn(echoPin, HIGH, 30000); // 30ms ≈ 5m
if (duration == 0) {
  digitalWrite(outputPin, LOW);
  return;
}

  // حساب المسافة بالسنتيمتر
  distance = duration * 0.034 / 2;

  // عرض المسافة في شاشة المراقبة
  Serial.print("Distance: ");
  Serial.println(distance);

  // شرط التشغيل: إذا كان الجسم على مسافة أقل من 20 سم مثلاً
  if (distance > 0 && distance < 20) { 
    digitalWrite(outputPin, HIGH); // تشغيل المخرج 4
  } else {
    digitalWrite(outputPin, LOW);  // إطفاء المخرج 4
  }

  delay(1000); // تأخير بسيط لاستقرار القراءة
}
