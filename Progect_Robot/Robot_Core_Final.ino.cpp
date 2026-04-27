/**
 * @file Robot_Core_Final.ino
 * @description المزامنة بين الحساسات واتخاذ القرار بناءً على البيانات المدمجة
 */

volatile unsigned long lidarTimestamp = 0;
volatile unsigned long ultraTimestamp = 0;
volatile bool newDataAvailable = false;

unsigned long lastProcess = 0;
const int interval = 100; // تحديث كل 100 ملي ثانية [cite: 1]

void setup() {
  Serial.begin(115200); [cite: 4]
  // استخدام Interrupts بدلاً من الـ Polling لضمان الدقة
  attachInterrupt(digitalPinToInterrupt(2), lidar_ISR, RISING);
  attachInterrupt(digitalPinToInterrupt(3), ultra_ISR, RISING);
}

void loop() {
  if (millis() - lastProcess >= interval) { [cite: 5]
    lastProcess = millis();

    // التحقق من تزامن البيانات (بحد أقصى 10ms فرق)
    if (newDataAvailable && abs((long)(lidarTimestamp - ultraTimestamp)) < 10000) {
      Serial.println("SYNC OK"); [cite: 18]
      
      float lidar = 55.0; // [cite: 2] قيم تجريبية كما في ملفك
      float ultra = 40.0; // [cite: 2]
      float imu = 3.0;    // [cite: 3]
      
      float distance = (lidar + ultra) / 2; [cite: 7]

      if (distance < 20) {
        Serial.println("DECISION: STOP"); [cite: 8]
      } else if (imu > 5) {
        Serial.println("DECISION: TURN RIGHT"); [cite: 9]
      } else {
        Serial.println("DECISION: MOVE FORWARD"); [cite: 10]
      }
      newDataAvailable = false;
    }
  }
}

void lidar_ISR() { lidarTimestamp = micros(); newDataAvailable = true; }
void ultra_ISR() { ultraTimestamp = micros(); newDataAvailable = true; }