#include <PID_v1.h>  // thư viện pid
#include <SimpleKalmanFilter.h>

double Setpoint ;    // điểm đặt
double Input;        // giá trị đầu vào của cam biến ánh sáng
double Output ;      // giá trị đầu ra là tín hiệu điều khiển bóng đèn led

double Kp=4.9, Ki=2.6, Kd=0.03; // các thông số kp,ki,kd các bạn có thể thay đổi

PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
SimpleKalmanFilter locnhieu(2, 2, 0.01);
float gt_doc;
float gt_filter;

void setup()
{
  Serial.begin(9600);   
  Setpoint = 60; // giá trị đặt là 240 , giá trị này các bạn có thể thay đổi
  myPID.SetMode(AUTOMATIC);
  myPID.SetTunings(Kp, Ki, Kd);
  
}
 
void loop()
{
  gt_doc = analogRead(A1);
  gt_filter = locnhieu.updateEstimate(gt_doc);
  Input = map(gt_filter, 0, 1024, 0, 255);  // giá trị chuyển đổi từ 0--1024 tương ứng 0---255
  myPID.Compute();
  analogWrite(6,Output); //chân điều khiển độ sáng của led. 
  Serial.print(Input);
  Serial.print(" ");
  Serial.println(Setpoint);
  delay(500); 
}
