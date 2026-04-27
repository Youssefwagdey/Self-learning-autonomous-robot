// تعريف مسامير الجنب الشمال (Left Side) 
int enLeft = 11;  // ENB في البروتيس واصل بـ Pin 11
int in3 = 10;     // متوصل بـ Pin 10
int in4 = 12;     // متوصل بـ Pin 12

// تعريف مسامير الجنب اليمين (Right Side) 
int enRight = 6;  // ENA في البروتيس واصل بـ Pin 6
int in1 = 5;      // متوصل بـ Pin 5
int in2 = 7;      // متوصل بـ Pin 7

void setup() {
  // تجهيز المسامير كمخرجات
  pinMode(enLeft, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enRight, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  // إيقاف كل المواتير في البداية
  stopMotors();
}

void loop() {
  directionControl();
  delay(1000);
  speedControl();
  delay(1000);
}

void directionControl() {
  // تشغيل المواتير بأقصى سرعة
  analogWrite(enLeft, 255);
  analogWrite(enRight, 255);

  // حرك كل المواتير للأمام لمدة ثانيتين
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW); 
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW); 
  delay(2000);
  
  // حرك كل المواتير للخلف لمدة ثانيتين
  digitalWrite(in1, LOW); digitalWrite(in2, HIGH); 
  digitalWrite(in3, LOW); digitalWrite(in4, HIGH); 
  delay(2000);
  
  stopMotors();
}

void speedControl() {
  // تحديد اتجاه الحركة للأمام
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);

  // تسارع (PWM)
  for (int i = 0; i < 256; i++) {
    analogWrite(enLeft, i);
    analogWrite(enRight, i);
    delay(20);
  }
  
  // تباطؤ
  for (int i = 255; i >= 0; i--) {
    analogWrite(enLeft, i);
    analogWrite(enRight, i);
    delay(20);
  }
  
  stopMotors();
}

void stopMotors() {
  digitalWrite(in1, LOW); digitalWrite(in2, LOW);
  digitalWrite(in3, LOW); digitalWrite(in4, LOW);
  analogWrite(enLeft, 0);
  analogWrite(enRight, 0);
}