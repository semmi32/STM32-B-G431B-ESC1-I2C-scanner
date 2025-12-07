#include <Wire.h>

void setup() {
  Serial.begin(115200);        // Инициализируем Serial 
  Wire.begin();               // Запускаем I2C-интерфейс
  
  Serial.println("I2C Scanner started...");
}


void loop() {
  byte error, address;
  int nDevices = 0;

  Serial.println("Scanning I2C bus...");

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("Device found at address: 0x");
      if (address < 16) Serial.print("0");  // Добавляем ведущий ноль для адресов < 0x10
      Serial.println(address, HEX);
      nDevices++;
    }
    else if (error == 4) {
      Serial.print("Unknown error at address: 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
    }
  }

  if (nDevices == 0) {
    Serial.println("No I2C devices found on the bus.");
  } else {
    Serial.println("Scan complete.");
  }

  Serial.println();            // Пустая строка для разделения сканирований
  delay(5000);              // Ждём 5 секунд до следующего сканирования
}
