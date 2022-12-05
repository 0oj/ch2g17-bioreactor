#include <WiFi.h> // WiFi control for ESP32
#include <ThingsBoard.h> // ThingsBoard SDK
// WiFi
#define WIFI_AP_NAME "Galaxy Z Flip3 5GD579"
#define WIFI_PASSWORD ""
// See https://thingsboard.io/docs/getting-started-guides/helloworld/
#define TOKEN "XfgfJXrjY8PhThCamEdq"
#define THINGSBOARD_SERVER "demo.thingsboard.io"
WiFiClient espClient; // Initialize ThingsBoard client
ThingsBoard tb(espClient); // Initialize ThingsBoard instance
int status = WL_IDLE_STATUS; // the Wifi radio's status
static uint16_t messageCounter = 0; // count values sent
void InitWiFi()
{
 Serial.println("Connecting to AP ...");
 // attempt to connect to WiFi network
 WiFi.begin(WIFI_AP_NAME, WIFI_PASSWORD);
 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.print(".");
 }
 Serial.println("Connected to AP");
}
void reconnect() {
 // Loop until we're reconnected
 status = WiFi.status();
 if ( status != WL_CONNECTED) {
 WiFi.begin(WIFI_AP_NAME, WIFI_PASSWORD);
 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.print(".");
 }
 Serial.println("Connected to AP");
 }
}
void setup() {
 Serial.begin(115200);
 WiFi.begin(WIFI_AP_NAME, WIFI_PASSWORD);
 InitWiFi();
}
void loop() {
 delay(1000);
 // Reconnect to WiFi, if needed
 if (WiFi.status() != WL_CONNECTED) {
 reconnect();
 return;
 }
 // Reconnect to ThingsBoard, if needed
 if (!tb.connected()) {
 // Connect to the ThingsBoard
 Serial.print("Connecting to: ");
 Serial.print(THINGSBOARD_SERVER);
 Serial.print(" with token ");
 Serial.println(TOKEN);
 if (!tb.connect(THINGSBOARD_SERVER, TOKEN)) {
 Serial.println("Failed to connect");
 return;
 }
 } 
 
 float r = (float)random(1000)/1000.0;
 messageCounter++;
 Serial.print("Sending data...["); 
 Serial.print(messageCounter);
 Serial.print("]: ");
 Serial.println(r);
 
 // Uploads new telemetry to ThingsBoard using MQTT. 
 // See https://thingsboard.io/docs/reference/mqtt-api/#telemetry-upload-api 
 // for more details
 tb.sendTelemetryInt("count", messageCounter); 
 tb.sendTelemetryFloat("randomVal", r);
 // Process messages
 tb.loop(); 
}