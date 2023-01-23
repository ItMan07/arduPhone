// размеры клавиатуры
#define KP_ROWS 4
#define KP_COLS 4

// пины подключения (по порядку штекера)
byte colPins[KP_COLS] = {7, 6, 5, 4};
byte rowPins[KP_ROWS] = {11, 10, 9, 8};

// массив имён кнопок
char keys[KP_ROWS][KP_COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

#include <SimpleKeypad.h>

SimpleKeypad keypad((char *)keys, rowPins, colPins, KP_ROWS, KP_COLS);

void keyboard()
{
  char key = keypad.getKey();

  if (key)
  {
    Serial.println(key);

    if (key == 'A') // начать набор номера
    {
      Serial.println("Начните набор номера (8 *** *** ****)");

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Enter number:");

      String str_number = "";
      char key2;

      while (1)
      {
        key2 = keypad.getKey(); // обработка нажатия
        if (key2 != '\0')       // если была нажата
        {
          if (key2 == 'B') // если нажата B
          {
            Serial.print("Номер телефона: ");
            Serial.println(str_number);

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Calling to:");
            lcd.setCursor(0, 1);
            lcd.print(str_number);

            sendATCommand("ATD" + str_number, 1);

            break;
          }

          else if (key2 == 'C') // если нажата C
          {
            Serial.println("Ввод прекращен");

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Cancelled");

            str_number = ""; // начать ввод сначала

            break;
          }

          else
          {
            str_number += key2; // прибавить нажатую цифру к номеру
            Serial.println(str_number);

            lcd.setCursor(0, 1);
            lcd.print(str_number);
          }
        }
      }
    }

    else if (key == 'B') // выйти в главное меню
    {
      lcd.clear();
      lcd.setCursor(0, 0); // столбец 1 строка 0
      lcd.print("ITM technologies");
      lcd.setCursor(0, 1);
      lcd.print(" ArduPhone v1.0");
    }

    else if (key == 'C') // готовность модуля совершать звонки
    {
      String _response = sendATCommand("AT+CCALR?", 1);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Ready calls:");
      lcd.setCursor(0, 1);
      lcd.print(_response);
    }

    else if (key == 'D') // качество связи
    {
      String _response = sendATCommand("AT+CSQ", true);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Link quality:");
      lcd.setCursor(0, 1);
      lcd.print(_response);
    }

    else if (key == '*') // принять вызов
    {
      sendATCommand("ATA", true);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Accept call");
    }

    else if (key == '#') // отклонить вызов
    {
      sendATCommand("ATH", true);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Disconnect call");
    }
  }
}
