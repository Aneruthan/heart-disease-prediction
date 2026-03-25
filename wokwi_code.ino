#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }

  Serial.println("Connected!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    http.begin("http://tomas-intergalactic-eliz.ngrok-free.dev/predict");//your link

    // 🔥 THIS LINE FIXES 307 REDIRECT
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);

    http.addHeader("Content-Type", "application/json");
    http.setTimeout(10000);

    String json = "{";
    json += "\"male\":1,";
    json += "\"age\":45,";
    json += "\"education\":2,";
    json += "\"currentSmoker\":1,";
    json += "\"cigsPerDay\":20,";
    json += "\"BPMeds\":0,";
    json += "\"prevalentStroke\":0,";
    json += "\"prevalentHyp\":1,";
    json += "\"diabetes\":0,";
    json += "\"totChol\":200,";
    json += "\"sysBP\":130,";
    json += "\"diaBP\":80,";
    json += "\"BMI\":25,";
    json += "\"heartRate\":75,";
    json += "\"glucose\":85";
    json += "}";

    int response = http.POST(json);

    Serial.print("Response Code: ");
    Serial.println(response);

    if (response > 0) {
      String res = http.getString();
      Serial.println(res);
    } else {
      Serial.println("Error in request ❌");
    }

    http.end();
  }

  delay(5000);
}