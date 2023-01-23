#include <Arduino.h>
#include <SoftwareSerial.h> // Библиотека програмной реализации обмена по UART-протоколу

#include "config.h"
#include "display.h"

SoftwareSerial SIM800(RX_PIN, TX_PIN); // RX, TX

String _response = ""; // Переменная для хранения ответа модуля
void setup()
{
  Serial.begin(SERIAL_SPEED);  // Скорость обмена данными с компьютером
  SIM800.begin(SIM800L_SPEED); // Скорость обмена данными с модемом
  Serial.println("Start!");

  setupDisplay();
}

#include "waitResponse.h"
#include "sendATCommand.h"
#include "keyboard.h"

void setupSIM800L()
{
  Serial.println("[INFO] Настройка модуля SIM800L...");

  sendATCommand("AT", 1); // Отправили AT для настройки скорости обмена данными
  // sendATCommand("ATE0V0+CMEE=1;&W", 1); // отключенный Echo Mode (ATE0), цифровой формат ответов модуля (ATV0) и цифровой код ошибок (AT+CMEE=1)
  // sendATCommand("ATE0V1+CMEE=2;&W", 1); // Echo Mode (ATE0), текстовый формат ответов модуля (ATV1) и текстовый код ошибок (AT+CMEE=2)
  // sendATCommand("AT+CMGF=1;&W", 1);        // Включить TextMode для SMS
  // sendATCommand("AT+DDET=1;&W", 1);        // Включаем DTMF
  // sendATCommand("AT+CLIP=1;&W", 1);        // АОН
  sendATCommand("AT+CSQ", 1);

  Serial.println("[INFO] Настройка модуля завершена");
}

void loop()
{
  keyboard();

  static bool flag;
  if (millis() > 500 && flag == 0)
  {
    setupSIM800L();
    flag = 1;
  }

  if (SIM800.available())
  {                             // Если модем, что-то отправил...
    _response = waitResponse(); // Получаем ответ от модема для анализа
    _response.trim();           // Убираем лишние пробелы в начале и конце
    Serial.println(_response);  // Если нужно выводим в монитор порта

    if (_response.startsWith("RING"))
    {                                                  // Есть входящий вызов
      int phoneindex = _response.indexOf("+CLIP: \""); // Есть ли информация об определении номера, если да, то phoneindex>-1
      String innerPhone = "";                          // Переменная для хранения определенного номера
      if (phoneindex >= 0)
      {                                                                                    // Если информация была найдена
        phoneindex += 8;                                                                   // Парсим строку и ...
        innerPhone = _response.substring(phoneindex, _response.indexOf("\"", phoneindex)); // ...получаем номер
        Serial.println("[INFO] Входящий вызов!");
        Serial.println("Номер: " + innerPhone); // Выводим номер в монитор порта

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Incoming call");
        lcd.setCursor(0, 1);
        lcd.print(innerPhone);
      }
      // Проверяем, чтобы длина номера была больше 6 цифр, и номер должен быть в списке
      // if (innerPhone.length() >= 7)
    }
  }
  if (Serial.available())
    sendATCommand(Serial.readString(), true);

  static uint32_t timer;
  if (millis() - timer >= 500)
  {
    digitalWrite(13, !digitalRead(13));
    timer = millis();
  }
}
