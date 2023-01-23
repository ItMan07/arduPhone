
String sendATCommand(String cmd, bool waiting)
{
  String resp = "";   // Переменная для хранения результата
  Serial.println(cmd); // Дублируем команду в монитор порта
  SIM800.println(cmd); // Отправляем команду модулю

  if (waiting)                  // Если необходимо дождаться ответа...
  {
    resp = waitResponse();     // ... ждем, когда будет передан ответ

    // Если Echo Mode выключен (ATE0), то эти 3 строки можно закомментировать
    if (resp.startsWith(cmd))  // Убираем из ответа дублирующуюся команду
      resp = resp.substring(resp.indexOf("\r", cmd.length()) + 2);

    Serial.println(resp);      // Дублируем ответ в монитор порта
  }
  return resp;                 // Возвращаем результат. Пусто, если проблема
}
