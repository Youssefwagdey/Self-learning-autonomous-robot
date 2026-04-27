/**
 * @file Sensor_Sync_Advanced.ino
 * @description اختبار دقة التزامن وحساب الفرق الزمني بين الحساسات
 */

volatile unsigned long t1 = 0;
volatile unsigned long t2 = 0;
volatile bool triggered = false;

void setup() {
  Serial.begin(115200); [cite: 17]
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), [](){ t1 = micros(); triggered = true; }, RISING);
  attachInterrupt(digitalPinToInterrupt(3), [](){ t2 = micros(); triggered = true; }, RISING);
}

void loop() {
  if (triggered) {
    noInterrupts(); // حماية البيانات أثناء القراءة
    unsigned long time1 = t1;
    unsigned long time2 = t2;
    triggered = false;
    interrupts();

    long offset = (long)(time1 - time2);
    Serial.print("Data Alignment Offset: ");
    Serial.print(offset);
    Serial.println(" microseconds"); [cite: 18]
    delay(100); 
  }
}