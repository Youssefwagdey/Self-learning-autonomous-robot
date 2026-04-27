
void setup() {
  Serial.begin(9600); 

void loop() {
  Serial.println("Hello from Bridge!");
  delay(1000);

  if (Serial.available()) {
    String incoming = Serial.readStringUntil('\n');
    Serial.print("Received: ");
    Serial.println(incoming);
  }
}
