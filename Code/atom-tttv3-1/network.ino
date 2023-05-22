

//=======AP Mode===================================
const char ssid_AP[] = "Open-TTTV";  //SSID
const char pass_AP[] = "opentttv";  //パスワード(8文字以上)

const IPAddress ip(192,168,11,2); //IPアドレス
const IPAddress subnet(255,255,255,0); //サブネットマスク

void setupAP(){
  setStatusLED(0xff0000);
  Serial.println("Setting AP...");
  WiFi.softAP(ssid_AP, pass_AP);  //ソフトAP設定

  // IPAddress ip = WiFi.softAPIP();
  WiFi.softAPConfig(ip, ip, subnet);
  
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());

  MDNS.begin("tttv");

  setStatusLED(0x00ff00);
}


//=======STA Mode====================================

//from: https://lang-ship.com/blog/work/esp32-wi-fi-setting/#toc5
void connectWiFi() {
  setStatusLED(0xff0000);

  // シリアル初期化
  Serial.begin(115200);
  // 前回接続時情報で接続する
  Serial.println("WiFi begin");
  WiFi.begin();
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
    // 10秒以上接続できなかったら抜ける
    if (10000 < millis()) {
      break;
    }
  }
  Serial.println("");
  // 未接続の場合にはSmartConfig待受
  if (WiFi.status() != WL_CONNECTED) {

    setStatusLED(0xff6600);
    WiFi.mode(WIFI_STA);
    WiFi.beginSmartConfig();
    Serial.println("Waiting for SmartConfig");
    while (!WiFi.smartConfigDone()) {
      delay(500);
      Serial.print("#");
      // 30秒以上接続できなかったら抜ける
      if (30000 < millis()) {
        Serial.println("");
        Serial.println("Reset");
        ESP.restart();
      }
    }
    // Wi-fi接続
    Serial.println("");
    Serial.println("Waiting for WiFi");
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
      // 60秒以上接続できなかったら抜ける
      if (60000 < millis()) {
        Serial.println("");
        Serial.println("Reset");
        ESP.restart();
      }
    }
    Serial.println("");
    Serial.println("WiFi Connected.");
  }
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());

  MDNS.begin("tttv");

  setStatusLED(0x00ff00);
}
