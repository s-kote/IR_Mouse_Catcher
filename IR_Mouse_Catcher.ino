#include <Servo.h>

Servo myServo;  // สร้างอ็อบเจ็กต์ servo

int irPin1 = 13;  // กำหนดพินที่ใช้เชื่อมต่อกับ IR Sensor ตัวแรก เข้ากับพิน 13
int irPin2 = 10;  // กำหนดพินที่ใช้เชื่อมต่อกับ IR Sensor ตัวที่สอง เข้ากับพิน 10
int irValue1;     // ตัวแปรเก็บค่าจาก IR Sensor ตัวแรก
int irValue2;     // ตัวแปรเก็บค่าจาก IR Sensor ตัวที่สอง

void setup() {
  Serial.begin(9600);
  myServo.attach(6);  // เชื่อมต่อ Servo เข้ากับพิน 6
  pinMode(irPin1, INPUT);  // ตั้งค่า IR Pin 1 เป็น Input
  pinMode(irPin2, INPUT);  // ตั้งค่า IR Pin 2 เป็น Input
  myServo.write(0);  // เปิดกรงตั้งแต่เริ่มต้น
}

void loop() {
  // อ่านค่าจาก IR Sensor
  irValue1 = digitalRead(irPin1);  // อ่านค่าจาก IR Sensor ตัวแรก
  irValue2 = digitalRead(irPin2);  // อ่านค่าจาก IR Sensor ตัวที่สอง
  
  // แสดงค่าที่อ่านจาก IR Sensors ใน Serial Monitor
  Serial.print("IR Sensor 1 State: ");
  Serial.println(irValue1);
  Serial.print("IR Sensor 2 State: ");
  Serial.println(irValue2);

  // เมื่อ IR Sensor 1 จับการเคลื่อนไหว (หนูเข้ามา)
  if (irValue1 == HIGH && irValue2 == LOW) {  
    myServo.write(180);  // ปิดกรง (เซอร์โวที่ 180 องศา)
    Serial.println("Mouse Detected! Cage Closed.");
    delay(1000);  // รอ 1 วินาที
  }

  // เมื่อ IR Sensor 2 จับการเคลื่อนไหว (หนูเข้ามาอยู่ด้านในกรง) และ IR Sensor 1 ไม่จับการเคลื่อนไหว
  else if (irValue1 == LOW && irValue2 == HIGH) {  
    myServo.write(0);  // เปิดกรง (เซอร์โวที่ 0 องศา)
    Serial.println("Cage Opened. Waiting for next mouse.");
    delay(1000);  // รอ 1 วินาที
  }

  // เมื่อ IR Sensor 1 และ 2 จับการเคลื่อนไหว (หนูยังอยู่ในกรง)
  else if (irValue1 == HIGH && irValue2 == HIGH) {  
    myServo.write(180);  // เปิดกรง (เซอร์โวที่ 0 องศา)
    Serial.println("Mouse Detected! Cage Closed.");
    delay(1000);  // รอ 1 วินาที
  }

}
