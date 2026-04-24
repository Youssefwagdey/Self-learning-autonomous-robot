#ifndef MOTOR_HAL_H
#define MOTOR_HAL_H

#include <Arduino.h>

// --- Pin Mapping (حسب جدول الليدر) ---
#define L_IN1 5
#define L_IN2 4
#define R_IN3 3
#define R_IN4 2

// --- Encoder Pins (Built-in) ---
// تم اختيار 18 و 19 لأنهم يدعموا الـ Interrupt في Arduino Mega
#define L_ENCODER_A 18  
#define R_ENCODER_A 19  

// --- الدوال الأساسية ---
void Motor_Init();                    // تهيئة الأطراف والـ Interrupts
void Motor_Forward(int speed);        // حركة للأمام
void Motor_Backward(int speed);       // حركة للخلف
void Motor_Stop();                    // توقف تام

// --- دوال الـ Encoder لقراءة المسافة ---
long getLeftCount();                  // قراءة نبضات الموتور الشمال
long getRightCount();                 // قراءة نبضات الموتور اليمين
void resetEncoders();                 // تصفير العدادات

#endif