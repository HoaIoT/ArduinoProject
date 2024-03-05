#include <Servo.h>
Servo dc_xoay;
Servo dc_nang1;
Servo dc_nang2;
Servo dc_kep;
  
int bt_xoay = A0; 
int bt_nang1 = A1;
int bt_nang2 = A2;
int bt_kep = A3;
int val1,val2,val3,val4;    

void setup() 
{
  dc_xoay.attach(9);  
  dc_nang1.attach(6); 
  dc_nang2.attach(5); 
  dc_kep.attach(3); 
}

void loop() 
{
  val1 = analogRead(bt_xoay);            
  val1 = map(val1, 0, 1023, 0, 180);     
  dc_xoay.write(val1);                 

  val2 = analogRead(bt_nang1);            
  val2 = map(val2, 0, 1023, 180, 0);     
  dc_nang1.write(val2);        

  val3 = analogRead(bt_nang2);            
  val3 = map(val3, 0, 1023, 180, 0);     
  dc_nang2.write(val3); 

  val4 = analogRead(bt_kep);            
  val4 = map(val4, 0, 1023, 0, 180);     
  dc_kep.write(val4); 





                
}
