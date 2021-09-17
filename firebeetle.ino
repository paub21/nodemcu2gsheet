#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid     = "Gpui";
const char* password = "gena1234";

// You can get the below information from IFTTT applet
String server = "https://maker.ifttt.com";
String evenName = "sensor_data";
String IFTTT_Key = "ch7j-r0W78OtwDPovTi7H4";
String IFTTTUrl = "https://maker.ifttt.com/trigger/sensor_data/with/key/ch7j-r0W78OtwDPovTi7H4";

// simualted data values to be written to google sheet
int value1;
int value2;
int value3;

void setup()
{
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
}

void sendDataToSheet(void)
{
  String url = server + "/trigger/" + evenName + "/with/key/" + IFTTT_Key + "?value1=" + String((int)value1) + "&value2=" + String((int)value2) + "&value3=" + "Class1" ; 

  Serial.print(url);

  HTTPClient http;
  Serial.print("[HTTP] begin... \n");
  http.begin(url); 

  Serial.print("[HTTP] GET... \n");

  int httpCode = http.GET();
  if(httpCode > 0){
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);

    if(httpCode == HTTP_CODE_OK){
      String payload = http.getString();
      Serial.println(payload);
      }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
}

int cnt = 0;
void loop()
{    
    value1 = random(0,10);
    value2 = random(-10,0);
    value3 = cnt;

    sendDataToSheet();
    delay(2000);
    cnt = cnt +1;
}
