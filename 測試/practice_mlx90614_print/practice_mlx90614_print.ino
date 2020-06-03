/*
 * Reference: https://create.arduino.cc/projecthub/SurtrTech/contactless-temperature-sensor-mlx90614-1e7bc7
 */
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include "U8glib.h"

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE); // I2C / TWI

void setup() {
  // put your setup code here, to run once:
  mlx.begin();  // 開始抓溫度
}

void loop() {
  // put your main code here, to run repeatedly:
  float temperature = mlx.readObjectTempC() + 1.45;
  
  u8g.firstPage(); 
  do{
    u8g.setFont(u8g_font_fur25);
    u8g.setPrintPos(10, 46);
    u8g.print(temperature, 1);
    u8g.drawStr(80, 46, "\260C"); // "\260C" => 度c
  } while (u8g.nextPage());
}
