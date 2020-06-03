#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include "U8glib.h"

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE); // I2C / TWI
int pin_buzzer = 4;
int pin_switch = 8;

void beep(){
  // beep
  for (int i = 0; i < 800; i+=8)
  {
    digitalWrite(pin_buzzer, LOW);
    delay(1);
    digitalWrite(pin_buzzer, HIGH);
    delay(1);
  }
}

void showText(float temperature){
  // 顯示
  u8g.firstPage(); 
  do{
    u8g.setFont(u8g_font_fur25);
    u8g.setPrintPos(10, 46);
    u8g.print(temperature, 1);
    u8g.drawStr(80, 46, "\260C"); // "\260C" => 度c
  } while (u8g.nextPage());
}

void showBlank(){
  // 顯示
  u8g.firstPage(); 
  do{
    u8g.drawStr(0, 0, "");
  } while (u8g.nextPage());
}

float getTemperture(){
  // 紀錄溫度
  float preTemperature = 0.0;

  // 紀錄時間
  unsigned long time = millis();
  unsigned long next_time = millis();

  // 若1.5--秒溫度差距小於0.2
  while (next_time-time < 1500){
    // 下一個時間
    next_time = millis();

    // 若放開按鈕則退出
    if (digitalRead(pin_switch) == HIGH) return -99.9;

    // 抓取溫度
    float temperature = mlx.readObjectTempC() + 1.45;


    // 若差距超過0.2, 重新記錄時間
    if (abs(preTemperature - temperature) > 0.2){
      preTemperature = temperature;
      time = next_time;
    }
    
    showText(temperature);
  }

  // 回傳時間
  return preTemperature;
}

void showResult(float temperature){
  // 記錄次數
  int count = 0;

  // 顯示3次
  while (count < 6){
    // 顯示溫度並發出聲音
    if (count % 2 == 0){
      showText(temperature);
      beep();
    }
    
    // 不顯示
    else{
      showBlank();
    }
    
    delay(700);
    count++;
  }
}


void setup() {
  Serial.begin(9600);
  pinMode(pin_buzzer, OUTPUT);
  pinMode(pin_switch, INPUT_PULLUP);

  mlx.begin();  // 開始抓溫度
}

void loop() {
  // 查看是否按下按鈕
  boolean pin_switch_state = digitalRead(pin_switch);

  // 若按下按鈕
  if (pin_switch_state == LOW){
    // 抓取溫度
    float temperature = getTemperture();

    // 若沒有中途放開
    if (temperature >= 0){
      // 顯示結果
      showResult(temperature);
    }
  }
  else{
    // 不顯示
    showBlank();
  }
}
