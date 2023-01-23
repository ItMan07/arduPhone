#include <LiquidCrystal_I2C.h>

// адрес дисплея 0x3f или 0x27
// размер дисплея 16x2 (поддерживаются и другие, например 20x4)
LiquidCrystal_I2C lcd(0x27, 16, 2); // адрес, столбцов, строк

void setupDisplay()
{
    lcd.init();      // инициализация
    lcd.backlight(); // включить подсветку
    lcd.clear();
    lcd.setCursor(0, 0); // столбец 1 строка 0
    lcd.print("ITM technologies");
    lcd.setCursor(0, 1);
    lcd.print(" ArduPhone v1.0");
}

/*      Команды для дисплея:

lcd.print("data");        // вывести (любой тип данных)
lcd.setCursor(1, 2);      // курсор на (столбец, строка)
lcd.clear();              // очистить дисплей
lcd.home();               // аналогично setCursor(0, 0)
lcd.noDisplay();          // отключить отображение
lcd.display();            // включить отображение
lcd.blink();              // мигать курсором на его текущей позиции
lcd.noBlink();            // не мигать
lcd.cursor();             // отобразить курсор
lcd.noCursor();           // скрыть курсор
lcd.scrollDisplayLeft();  // подвинуть экран влево на 1 столбец
lcd.scrollDisplayRight(); // подвинуть экран вправо на 1 столбец
lcd.backlight();          // включить подсветку
lcd.noBacklight();        // выключить подсветку

*/