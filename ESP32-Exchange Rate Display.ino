#define LDR_PIN 2
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
const char* server = "http://api.exchangerate.host/latest?base=TND&symbols=USD,EUR,CZK";
float USD,EUR;
const char* date;
const char* ssid = "";
const char* password = "";
String myApikey="Get your own Api";
void setup() {
  Serial.begin(115200);
   WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  } 
 Serial.println("Connected to the WiFi network"); 
  pinMode(LDR_PIN, INPUT);
  lcd.init();
  lcd.backlight();
}

void loop() {
  Tauxdechange(date,USD,EUR) ;
  WiFiClient client;
  HTTPClient http;
  if (http.begin(client, server)) {  
  http.addHeader("content-type","application/json"); 
  String httpRequestData = "{\"api_key\":\"" + myApikey + "\"}";           
  int httpResponseCode = http.GET() ;

  String jsonfile = http.getString();
  Serial.println(jsonfile);
  DynamicJsonDocument doc(512);

  deserializeJson(doc,jsonfile);
    USD = doc["rates"]["USD"];
    EUR = doc["rates"]["EUR"];
  const char* date=doc["date"];
  Tauxdechange(date,USD,EUR);
 
  }
}

void Tauxdechange(const char* date,float USD, float EUR) { 
 lcd.setCursor(1, 0);
  lcd.print("FST:Taux de change");
  lcd.setCursor(2, 1);
  lcd.print("date:");
  lcd.print(date);
  lcd.setCursor(2,2);
  lcd.print("USD:");
  lcd.print(USD);
  lcd.setCursor(2, 3);
  lcd.print("EUR:");
  lcd.print(EUR);

  delay(5000);
  }
