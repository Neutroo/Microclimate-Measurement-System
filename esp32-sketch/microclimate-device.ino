#include <GyverOLED.h>
#include <WiFiMulti.h>
#include <InfluxDbClient.h>
#include <DHT.h>

GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;

#define WIFI_SSID "<your wifi name>"
#define WIFI_PASSWORD "<your wifi password>"

WiFiMulti wifi;

#define INFLUXDB_URL "http://<your influx server ip>:8086"
#define INFLUXDB_TOKEN "<your influx token>"
#define INFLUXDB_ORG "<your org name>"
#define INFLUXDB_BUCKET "<your bucket name>"

InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN);

Point sensor("weather");

DHT dht(18, DHT11);

void setup()
{
  oled.init();
  dht.begin();
  oled.clear();
  
  WiFi.mode(WIFI_STA);
  wifi.addAP(WIFI_SSID, WIFI_PASSWORD);

  oled.setCursor(26, 3);
  oled.print("Connecting...");
  
  while (wifi.run() != WL_CONNECTED)
  {    
    delay(100);
  }

  oled.clear();
  oled.setCursor(38, 3);
  oled.print("Connected");
  oled.setCursor(16, 5);
  oled.print("IP: ");
  oled.print(WiFi.localIP());

  sensor.addTag("device", "esp32");
}

void loop()
{
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  sensor.clearFields();

  sensor.addField("Temperature", temperature);
  sensor.addField("Humidity", humidity);

  oled.setScale(1);

  if (wifi.run() != WL_CONNECTED)
  {
    oled.clear();
    oled.setCursor(10, 3);
    oled.print("Connection lost");
    
    while (wifi.run() != WL_CONNECTED)
    {
      delay(100);
    }
  }
     
  while (!client.writePoint(sensor))
  {
    oled.clear();
    oled.setCursor(0, 2);
    oled.print("InfluxDB write failed: ");
    oled.setCursor(0, 4);

    if (isnan(temperature) || isnan(humidity))
    {
      oled.print("nan values");
      oled.setCursor(0, 7);
      oled.print("Skipping...");

      delay(3500);         
      temperature = dht.readTemperature();
      delay(1500);
      humidity = dht.readHumidity();
        
      sensor.clearFields();

      sensor.addField("Temperature", temperature);
      sensor.addField("Humidity", humidity);
    }
    else
    {
      oled.print(client.getLastErrorMessage());

      while (!client.validateConnection())
      {
        delay(100);
      }

      break;
    }   
  }
  
  oled.clear();
  oled.setCursorXY(30, 0);
  oled.print("Temperature:");
  oled.setCursorXY(30, 36);
  oled.print("Humidity:");
  
  oled.setScale(2);
  oled.setCursorXY(30, 12);
  oled.print(String(temperature, 1) + 'C');
  oled.setCursorXY(30, 48);
  oled.print(String(humidity, 0) + '%');
  
  delay(60000);
}
