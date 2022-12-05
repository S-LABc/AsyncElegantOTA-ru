 /*
  AsyncElegantOTA Demo Example - Этот пример будет работать как для микроконтроллеров ESP8266, так и для ESP32.
  -----
  Автор: Ayush Sharma ( https://github.com/ayushsharma82 )
  Перевод: Скляр Роман ( https://github.com/S-LABc )
  
  Важное примечание: отметьте репозиторий на Github, если вам нравится библиотека! :)
  оригинал - https://github.com/ayushsharma82/AsyncElegantOTA
  русский - https://github.com/S-LABc/AsyncElegantOTA-ru
*/

#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h> // https://github.com/me-no-dev/ESPAsyncTCP
#elif defined(ESP32)
  #include <WiFi.h>
  #include <AsyncTCP.h> // https://github.com/me-no-dev/AsyncTCP
#endif

#include <ESPAsyncWebServer.h> // https://github.com/me-no-dev/ESPAsyncWebServer
#include <AsyncElegantOTA_RU.h>

const char* ssid = "........"; // Имя сети WiFi
const char* password = "........"; // Пароль сети WiFi

AsyncWebServer server(80);

void setup(void) {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println();

  // Ожидание подключения
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Подключен к: ");
  Serial.println(ssid);
  Serial.print("IP адрес: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html", "<!DOCTYPE html><html><meta http-equiv=\"Content-type\"content=\"text/html;charset=utf-8\"><body><div>Привет! Это образец ответа AsyncWebServer. Добавь /update в конец адресной строки браузера. Или перейдите по <a href=\"/update\">ссылке</a></div></body></html>");
  });

  AsyncElegantOTAru.begin(&server);
  Serial.println("AsyncElegantOTAru запущен");

  server.begin();
  Serial.println("HTTP сервер запущен");
}

void loop(void) {
}
