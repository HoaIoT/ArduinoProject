#include <Servo.h>
Servo dc_xoay;
Servo dc_nang1;
Servo dc_nang2;
Servo dc_kep;
int val1,val2,val3,val4;    

void setup() 
{
  dc_xoay.attach(9);  
  dc_nang1.attach(6); 
  dc_nang2.attach(5); 
  dc_kep.attach(3); 
  Serial.begin(9600);
}

void loop() 
{
 val1 =114 ; val2 = 128;val3 =68 ; val4 =180 ;motor(); delay(1000);
 val4 =92 ;dc_kep.write(val4); delay(1000);
 for (val2 = 128; val2 >= 63; val2 -= 1) {dc_nang1.write(val2);delay(15);}
 for (val3 = 68; val3 <= 82; val3 += 1) {dc_nang2.write(val3);delay(15);}
 for (val1 = 114; val1 >= 7; val1 -= 1) {dc_xoay.write(val1);delay(15);}
 for (val3 = 68; val3 <= 78; val3 += 1) {dc_nang2.write(val3);delay(15);}
 for (val2 = 63; val2 <= 128; val2 += 1) {dc_nang1.write(val2);delay(15);}
 val4 =180 ;dc_kep.write(val4); delay(1000);
 
 for (val2 = 128; val2 >= 63; val2 -= 1) {dc_nang1.write(val2);delay(15);}
 for (val1 = 7; val1 <= 114; val1 += 1) {dc_xoay.write(val1);delay(15);}  
 for (val2 = 63; val2 <= 128; val2 += 1) {dc_nang1.write(val2);delay(15);}
          
}
void motor()
{
  dc_xoay.write(val1);                  
  dc_nang1.write(val2);           
  dc_nang2.write(val3);   
  dc_kep.write(val4); 
}
  
