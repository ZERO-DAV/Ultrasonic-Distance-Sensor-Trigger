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

}
