<p align="center"><img src="/docs/logo.svg?sanitize=true&raw=true" width="400"></p>

<hr/>
<p align="center">
Это репо является копией этого https://github.com/ayushsharma82/AsyncElegantOTA с русскоязычным переводом интефейса веб-страницы и сообщений. Ресурс [buy me a coffee](https://www.buymeacoffee.com/) не работает у нас, я убрал его плагин со страницы. Все остальоне как в оригинале. Про то как устроена страница обновления и как ее изменять написано тут https://github.com/ayushsharma82/AsyncElegantOTA/issues/68. Ниже идет практически дословный перевод текста автора оригинальной библиотеки.
</p>
<hr/>

<p align="center">Выпоняет асинхронное обновление через OTA у ESP8266 и ESP32</p>
<p align="center">
AsyncElegantOTA предоставляет красивый интерфейс для загрузки обновлений `.bin` по воздуху в модули ESP с точным статусом и прогрессом, отображаемым в пользовательском интерфейсе. Библиотека показывает текущий процесс загрузки, а после завершения отобразит статус. Эта версия библиотеки использует AsyncWebServer. Спасибо @me-no-dev за прекрасную библиотеку веб-сервера.
</p>

<br>
<br>

<p align="center"><img src="/docs/elegantOtaDemo-ru.gif?raw=true"></p>

<br>
<br>

<h2>Как установить</h2>

###### Ручная установка

Для Windows: Скачать [Репо](https://github.com/S-LABc/AsyncElegantOTA-ru/archive/main.zip) и извлечь .zip в Документы>Arduino>Libraries>{создать папку "AsyncElegantOTA-ru"}

Для Linux: Скачать [Репо](https://github.com/S-LABc/AsyncElegantOTA-ru/archive/main.zip) и извлечь .zip в Sketchbook>Libraries>{создать каталог "AsyncElegantOTA-ru"}

###### Ручная установка через IDE

Скачать [Репо](https://github.com/S-LABc/AsyncElegantOTA-ru/archive/main.zip), Скетч > Подключить библиотеку > Добавить .Zip библиотеку > Вывбрать скаченный файл .zip.

<br>

<h2>Документация</h2>
<p>AsyncElegantOTA — очень простая библиотека, которая выполняет все, что нужно одной строчкой. Честно говоря, это просто библиотека-оболочка, которая внедряет собственную элегантную веб-страницу вместо уродливой страницы загрузки, которая по умолчанию входит в библиотеку Arduino.</p>

 Подключите библиотеку AsyncElegantOTA `#include <AsyncElegantOTA.h>` в начале скетча Arduino.
 
В методе setup() вставьте это - `AsyncElegantOTA.begin(&server);` перед этим - `server.begin();`
 
 Вот и все!
 
 Теперь скопируйте IP адрес из Монитора Порта и перейдите по ссылке `http://<IP адрес>/update` через браузер. Например http://192.168.1.123/update
 
 <br>
 
 #### Дополнительная безопасность:
 
 Если вы хотите добавить логин с паролем на веб-страницу OTA, замените `AsyncElegantOTA.begin(&server);` на `AsyncElegantOTA.begin(&server, "username", "password");`. Это предотвратит несанкционированные запросы веб-страницы и загрузку прошивки на MCU.
 
<br>

<b>Проблема с антивирусом:</b> Если на вашем компьютере установлен антивирус с брандмауэром, индикатор выполнения на веб-странице мгновенно покажет 100% из-за кэширования запросов антивирусом. Для этого нет решения, если вы не хотите отключить антивирус или добавить локальные IP-адреса в исключения. То же самое будет с iOS, Safari, они будут кэшировать исходящие запросы.

<br>

<h2>Руководства</h2>
<p>Руководства для AsyncElegantOTA доступны на RandomNerdTutorials.</p>

<h3>ESP8266</h3> 
<h4>Arduino IDE:</h4>
<p>https://randomnerdtutorials.com/esp8266-nodemcu-ota-over-the-air-arduino/</p>
<h4>PlatformIO (ручной метод):</h4>
<p>https://randomnerdtutorials.com/esp8266-nodemcu-ota-over-the-air-vs-code/</p>
<br>

<h3>ESP32</h3>
<h4>Arduino IDE:</h4>
<p>https://randomnerdtutorials.com/esp32-ota-over-the-air-arduino/</p>
<h4>PlatformIO (ручной метод):</h4>
<p>https://randomnerdtutorials.com/esp32-ota-over-the-air-vs-code/</p>
<br>
<h3>PlatformIO автоматический метод</h3>
<ul>
<li> Скопируйте файл «platformio_upload.py» из этого репозитория в ту же папку, где находится ваш файл platformio.ini.
<li> Установите метод загрузки для вашего проекта в файле platformio.ini:
</ul>

```
extra_scripts = platformio_upload.py
upload_protocol = custom
upload_url = <Ваш URL-адрес для загрузки, например http://192.168.1.123/update>
``` 
<br>
<h2>Примеры</h2>
 
<h3>Для ESP8266:</h3>

```
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA_RU.h>

const char* ssid = "........";
const char* password = "........";

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
    request->send(200, "text/plain", "Hi! I am ESP8266.");
  });

  AsyncElegantOTAru.begin(&server);
  Serial.println("AsyncElegantOTAru запущен");
  
  server.begin();
  Serial.println("HTTP сервер запущен");
}

void loop(void) {
}

```

<br>
<h3>Для ESP32:</h3>

```
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA_RU.h>

const char* ssid = "........";
const char* password = "........";

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
    request->send(200, "text/plain", "Hi! I am ESP32.");
  });

  AsyncElegantOTAru.begin(&server);
  Serial.println("AsyncElegantOTAru запущен");

  server.begin();
  Serial.println("HTTP сервер запущен");
}

void loop(void) {
}

```
