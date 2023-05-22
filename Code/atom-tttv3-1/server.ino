
void setupServer() {
  // サーバー設定
  server.on("/", handleRoot);
  server.on(UriBraces("/assets/{}"), handleAssets);

  server.on("/api/ping", handlePing);
  server.on("/api/rotate", handleRotate); //param: bottle:1~N
  server.on("/api/push", handlePush);
  server.on("/api/sequence", handleSequence);
  server.onNotFound(handleNotFound);
  server.begin();
}


//-------------------------------------------------
// サーバーリクエスト時処理関数
//-------------------------------------------------
// ルートアクセス時の応答関数
void handleRoot() {
  handleFileRead("/index.html");
  blinkLED();
}

void handleAssets(){
  blinkLED();

  String path = server.uri();
  if(handleFileRead(path) == 0){
    //ファイルあった
    return;
  }

  handleError();
}

// エラー（Webページが見つからない）時の応答関数
void handleNotFound() {
  blinkLED();

  
  server.send(404, "text/plain", "404 Not Found!");  //text送信
  blinkLED();
}

void handlePing(){  
  handleOk();
  blinkLED();
}

void handleRotate(){
  blinkLED();
  
  if(server.hasArg("bottle")){
    String indexStr = server.arg("bottle");

    int index = indexStr.toInt();
    
    if(index != 0){
      rotateBottleCylinder(index - 1);
      handleOk();
      return;
    }
  }

  handleError();
}

void handlePush(){
  blinkLED();

  if(server.hasArg("times")){
    String timesStr = server.arg("times");
    int times = timesStr.toInt();
    
    if(times != 0){
      pushNozzleTimes(times);
      handleOk();
      return;
    }
  }else{
    pushNozzle();
    handleOk();
    return;
  }

  handleError();
}

void handleSequence(){
  blinkLED();

  if(server.hasArg("salty") || server.hasArg("sour") || server.hasArg("sweet") || server.hasArg("bitter") || server.hasArg("umami") || server.hasArg("black") || server.hasArg("cyan") || server.hasArg("magenta") || server.hasArg("yellow")){
    int tastes[] = {
      constrain(server.arg("salty").toInt(), 0, 10),
      constrain(server.arg("sour").toInt(), 0, 10),
      constrain(server.arg("sweet").toInt(), 0, 10),
      constrain(server.arg("bitter").toInt(), 0, 10),
      constrain(server.arg("umami").toInt(), 0, 10),
      constrain(server.arg("black").toInt(), 0, 10),
      constrain(server.arg("cyan").toInt(), 0, 10),
      constrain(server.arg("magenta").toInt(), 0, 10),
      constrain(server.arg("yellow").toInt(), 0, 10),       
    };
    
    sequentialPush(tastes);
    handleOk();
    
  }
  handleError();
}



void handleOk(){
  server.send(200, "text/plain", "ok");
}

void handleError(){
  server.send(400, "text/plain", "bad request");
}

int handleFileRead(String path) {
  Serial.print("handleFile: ");
  Serial.println(path);

  // ファイルのMIMEタイプを取得
  String contentType = getContentType(path);
  // SPIFFSにファイルが存在するか確認
  if (SPIFFS.exists(path)) {
    Serial.println("exist");
    // ファイルを読み込む
    File file = SPIFFS.open(path, "r");
    // cache設定
    server.sendHeader("Cache-Control", "public, max-age=86400");
    // 読み込んだファイルをブラウザ側に返す
    size_t sent = server.streamFile(file, contentType);
    // ファイルクローズ
    file.close();

    return 0;
  }else{
    Serial.println("not exist");

    return 1;
  }
}


//  MIMEタイプを推定
String getContentType(String filename) {
  if (server.hasArg("download")) return "application/octet-stream";
  else if (filename.endsWith(".htm")) return "text/html";
  else if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".png")) return "image/png";
  else if (filename.endsWith(".gif")) return "image/gif";
  else if (filename.endsWith(".jpg")) return "image/jpeg";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  else if (filename.endsWith(".xml")) return "text/xml";
  else if (filename.endsWith(".pdf")) return "application/x-pdf";
  else if (filename.endsWith(".zip")) return "application/x-zip";
  else if (filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}


