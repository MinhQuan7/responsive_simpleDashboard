#include <Arduino.h>
#define ERA_LOCATION_VN
// #define ERA_LOCATION_SG

// You should get Auth Token in the ERa App or ERa Dashboard
#define ERA_AUTH_TOKEN "ca614c19-2a5c-4a12-9cd8-895cf754d84e"

#include <ERa.hpp>

#define LED_PIN  2

const char ssid[] = "eoh.io";
const char pass[] = "Eoh@2020";
// Khai báo các biến
float current; // Dòng điện (A)
float voltage; // Điện áp (V)
float power;   // Công suất tiêu thụ (W)

ERA_CONNECTED() {
    ERA_LOG("ERa", "ERa connected!");
}

/* This function will run every time ERa is disconnected */
ERA_DISCONNECTED() {
    ERA_LOG("ERa", "ERa disconnected!");
}

void timerEvent() {
    ERa.virtualWrite(V1, ERaMillis() / 1000L);
    ERA_LOG("Timer", "Uptime: %d", ERaMillis() / 1000L);
    ERa.virtualWrite(V15, current);
    ERa.virtualWrite(V16, voltage);
    ERa.virtualWrite(V17, power);
}


void setup() {
  // Khởi tạo giao tiếp Serial
  Serial.begin(115200);
  #if defined(ERA_DEBUG)
    Serial.begin(115200);
#endif
  Serial.println("ESP32 Power Calculation Simulation");
      ERa.setScanWiFi(true);

    /* Initializing the ERa library. */
    ERa.begin(ssid, pass);

    /* Setup timer called function every second */
    ERa.addInterval(1000L, timerEvent);
}

void loop() {
  ERa.run();
  // Sinh giá trị ngẫu nhiên cho dòng điện và điện áp
  current = random(10, 200) / 100.0; // Giá trị từ 1.00A đến 2.00A
  voltage = random(10, 240) / 1.0;   // Giá trị từ 220V đến 240V
  
  // Tính công suất tiêu thụ
  power = current * voltage;

  // Hiển thị kết quả
  Serial.print("Current: ");
  Serial.print(current);
  Serial.print(" A, Voltage: ");
  Serial.print(voltage);
  Serial.print(" V, Power: ");
  Serial.print(power);
  Serial.println(" W");

  // Chờ 1 giây
  delay(1000);
}
