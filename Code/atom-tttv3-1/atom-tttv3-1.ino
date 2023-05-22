#include "WiFi.h"
#include <WebServer.h>
#include <uri/UriBraces.h>
#include <ESPmDNS.h>
#include "M5Atom.h"
#include <SPIFFS.h>
#include <ESP32Servo.h>


// サーバー設定ポート80で接続
WebServer server(80);

void setup() {
  SPIFFS.begin();
  M5.begin(true, false, true);
  delay(50);

  // connectWiFi(); //STAモード
  setupAP(); //APモード
  
  setupServer();
  setupDriver();
}

void loop() {
  M5.update();
  server.handleClient();  //クライアントからのアクセス確認
  delay(50);              //遅延時間（ms）
}