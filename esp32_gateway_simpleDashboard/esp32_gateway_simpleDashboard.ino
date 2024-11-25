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
float current;                 // Dòng điện (A)
float voltage;                 // Điện áp (V)
float instantaneousPower;      // Công suất tức thời (W)
float totalPower = 0;          // Tổng công suất tiêu thụ (Joules)
unsigned long previousTime = 0; // Thời điểm trước đó (ms)
const unsigned long interval = 1000; // Khoảng thời gian cập nhật (ms)

ERA_CONNECTED() {
    ERA_LOG("ERa", "ERa connected!");
}

/* This function will run every time ERa is disconnected */
ERA_DISCONNECTED() {
    ERA_LOG("ERa", "ERa disconnected!");
}

// Hàm gửi dữ liệu đến ERa IoT Platform
void timerEvent() {
    ERa.virtualWrite(V1, ERaMillis() / 1000L); // Uptime
    ERA_LOG("Timer", "Uptime: %d", ERaMillis() / 1000L);
    ERa.virtualWrite(V15, current);            // Dòng điện
    ERa.virtualWrite(V16, voltage);            // Điện áp
    ERa.virtualWrite(V17, instantaneousPower); // Công suất tức thời
    ERa.virtualWrite(V18, totalPower);         // Tổng công suất tiêu thụ
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
    ERa.addInterval(interval, timerEvent);
}

void loop() {
    ERa.run();

    // Kiểm tra nếu đủ thời gian cập nhật
    unsigned long currentTime = millis();
    if (currentTime - previousTime >= interval) {
        previousTime = currentTime;

        // Sinh giá trị ngẫu nhiên cho dòng điện và điện áp
        current = random(10, 200) / 100.0; // Giá trị từ 0.10A đến 2.00A
        voltage = random(220, 240) / 1.0;   // Giá trị từ 220V đến 240V

        // Tính công suất tức thời
        instantaneousPower = current * voltage;

        // Cộng dồn công suất tức thời vào tổng công suất tiêu thụ
        totalPower += instantaneousPower * (interval / 1000.0); // Joules (W × s)

        // Hiển thị kết quả trên Serial Monitor
        Serial.print("Current: ");
        Serial.print(current);
        Serial.print(" A, Voltage: ");
        Serial.print(voltage);
        Serial.print(" V, Instantaneous Power: ");
        Serial.print(instantaneousPower);
        Serial.print(" W, Total Power Consumption: ");
        Serial.print(totalPower);
        Serial.println(" J (Joules)");
    }
}
