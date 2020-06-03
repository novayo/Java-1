/*
 * Reference: http://henrysbench.capnfatz.com/henrys-bench/u8glib-graphics-library-user-guide/u8glib-arduino-oled-tutorial-1-hello-world-on-steroids/
 */

#include "U8glib.h"
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE); // I2C / TWI

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  u8g.firstPage(); 
  do{
    u8g.setFont(u8g_font_unifont);
    u8g.drawStr(0, 20, "Hello World!");
  } while (u8g.nextPage());
}
