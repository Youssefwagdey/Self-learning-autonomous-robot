#include "Motor_HAL.h"

// استخدام volatile لضمان قراءة القيم بدقة من الذاكرة أثناء الـ Interrupt
volatile long leftCounter = 0;
volatile long rightCounter = 0;

// دوال الـ Interrupt Service Routine (ISR)
// بتشتغل تلقائياً أول ما الموتور يلف نبضة واحدة
void IRAM_ATTR countLeft() { leftCounter++; }
void IRAM_ATTR countRight() { rightCounter++; }

void Motor_Init() {
    // إعداد دبابيس المواتير كمخارج
    pinMode(L_IN1, OUTPUT); pinMode(L_IN2, OUTPUT);
    pinMode(R_IN3, OUTPUT); pinMode(R_IN4, OUTPUT);

    // إعداد دبابيس الـ Encoder كمداخل مع مقاومة رفع داخلية
    pinMode(L_ENCODER_A, INPUT_PULLUP);
    pinMode(R_ENCODER_A, INPUT_PULLUP);
    
    // ربط الدبابيس بدوال العد (تشتغل مع كل نبضة صاعدة RISING)
    attachInterrupt(digitalPinToInterrupt(L_ENCODER_A), countLeft, RISING);
    attachInterrupt(digitalPinToInterrupt(R_ENCODER_A), countRight, RISING);
}

void Motor_Forward(int speed) {
    analogWrite(L_IN1, speed); digitalWrite(L_IN2, LOW);
    analogWrite(R_IN3, speed); digitalWrite(R_IN4, LOW);
}

void Motor_Backward(int speed) {
    digitalWrite(L_IN1, LOW); analogWrite(L_IN2, speed);
    digitalWrite(R_IN3, LOW); analogWrite(R_IN4, speed);
}

void Motor_Stop() {
    digitalWrite(L_IN1, LOW); digitalWrite(L_IN2, LOW);
    digitalWrite(R_IN3, LOW); digitalWrite(R_IN4, LOW);
}

long getLeftCount() { return leftCounter; }
long getRightCount() { return rightCounter; }
void resetEncoders() { leftCounter = 0; rightCounter = 0; }