# 1. Home에서 Arduino IDE Download
https://www.arduino.cc/
# 2. setup에서 esp8266 board URL 등록
http://arduino.esp8266.com/stable/package_esp8266com_index.json
# 3. CH341SER download
https://www.wch-ic.com/downloads/ch341ser_exe.html
# 4. Blink Code
```
#define LED D5

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  digitalWrite(LED, HIGH); 
  delay(1000);
  digitalWrite(LED, LOW);
  delay(1000);
}
```
