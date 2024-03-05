#include <Wire.h>
#include <Adafruit_TCS34725.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include<TimerOne.h>
#define enA 5
#define in1 10
#define in2 3
#define tiemcan 7
#define stop_bt A2

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
LiquidCrystal_I2C lcd(0x27,16,2);
int so_luong_do, so_luong_xanh_la, so_luong_xanh_duong;
double dulieu;
Servo servo1;
Servo servo2;


void setup() { 
  Serial.begin(9600);
  Wire.begin();
  tcs.begin();

  servo1.attach(9);  // Chân điều khiển servo 1
  servo2.attach(11);  // Chân điều khiển servo 2


  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(tiemcan, INPUT);
  //khoi tao LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Mo hinh bang tai");
  lcd.setCursor(0,1);
  lcd.print("Dem va phan loai");

}

void loop() { 
  while(digitalRead(stop_bt)) //chay toi khi nao nhan stop
    {
      dung_bang_tai();
      int so_lan = 0;
      while (so_lan == 0)
      {
        chay_bang_tai();  
        if (digitalRead(tiemcan) == 1)
        {
          while(digitalRead(tiemcan) == 1);
          so_lan = 1;
          delay(3000);
          dung_bang_tai(); 
          delay(1000);     
   uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);
  Serial.print(r);
  Serial.print(",");
  Serial.print(g);
  Serial.print(",");
  Serial.println(b);    
  if (r > g && r > b) {  // Nhóm màu đỏ
    so_luong_do += 1;
    servo1.write(90);  
    servo2.write(0);  
    if(so_luong_do == 3){
      so_luong_do = 0;
    }
    
  } else if (g > r && g > b) {  // Nhóm màu xanh lá
    so_luong_xanh_la += 1;
    servo1.write(0);  
    servo2.write(0);  
    if(so_luong_xanh_la == 3){
      so_luong_xanh_la = 0;
    }
  } else if (b > r && b > g) {  // Nhóm màu xanh dương
    so_luong_xanh_duong += 1;
    servo1.write(0);  
    servo2.write(90);  
    if(so_luong_xanh_duong == 3){
      so_luong_xanh_duong = 0;
    }
  }
  else{
    servo1.write(0);  
    servo2.write(0);  
    
  }
        lcd.clear();
        lcd.setCursor(8,0);
        lcd.print("RED:");
        lcd.print(so_luong_do);
        lcd.setCursor(0,1);
        lcd.print(" BLUE:");
        lcd.print(so_luong_xanh_duong);
        lcd.print(" GREEN:");
        lcd.print(so_luong_xanh_la);
        delay(300);
        chay_bang_tai();
          
}
      }
    }
    delay(1000);
}
void chay_bang_tai()
{
  if (Serial.available() > 0) {
  dulieu = Serial.read();
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, dulieu);
  }
  else{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, dulieu);
  }
}

void dung_bang_tai()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  
}
