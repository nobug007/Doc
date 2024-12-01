#include <ESP8266WiFi.h>
#define LED D5

const char *ssid = "********";
const char *password = "********";
 
WiFiServer server(80);

void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" ");
  Serial.println("=========================");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("=========================");  
  
  server.begin();
  Serial.println("\n웹 서버 시작");
}

void loop() {
  WiFiClient client = server.available();

  if(!client) return;

  Serial.print(" < 페이지 시작");
  client.setTimeout(5000);
  
  String request = client.readStringUntil('\r');
 
  if(request.indexOf("ledon") > -1) {
    digitalWrite(LED, HIGH);
  }
  else if(request.indexOf("ledoff") > -1) {
    digitalWrite(LED, LOW);
  }
  
  client.flush();
  htmlPage(client);
  client.stop();
  Serial.println(" .... 끝> ");
}

void htmlPage(WiFiClient client) {
  client.print("HTTP/1.1 200 OK");
  client.print("Content-Type: text/html\r\n\r\n");
  client.print("<!DOCTYPE HTML>");
  client.print("<html>");
  client.print("<body>");
  client.print("<br>");
  client.print("<h1 align=\"center\">LED On Off Test</h1>");
  client.print("<br>");
  client.print("<a href='/ledon'><h2 align=\"center\">ON</h2></a>");
  client.print("<br>");
  client.print("<a href='/ledoff'><h2 align=\"center\">OFF</h2></a>");
  client.print("<br>");
  client.print("<h2 align=\"center\">");
  client.print("LED Status: ");
  client.print((digitalRead(LED)) ? "ON" : "OFF");
  client.print("</h2>");
  client.print("</body>");
  client.print("</html>");
}
