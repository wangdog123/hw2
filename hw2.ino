const int r = 7;
const int g = 8;
const int b = 9.;
const int bt = 2;

int buttonState = HIGH;       // 當前按鈕狀態 (預設HIGH，因為用了PULLUP)
bool buttonpressed = false;   // 上一次的按鈕狀態
int c = 0;                    // 顏色模式
String color ;

int mood = 0;
const int neutralMood = 10;
unsigned long touchedTimer = 0;
unsigned long reducedTimer = 0;
const long unTouchInterval = 5000;
const long reducedInterval = 1000;



void setup() {
  for (int i = 7; i < 10; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(bt, INPUT);   // 使用內建上拉電阻
  Serial.begin(4800);
  
  mood = neutralMood;
}

void loop() {
  showLED(mood);
  buttonState = digitalRead(bt);

  // 偵測「按下去的一瞬間」(HIGH → LOW)
  if (buttonState == LOW && !buttonpressed) {
    mood += 1;
    if (mood > 20)
      mood = 20;  // 循環回到 0
    touchedTimer = millis();
    buttonpressed = true;
    // delay(50); // 去抖動
  }
  if(buttonState == HIGH && buttonpressed)
    buttonpressed = false;

  unsigned long currentTimer = millis();
  if(currentTimer - touchedTimer > unTouchInterval)
  {
    if(currentTimer - reducedTimer > reducedInterval)
    {
      mood -= 1;
      if(mood< 0)
        mood = 0;
      reducedTimer = currentTimer;
    }
  }

  Serial.print("Current Mood: ");
  Serial.println(mood);
}
void showLED(int state){

  float brightnessInterval = 255 / 10.0;
  if(state >= neutralMood)
  {
    analogWrite(r, 255);
    analogWrite(g, brightnessInterval*(state - neutralMood));
    analogWrite(b, 255 - brightnessInterval*(state - neutralMood));
  }
  else
  {
    analogWrite(r, 255 - brightnessInterval*(neutralMood - state)); 
    analogWrite(g, brightnessInterval*(neutralMood - state));
    analogWrite(b, 255);
  }

}
