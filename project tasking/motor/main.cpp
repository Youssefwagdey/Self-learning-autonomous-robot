#include "Motor_HAL.h"

unsigned long lastLogTime = 0;
const int logInterval = 100; // تحديث البيانات كل 100 ملي ثانية

void setup() {
    Serial.begin(115200); // سرعة عالية للتواصل مع الـ ESP32 والـ LiDAR
    Motor_Init();
    resetEncoders();
    Serial.println("Robot System Online: Motor HAL & Encoders Ready.");
}

void loop() {
    unsigned long currentMillis = millis();

    // تشغيل الروبوت (مثال: يتحرك للأمام)
    Motor_Forward(180);

    // --- نظام الـ Non-blocking ---
    // الكود هنا بيلف بسرعة وبيدخل ينفذ اللي جوه الـ if كل 100ms بس
    if (currentMillis - lastLogTime >= logInterval) {
        lastLogTime = currentMillis;

        // طباعة بيانات الـ Encoder (المسافة المقطوعة)
        Serial.print("Encoder Data -> Left: ");
        Serial.print(getLeftCount());
        Serial.print(" | Right: ");
        Serial.println(getRightCount());

        // هنا تقدري تضيفي كود استقبال داتا الـ LiDAR من الـ ESP32
    }
}