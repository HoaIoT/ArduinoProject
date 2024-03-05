
int trucX;
int trucY;
const int buttonPin = 2;
//int chanX = A1;
//int chanY = A2;
const int led1=3;
const int led2=4;
const int led3=5;
const int led4=6;
int buttonState = 0;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT); 
  Serial.begin(9600);
  
  
 
}

void loop() {
  
  trucX = analogRead(A1);
  trucY = analogRead(A2);
  
  Serial.println(trucX);
  Serial.println(trucY);
  float sled1 = ( trucX / 4); 
  float sled2 = ( (1024 - trucX) / 4); 
  float sled3 = ( trucY / 4); 
  float sled4 = ( (1024 - trucY) / 4); 
  
  analogWrite(led1, sled1);
  analogWrite(led2, sled2);
  analogWrite(led3, sled3);
  analogWrite(led4, sled4);
  
}
