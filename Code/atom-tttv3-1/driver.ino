TaskHandle_t th[2];

Servo servo;

const uint8_t cylinderServoPin = 22;
const uint8_t pushSolenoidPin = 19;
const uint8_t pushSolenoidPwmChannel = 15;

const int bottleNum = 9;

//各indexごとのサーボ設定角度を指定
const int offset = 0;
const int angleDiv = 20;
//個々の値を適宜調整してスプレーが押せるように調整してください
const int bottleIndexToAngle[] = {
  offset + 11,
  offset + angleDiv * 1 + 5,
  offset + angleDiv * 2 + 4,
  offset + angleDiv * 3 + 2,
  offset + angleDiv * 4 + 2,
  offset + angleDiv * 5 + 0,
  offset + angleDiv * 6 + 1,
  offset + angleDiv * 7 - 0,
  offset + angleDiv * 8 - 3
};

//順にsalty, sour, sweet, bitter, umami, black, cyan, magenta, yellowに対応
//各味の置く場所を変えた場合はここを変える
const int tasteIndexToBottleIndex[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

//各味のsequence出力順
//0: salty, 1: sour, 2: sweet, 3: bitter, 4: umami, 5: black, 6: cyan, 7: magenta, 8: yellow
const int tasteIndexSequence[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8};

const int solenoidPower = 255;  //0~255 線形では無いかも

void setupDriver() {
  // pinMode(cylinderServoPin, OUTPUT);
  ESP32PWM::allocateTimer(0);
  servo.setPeriodHertz(50);
  servo.attach(cylinderServoPin, 600, 2500);

  pinMode(pushSolenoidPin, OUTPUT);
  ledcSetup(pushSolenoidPwmChannel, 12800, 8);
  ledcAttachPin(pushSolenoidPin, pushSolenoidPwmChannel);

  rotateBottleCylinder(0);
}

void rotateBottleCylinder(int bottleIndex) {
  Serial.print("rotateBottleCylinder: ");
  Serial.println(bottleIndex);

  int angle = bottleIndexToAngle[(bottleIndex + bottleNum) % bottleNum];

  // Atom.SetServoAngle(cylinderServoChannel, angle);
  servo.write(angle);
}

void pushNozzle() {
  pushNozzleTimes(1);
}

int gtimes = 0;

void pushNozzleTimes(int times) {
  Serial.print("pushNozzleTimes: ");
  Serial.println(times);

  gtimes = times;

  //delayするとサーバの応答が止まってしまうので、別コアで処理する
  xTaskCreatePinnedToCore(pushNozzleTimesTask, "pushNozzleTimesTask", 4096, NULL, 2, NULL, 0);
}

void pushNozzleTimesSync(int times) {
  for (int i = 0; i < times; i++) {

    ledcWrite(pushSolenoidPwmChannel, solenoidPower);  //0 ~ 255
    delay(500);
    ledcWrite(pushSolenoidPwmChannel, 0);
    delay(500);
  }
}

void pushNozzleTimesTask(void* timesPointer) {
  //キャストしてポインタからパラメータを取り出し
  int times = gtimes;

  Serial.print("pushNozzleTimesTask times:");
  Serial.println(times);

  pushNozzleTimesSync(times);

  vTaskDelete(NULL);
}

void sequentialPush(int* tastes) {
  for (int i = 0; i < bottleNum; i++) {
    int tasteIndex = tasteIndexSequence[i];
    rotateBottleCylinder(tasteIndexToBottleIndex[tasteIndex]);
    delay(2000);
    pushNozzleTimesSync(tastes[tasteIndex]);
    delay(2000);
  }
}

CRGB color = 0x000000;
void setStatusLED(CRGB _color) {
  color = _color;
  M5.dis.drawpix(0, color);
}


void blinkLED() {
  xTaskCreatePinnedToCore(blinkLEDTask, "blinkLEDTask", 4096, NULL, 2, NULL, 0);
}

void blinkLEDTask(void* param) {
  M5.dis.drawpix(0, 0x000000);
  delay(100);
  M5.dis.drawpix(0, color);
  delay(100);

  M5.dis.drawpix(0, 0x000000);
  delay(100);
  M5.dis.drawpix(0, color);

  vTaskDelete(NULL);
}
