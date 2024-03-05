#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

const char* ssid = "";
const char* password = "";

String openWeatherMapApiKey = "8abc699afb41ebfb14b3913e4d627245";

String lat = "16.076667";   // vĩ độ
String lon = "108.222778"; // kinh độ

String lat1 = "15.556898";   // vĩ độ
String lon1 = "108.0368"; // kinh độ

String jsonBuffer;
String jsonBuffer1;
unsigned long lastTime = 0;
unsigned long timerDelay = 10000;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Timer set to 10 seconds (timerDelay variable), it will take 10 seconds before publishing the first reading.");
}

void loop() {
  // Send an HTTP GET request
  if ((millis() - lastTime) > timerDelay) {
    // Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      String serverPath = "http://api.openweathermap.org/data/2.5/weather?lat=" + lat + "&lon=" + lon + "&appid=" + openWeatherMapApiKey;
      String serverPath1 = "http://api.openweathermap.org/data/2.5/weather?lat=" + lat1 + "&lon=" + lon1 + "&appid=" + openWeatherMapApiKey;
      jsonBuffer = httpGETRequest(serverPath.c_str());
      jsonBuffer1 = httpGETRequest(serverPath1.c_str());
      Serial.println(jsonBuffer);
      Serial.println(jsonBuffer1);
      JSONVar myObject = JSON.parse(jsonBuffer);
      JSONVar myObject1 = JSON.parse(jsonBuffer1);

      // JSON.typeof(jsonVar) can be used to get the type of the var
      if (JSON.typeof(myObject) == "undefined" || JSON.typeof(myObject1) == "undefined") {
        Serial.println("Parsing input failed!");
        return;
      }
    
      Serial.print("JSON object = ");
      Serial.println(myObject);
      Serial.print("nhiệt độ kv1: ");
      Serial.println(myObject["main"]["temp"]);
      Serial.print("áp suất kv1: ");
      Serial.println(myObject["main"]["pressure"]);
      Serial.print("độ ẩm kv1: ");
      Serial.println(myObject["main"]["humidity"]);
      Serial.print("tốc độ gió kv1: ");
      Serial.println(myObject["wind"]["speed"]);

      Serial.print("JSON object = ");
      Serial.println(myObject1);
      Serial.print("nhiệt độ kv2: ");
      Serial.println(myObject1["main"]["temp"]);
      Serial.print("áp suất kv2: ");
      Serial.println(myObject1["main"]["pressure"]);
      Serial.print("độ ẩm kv2: ");
      Serial.println(myObject1["main"]["humidity"]);
      Serial.print("tốc độ gió kv2: ");
      Serial.println(myObject1["wind"]["speed"]);

      // So sánh nhiệt độ và hiển thị tên vùng có nhiệt độ cao hơn
      
      double temp1 = static_cast<double>(myObject["main"]["temp"]);
      double temp2 = static_cast<double>(myObject1["main"]["temp"]);
      double humidity1 = static_cast<double>(myObject["main"]["humidity"]);
      double humidity2 = static_cast<double>(myObject1["main"]["humidity"]);

      Serial.print("Kết quả so sánh nhiệt độ 2 khu vực: ");
      if (temp1 > temp2) {
        Serial.println("khu vực 1 có nhiệt độ lớn hơn");
      } else if (temp1 < temp2) {
        Serial.println("khu vực 2 có nhiệt độ lớn hơn");
      } else {
        Serial.println("2 kv có nhiệt độ bằng nhau");
      }
       Serial.print("Kết quả so sánh độ ẩm 2 khu vực: ");
      if (humidity1 > humidity2) {
        Serial.println("khu vực 1 có độ ẩm lớn hơn");
      } else if (humidity1 < humidity2) {
        Serial.println("khu vực 2 có độ ẩm lớn hơn");
      } else {
        Serial.println("2 kv có độ ẩm bằng nhau");
      }


    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your Domain name with URL path or IP address with path
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
