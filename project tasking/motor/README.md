# 🤖 Cave Exploration Robot - Motor Control Module (IT Standard)

هذا المديول مسؤول عن التحكم في حركة الروبوت واستخلاص بيانات الـ Odometry بدقة عالية.

## 🛠 المواصفات التقنية (Technical Specifications)
- **Architecture**: Modular HAL (Hardware Abstraction Layer).
- **Control System**: PWM for variable speed control.
- **Feedback System**: Built-in Hall Effect Encoders via External Interrupts (Pins 18, 19).
- **Concurrency**: Fully Non-blocking design using `millis()` to support simultaneous LiDAR/Serial processing.

## 📋 النقاط المغطاة (Scope of Work)
1. **Interrupt Management**: التعامل مع نبضات الـ Encoder في الخلفية لضمان عدم فقدان البيانات.
2. **Safety Measures**: توفير وظائف توقف فوري (Immediate Stop) مستقلة.
3. **Data Integrity**: استخدام `volatile` keywords لضمان دقة المتغيرات المشتركة بين الـ Main Loop والـ ISR.
4. **Portability**: سهولة نقل الكود لأي لوحة تحكم أخرى بفضل فصل الـ Pins عن المنطق البرمجي.