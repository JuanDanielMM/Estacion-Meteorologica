#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

#define USE_SERIAL Serial

int AnalogTemp = A3;
int DigitalTemp = 0;
double Temperature = 0;

int AnalogLight = A6;
int DigitalLight = 0;
int LightLevel =0 ;

int AnalogHum = A0;
int DigitalHum = 0;
int Humidity = 0;


WiFiMulti wifiMulti;

void setup() {

    USE_SERIAL.begin(115200);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    wifiMulti.addAP("Totalplay-0FA5", "0FA577FBkQq8MRys");

}

void loop() {
    DigitalTemp = analogRead(AnalogTemp);     // read the analog value
    Temperature = (DigitalTemp / 4096.0) * 3300 * 0.1;  // 3.3v reference and 12 bits resolution
    DigitalLight = analogRead(AnalogLight);
    LightLevel = map(DigitalLight, 0, 4095, 0, 100);
    DigitalHum = analogRead(AnalogHum);
    Humidity = map(DigitalHum, 0, 4095, 100, 0);

    String parte1 = "{\"query\":\"mutation{createMedicion(Humedad: ";
    String query = parte1 + Humidity + ",Luz: " + LightLevel + ",Temperatura: " + Temperature + "){id}}\"}";
    
    // wait for WiFi connection
    if((wifiMulti.run() == WL_CONNECTED)) {
        Serial.println("Empeiza");
        HTTPClient http;

        USE_SERIAL.print("[HTTP] begin...\n");
        // configure traged server and url
        //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
        http.begin("http://34.125.7.41:8093/graphql/"); //HTTP
        http.addHeader("Content-Type", "application/json");

        USE_SERIAL.print("[HTTP] POST...\n");
        // start connection and send HTTP header
        // WORKING QUERY  MUTATION "{\"query\":\"mutation{createMedicion(Humedad: 600,Luz: 150,Temperatura: 500){id}}\"}"
        Serial.println(query);
        int httpCode = http.POST(query);   //Send the request
        String payload = http.getString();                  //Get the response payload

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] POST... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                USE_SERIAL.println(payload);
                Serial.println("Respuesta OK");
            }
        } else {
            USE_SERIAL.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }

    delay(5000);
}
