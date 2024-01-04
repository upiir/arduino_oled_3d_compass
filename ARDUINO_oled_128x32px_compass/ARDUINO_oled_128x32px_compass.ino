// simple project using Arduino UNO and 128x32 SSD1306 IIC OLED Display to show compass (driven by potentiometer)

// created by upir, 2024
// youtube channel: https://www.youtube.com/upir_upir

// YOUTUBE VIDEO: https://youtu.be/q1HzAcj0n7Y
// SOURCE FILES: https://github.com/upiir/arduino_oled_3d_compass
// WOKWI PROJECT: https://wokwi.com/projects/385987811439126529

// Links from the video:
// starting wokwi project: https://wokwi.com/projects/371852029526395905
// 10K Potentiometer: https://s.click.aliexpress.com/e/_Dk1WFoV
// 128x64 SSD1306 OLED Display 1.54": https://s.click.aliexpress.com/e/_DCYdWXb
// 128x64 SSD1306 OLED Display 0.96": https://s.click.aliexpress.com/e/_DCKdvnh
// 128x64 SSD1306 OLED Display 2.42": https://s.click.aliexpress.com/e/_DFdMoTh
// Breadboard wires: https://s.click.aliexpress.com/e/_Dkbngin
// Arduino UNO: https://s.click.aliexpress.com/e/_AXDw1h
// Arduino breadboard prototyping shield: https://s.click.aliexpress.com/e/_ApbCwx
// Image2cpp (convert array to image): https://javl.github.io/image2cpp/
// Photopea (online graphics editor like Photoshop): https://www.photopea.com/
// arrays of strings: https://www.arduino.cc/reference/en/language/variables/data-types/string/
// 128x64 display initialization: https://github.com/olikraus/u8g2/wiki/u8g2setupcpp#ssd1306-128x32_univision
// used u8g2 font: https://github.com/olikraus/u8g2/wiki/fntgrpu8g#squeezed_b7

// Related videos with Arduino UNO and OLED screen:
// Image to OLED in 60 seconds - https://www.youtube.com/watch?v=Lw0Aaoo3YSY
// Arduino + OLED displays: https://www.youtube.com/playlist?list=PLjQRaMdk7pBZ1UV3IL5ol8Qc7R9k-kwXA

#include <Arduino.h>
#include <U8g2lib.h> // u8g2 library is used to draw graphics on the OLED display
#include <Wire.h> // library required for IIC communication

//U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); // initialization for the 128x64px OLED display
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); // initialization for the 128x32px OLED display, [full framebuffer, size = 512 bytes]


// two bubble images were drawn in Photopea and arrays were created using the image2cpp website

// 'img_bubble_fill', 26x13px
const unsigned char epd_bitmap_img_bubble_fill [] PROGMEM = {
  0xfc, 0xff, 0xff, 0x00, 0xfe, 0xff, 0xff, 0x01, 0xfe, 0xff, 0xff, 0x01, 0xfe, 0xff, 0xff, 0x01,
  0xfe, 0xff, 0xff, 0x01, 0xfe, 0xff, 0xff, 0x01, 0xfe, 0xff, 0xff, 0x01, 0xfe, 0xff, 0xff, 0x01,
  0xfc, 0xff, 0xff, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00
};
// 'img_bubble_outline', 26x13px
const unsigned char epd_bitmap_img_bubble_outline [] PROGMEM = {
  0xfe, 0xff, 0xff, 0x01, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0x03,
  0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0x03,
  0xfe, 0xff, 0xff, 0x01, 0xfc, 0xff, 0xff, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00,
  0x00, 0x30, 0x00, 0x00
};


// scaled labels as images

// '000_letter_n_0', 26x12px
const unsigned char epd_bitmap_000_letter_n_0 [] PROGMEM = {
  0x00, 0x48, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00, 0x58, 0x00, 0x00,
  0x00, 0x58, 0x00, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00,
  0x00, 0x68, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00
};
// '000_letter_n_1', 26x12px
const unsigned char epd_bitmap_000_letter_n_1 [] PROGMEM = {
  0x00, 0x88, 0x00, 0x00, 0x00, 0x98, 0x00, 0x00, 0x00, 0x98, 0x00, 0x00, 0x00, 0x98, 0x00, 0x00,
  0x00, 0x98, 0x00, 0x00, 0x00, 0xa8, 0x00, 0x00, 0x00, 0xa8, 0x00, 0x00, 0x00, 0xa8, 0x00, 0x00,
  0x00, 0xc8, 0x00, 0x00, 0x00, 0xc8, 0x00, 0x00, 0x00, 0xc8, 0x00, 0x00, 0x00, 0x88, 0x00, 0x00
};
// '000_letter_n_2', 26x12px
const unsigned char epd_bitmap_000_letter_n_2 [] PROGMEM = {
  0x00, 0x8c, 0x01, 0x00, 0x00, 0x9c, 0x01, 0x00, 0x00, 0x9c, 0x01, 0x00, 0x00, 0xbc, 0x01, 0x00,
  0x00, 0xbc, 0x01, 0x00, 0x00, 0xbc, 0x01, 0x00, 0x00, 0xec, 0x01, 0x00, 0x00, 0xec, 0x01, 0x00,
  0x00, 0xec, 0x01, 0x00, 0x00, 0xcc, 0x01, 0x00, 0x00, 0xcc, 0x01, 0x00, 0x00, 0x8c, 0x01, 0x00
};
// '000_letter_n_3', 26x12px
const unsigned char epd_bitmap_000_letter_n_3 [] PROGMEM = {
  0x00, 0x03, 0x03, 0x00, 0x00, 0x07, 0x03, 0x00, 0x00, 0x0f, 0x03, 0x00, 0x00, 0x0f, 0x03, 0x00,
  0x00, 0x1b, 0x03, 0x00, 0x00, 0x33, 0x03, 0x00, 0x00, 0x33, 0x03, 0x00, 0x00, 0x63, 0x03, 0x00,
  0x00, 0xc3, 0x03, 0x00, 0x00, 0xc3, 0x03, 0x00, 0x00, 0x83, 0x03, 0x00, 0x00, 0x03, 0x03, 0x00
};
// '045_letter_ne_0', 26x12px
const unsigned char epd_bitmap_045_letter_ne_0 [] PROGMEM = {
  0x00, 0xd2, 0x01, 0x00, 0x00, 0xd2, 0x01, 0x00, 0x00, 0x56, 0x00, 0x00, 0x00, 0x56, 0x00, 0x00,
  0x00, 0x56, 0x00, 0x00, 0x00, 0xd6, 0x01, 0x00, 0x00, 0xda, 0x01, 0x00, 0x00, 0x5a, 0x00, 0x00,
  0x00, 0x5a, 0x00, 0x00, 0x00, 0x5a, 0x00, 0x00, 0x00, 0xd2, 0x01, 0x00, 0x00, 0xd2, 0x01, 0x00
};
// '045_letter_ne_1', 26x12px
const unsigned char epd_bitmap_045_letter_ne_1 [] PROGMEM = {
  0x00, 0xd1, 0x03, 0x00, 0x00, 0xd3, 0x03, 0x00, 0x00, 0x53, 0x00, 0x00, 0x00, 0x53, 0x00, 0x00,
  0x00, 0x53, 0x00, 0x00, 0x00, 0xd5, 0x03, 0x00, 0x00, 0xd5, 0x03, 0x00, 0x00, 0x55, 0x00, 0x00,
  0x00, 0x59, 0x00, 0x00, 0x00, 0x59, 0x00, 0x00, 0x00, 0xd9, 0x03, 0x00, 0x00, 0xd1, 0x03, 0x00
};
// '045_letter_ne_2', 26x12px
const unsigned char epd_bitmap_045_letter_ne_2 [] PROGMEM = {
  0xc0, 0xd8, 0x0f, 0x00, 0xc0, 0xd9, 0x0f, 0x00, 0xc0, 0xd9, 0x00, 0x00, 0xc0, 0xdb, 0x00, 0x00,
  0xc0, 0xdb, 0x00, 0x00, 0xc0, 0xdb, 0x0f, 0x00, 0xc0, 0xde, 0x0f, 0x00, 0xc0, 0xde, 0x00, 0x00,
  0xc0, 0xde, 0x00, 0x00, 0xc0, 0xdc, 0x00, 0x00, 0xc0, 0xdc, 0x0f, 0x00, 0xc0, 0xd8, 0x0f, 0x00
};
// '045_letter_ne_3', 26x12px
const unsigned char epd_bitmap_045_letter_ne_3 [] PROGMEM = {
  0x18, 0xd8, 0x7f, 0x00, 0x38, 0xd8, 0x7f, 0x00, 0x78, 0xd8, 0x00, 0x00, 0x78, 0xd8, 0x00, 0x00,
  0xd8, 0xd8, 0x00, 0x00, 0x98, 0xd9, 0x7f, 0x00, 0x98, 0xd9, 0x7f, 0x00, 0x18, 0xdb, 0x00, 0x00,
  0x18, 0xde, 0x00, 0x00, 0x18, 0xde, 0x00, 0x00, 0x18, 0xdc, 0x7f, 0x00, 0x18, 0xd8, 0x7f, 0x00
};
// '090_letter_e_0', 26x12px
const unsigned char epd_bitmap_090_letter_e_0 [] PROGMEM = {
  0x00, 0x38, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00,
  0x00, 0x08, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00,
  0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00
};
// '090_letter_e_1', 26x12px
const unsigned char epd_bitmap_090_letter_e_1 [] PROGMEM = {
  0x00, 0x78, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00,
  0x00, 0x08, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00,
  0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00
};
// '090_letter_e_2', 26x12px
const unsigned char epd_bitmap_090_letter_e_2 [] PROGMEM = {
  0x00, 0x7c, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00,
  0x00, 0x0c, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00,
  0x00, 0x0c, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00
};
// '090_letter_e_3', 26x12px
const unsigned char epd_bitmap_090_letter_e_3 [] PROGMEM = {
  0x00, 0xfe, 0x03, 0x00, 0x00, 0xfe, 0x03, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00,
  0x00, 0x06, 0x00, 0x00, 0x00, 0xfe, 0x03, 0x00, 0x00, 0xfe, 0x03, 0x00, 0x00, 0x06, 0x00, 0x00,
  0x00, 0x06, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0xfe, 0x03, 0x00, 0x00, 0xfe, 0x03, 0x00
};
// '135_letter_se_1', 26x12px
const unsigned char epd_bitmap_135_letter_se_1 [] PROGMEM = {
  0x00, 0xe6, 0x01, 0x00, 0x00, 0xef, 0x01, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00,
  0x00, 0x23, 0x00, 0x00, 0x00, 0xe7, 0x01, 0x00, 0x00, 0xee, 0x01, 0x00, 0x00, 0x2c, 0x00, 0x00,
  0x00, 0x29, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00, 0xef, 0x01, 0x00, 0x00, 0xe6, 0x01, 0x00
};
// '135_letter_se_0', 26x12px
const unsigned char epd_bitmap_135_letter_se_0 [] PROGMEM = {
  0x00, 0xe4, 0x00, 0x00, 0x00, 0xee, 0x00, 0x00, 0x00, 0x2a, 0x00, 0x00, 0x00, 0x2a, 0x00, 0x00,
  0x00, 0x22, 0x00, 0x00, 0x00, 0xe6, 0x00, 0x00, 0x00, 0xec, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00,
  0x00, 0x2a, 0x00, 0x00, 0x00, 0x2a, 0x00, 0x00, 0x00, 0xee, 0x00, 0x00, 0x00, 0xe4, 0x00, 0x00
};
// '135_letter_se_2', 26x12px
const unsigned char epd_bitmap_135_letter_se_2 [] PROGMEM = {
  0x00, 0xcf, 0x07, 0x00, 0x80, 0xdf, 0x07, 0x00, 0x80, 0xd9, 0x00, 0x00, 0x80, 0xd9, 0x00, 0x00,
  0x80, 0xc3, 0x00, 0x00, 0x00, 0xcf, 0x07, 0x00, 0x00, 0xde, 0x07, 0x00, 0x00, 0xdc, 0x00, 0x00,
  0x80, 0xd9, 0x00, 0x00, 0x80, 0xd9, 0x00, 0x00, 0x00, 0xdf, 0x07, 0x00, 0x00, 0xcf, 0x07, 0x00
};
// '135_letter_se_3', 26x12px
const unsigned char epd_bitmap_135_letter_se_3 [] PROGMEM = {
  0xe0, 0xc3, 0x7f, 0x00, 0xf0, 0xc7, 0x7f, 0x00, 0x18, 0xce, 0x00, 0x00, 0x18, 0xcc, 0x00, 0x00,
  0x78, 0xc0, 0x00, 0x00, 0xf0, 0xc3, 0x7f, 0x00, 0xc0, 0xc7, 0x7f, 0x00, 0x00, 0xce, 0x00, 0x00,
  0x18, 0xcc, 0x00, 0x00, 0x38, 0xce, 0x00, 0x00, 0xf0, 0xc7, 0x7f, 0x00, 0xe0, 0xc3, 0x7f, 0x00
};
// '180_letter_s_0', 26x12px
const unsigned char epd_bitmap_180_letter_s_0 [] PROGMEM = {
  0x00, 0x20, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00,
  0x00, 0x10, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00,
  0x00, 0x50, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00
};
// '180_letter_s_1', 26x12px
const unsigned char epd_bitmap_180_letter_s_1 [] PROGMEM = {
  0x00, 0x30, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00,
  0x00, 0x18, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00,
  0x00, 0x48, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00
};
// '180_letter_s_2', 26x12px
const unsigned char epd_bitmap_180_letter_s_2 [] PROGMEM = {
  0x00, 0x78, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0xcc, 0x00, 0x00, 0x00, 0xcc, 0x00, 0x00,
  0x00, 0x1c, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00,
  0x00, 0xcc, 0x00, 0x00, 0x00, 0xcc, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00
};
// '180_letter_s_3', 26x12px
const unsigned char epd_bitmap_180_letter_s_3 [] PROGMEM = {
  0x00, 0xf8, 0x00, 0x00, 0x00, 0xfc, 0x01, 0x00, 0x00, 0x86, 0x03, 0x00, 0x00, 0x06, 0x03, 0x00,
  0x00, 0x1e, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0xf0, 0x01, 0x00, 0x00, 0x80, 0x03, 0x00,
  0x00, 0x06, 0x03, 0x00, 0x00, 0x8e, 0x03, 0x00, 0x00, 0xfc, 0x01, 0x00, 0x00, 0xf8, 0x00, 0x00
};
// '225_letter_sw_0', 26x12px
const unsigned char epd_bitmap_225_letter_sw_0 [] PROGMEM = {
  0x00, 0x52, 0x01, 0x00, 0x00, 0x57, 0x01, 0x00, 0x00, 0x55, 0x01, 0x00, 0x00, 0x55, 0x01, 0x00,
  0x00, 0x51, 0x01, 0x00, 0x00, 0x53, 0x01, 0x00, 0x00, 0x56, 0x01, 0x00, 0x00, 0x54, 0x01, 0x00,
  0x00, 0xa5, 0x00, 0x00, 0x00, 0xa5, 0x00, 0x00, 0x00, 0xa7, 0x00, 0x00, 0x00, 0xa2, 0x00, 0x00
};
// '225_letter_sw_1', 26x12px
const unsigned char epd_bitmap_225_letter_sw_1 [] PROGMEM = {
  0x80, 0x89, 0x08, 0x00, 0xc0, 0x8b, 0x08, 0x00, 0x40, 0x8a, 0x08, 0x00, 0x40, 0x52, 0x05, 0x00,
  0xc0, 0x50, 0x05, 0x00, 0xc0, 0x51, 0x05, 0x00, 0x80, 0x53, 0x05, 0x00, 0x00, 0x53, 0x05, 0x00,
  0x40, 0x52, 0x05, 0x00, 0x40, 0x22, 0x02, 0x00, 0xc0, 0x23, 0x02, 0x00, 0x80, 0x21, 0x02, 0x00
};
// '225_letter_sw_2', 26x12px
const unsigned char epd_bitmap_225_letter_sw_2 [] PROGMEM = {
  0xc0, 0x33, 0x62, 0x00, 0xe0, 0x37, 0x66, 0x00, 0x60, 0x36, 0x67, 0x00, 0x60, 0x66, 0x35, 0x00,
  0xe0, 0x60, 0x35, 0x00, 0xc0, 0x63, 0x35, 0x00, 0x80, 0x67, 0x35, 0x00, 0x00, 0x67, 0x35, 0x00,
  0x60, 0xc6, 0x1d, 0x00, 0x60, 0xc6, 0x18, 0x00, 0xc0, 0xc7, 0x18, 0x00, 0xc0, 0xc3, 0x18, 0x00
};
// '225_letter_sw_3', 26x12px
const unsigned char epd_bitmap_225_letter_sw_3 [] PROGMEM = {
  0xf8, 0x18, 0x0e, 0x03, 0xfc, 0x39, 0x0e, 0x03, 0x86, 0x33, 0x8e, 0x01, 0x06, 0x33, 0x9b, 0x01,
  0x1e, 0x30, 0x9b, 0x01, 0xfc, 0x60, 0xdb, 0x00, 0xf0, 0x61, 0xdb, 0x00, 0x80, 0x63, 0xdb, 0x00,
  0x06, 0xc3, 0xf1, 0x00, 0x8e, 0xc3, 0x71, 0x00, 0xfc, 0xc1, 0x71, 0x00, 0xf8, 0xc0, 0x71, 0x00
};
// '270_letter_w_1', 26x12px
const unsigned char epd_bitmap_270_letter_w_1 [] PROGMEM = {
  0x00, 0x22, 0x02, 0x00, 0x00, 0x22, 0x02, 0x00, 0x00, 0x22, 0x02, 0x00, 0x00, 0x54, 0x01, 0x00,
  0x00, 0x54, 0x01, 0x00, 0x00, 0x54, 0x01, 0x00, 0x00, 0x54, 0x01, 0x00, 0x00, 0x54, 0x01, 0x00,
  0x00, 0x54, 0x01, 0x00, 0x00, 0x88, 0x00, 0x00, 0x00, 0x88, 0x00, 0x00, 0x00, 0x88, 0x00, 0x00
};
// '270_letter_w_0', 26x12px
const unsigned char epd_bitmap_270_letter_w_0 [] PROGMEM = {
  0x00, 0xa8, 0x00, 0x00, 0x00, 0xa8, 0x00, 0x00, 0x00, 0xa8, 0x00, 0x00, 0x00, 0xa8, 0x00, 0x00,
  0x00, 0xa8, 0x00, 0x00, 0x00, 0xa8, 0x00, 0x00, 0x00, 0xa8, 0x00, 0x00, 0x00, 0xa8, 0x00, 0x00,
  0x00, 0x50, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00
};
// '270_letter_w_2', 26x12px
const unsigned char epd_bitmap_270_letter_w_2 [] PROGMEM = {
  0x00, 0x23, 0x06, 0x00, 0x00, 0x73, 0x06, 0x00, 0x00, 0x73, 0x06, 0x00, 0x00, 0x56, 0x03, 0x00,
  0x00, 0x56, 0x03, 0x00, 0x00, 0x56, 0x03, 0x00, 0x00, 0x56, 0x03, 0x00, 0x00, 0x56, 0x03, 0x00,
  0x00, 0xdc, 0x01, 0x00, 0x00, 0x8c, 0x01, 0x00, 0x00, 0x8c, 0x01, 0x00, 0x00, 0x8c, 0x01, 0x00
};
// '270_letter_w_3', 26x12px
const unsigned char epd_bitmap_270_letter_w_3 [] PROGMEM = {
  0xc0, 0x70, 0x18, 0x00, 0xc0, 0x71, 0x18, 0x00, 0x80, 0x71, 0x0c, 0x00, 0x80, 0xd9, 0x0c, 0x00,
  0x80, 0xd9, 0x0c, 0x00, 0x00, 0xdb, 0x06, 0x00, 0x00, 0xdb, 0x06, 0x00, 0x00, 0xdb, 0x06, 0x00,
  0x00, 0x8e, 0x07, 0x00, 0x00, 0x8e, 0x03, 0x00, 0x00, 0x8e, 0x03, 0x00, 0x00, 0x8e, 0x03, 0x00
};
// '315_letter_nw_1', 26x12px
const unsigned char epd_bitmap_315_letter_nw_1 [] PROGMEM = {
  0x20, 0x8a, 0x08, 0x00, 0x60, 0x8a, 0x08, 0x00, 0x60, 0x8a, 0x08, 0x00, 0x60, 0x52, 0x05, 0x00,
  0x60, 0x52, 0x05, 0x00, 0xa0, 0x52, 0x05, 0x00, 0xa0, 0x52, 0x05, 0x00, 0xa0, 0x52, 0x05, 0x00,
  0x20, 0x53, 0x05, 0x00, 0x20, 0x23, 0x02, 0x00, 0x20, 0x23, 0x02, 0x00, 0x20, 0x22, 0x02, 0x00
};
// '315_letter_nw_0', 26x12px
const unsigned char epd_bitmap_315_letter_nw_0 [] PROGMEM = {
  0x00, 0xa9, 0x02, 0x00, 0x00, 0xa9, 0x02, 0x00, 0x00, 0xab, 0x02, 0x00, 0x00, 0xab, 0x02, 0x00,
  0x00, 0xab, 0x02, 0x00, 0x00, 0xab, 0x02, 0x00, 0x00, 0xad, 0x02, 0x00, 0x00, 0xad, 0x02, 0x00,
  0x00, 0x4d, 0x01, 0x00, 0x00, 0x4d, 0x01, 0x00, 0x00, 0x49, 0x01, 0x00, 0x00, 0x49, 0x01, 0x00
};
// '315_letter_nw_2', 26x12px
const unsigned char epd_bitmap_315_letter_nw_2 [] PROGMEM = {
  0x60, 0x36, 0x62, 0x00, 0xe0, 0x36, 0x67, 0x00, 0xe0, 0x36, 0x67, 0x00, 0xe0, 0x67, 0x35, 0x00,
  0xe0, 0x67, 0x35, 0x00, 0xe0, 0x67, 0x35, 0x00, 0xe0, 0x67, 0x35, 0x00, 0xe0, 0x67, 0x35, 0x00,
  0xe0, 0xc7, 0x1d, 0x00, 0x60, 0xc7, 0x18, 0x00, 0x60, 0xc7, 0x18, 0x00, 0x60, 0xc6, 0x18, 0x00
};
// '315_letter_nw_3', 26x12px
const unsigned char epd_bitmap_315_letter_nw_3 [] PROGMEM = {
  0x03, 0x1b, 0x0e, 0x03, 0x07, 0x3b, 0x0e, 0x03, 0x0f, 0x33, 0x8e, 0x01, 0x0f, 0x33, 0x9b, 0x01,
  0x1b, 0x33, 0x9b, 0x01, 0x33, 0x63, 0xdb, 0x00, 0x33, 0x63, 0xdb, 0x00, 0x63, 0x63, 0xdb, 0x00,
  0xc3, 0xc3, 0xf1, 0x00, 0xc3, 0xc3, 0x71, 0x00, 0x83, 0xc3, 0x71, 0x00, 0x03, 0xc3, 0x71, 0x00
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 2048)
const int epd_bitmap_allArray_LEN = 32;
const unsigned char* character_bitmaps[32] = {
  epd_bitmap_000_letter_n_0,
  epd_bitmap_000_letter_n_1,
  epd_bitmap_000_letter_n_2,
  epd_bitmap_000_letter_n_3,
  epd_bitmap_045_letter_ne_0,
  epd_bitmap_045_letter_ne_1,
  epd_bitmap_045_letter_ne_2,
  epd_bitmap_045_letter_ne_3,
  epd_bitmap_090_letter_e_0,
  epd_bitmap_090_letter_e_1,
  epd_bitmap_090_letter_e_2,
  epd_bitmap_090_letter_e_3,
  epd_bitmap_135_letter_se_0,
  epd_bitmap_135_letter_se_1,
  epd_bitmap_135_letter_se_2,
  epd_bitmap_135_letter_se_3,
  epd_bitmap_180_letter_s_0,
  epd_bitmap_180_letter_s_1,
  epd_bitmap_180_letter_s_2,
  epd_bitmap_180_letter_s_3,
  epd_bitmap_225_letter_sw_0,
  epd_bitmap_225_letter_sw_1,
  epd_bitmap_225_letter_sw_2,
  epd_bitmap_225_letter_sw_3,
  epd_bitmap_270_letter_w_0,
  epd_bitmap_270_letter_w_1,
  epd_bitmap_270_letter_w_2,
  epd_bitmap_270_letter_w_3,
  epd_bitmap_315_letter_nw_0,
  epd_bitmap_315_letter_nw_1,
  epd_bitmap_315_letter_nw_2,
  epd_bitmap_315_letter_nw_3
};



int compass_degrees; // 0-360° -- compass heading, for now, this value is taken from the potentiometer value
char buffer[20]; // helper buffer for displaying strings on the display
int xpos_offset; // x offset of all the tickmarks
int xpos_with_offset; // x position of the tickmark with applied offset
float xpos_final; // final x position for the tickmark
int str_width; // calculated width of the string

int labels_count = 3; // number of different images for every label (for example, "SW"), 3 = total of 4 images per label
int label_display = 0; // which label version to display for the current big tickmark
int SHOW_SCALED_LABEL = 1; // should we show the scaled label (drawn using image) or the standard non-scaled label (drawn using the u8g2 font)

char *compass_labels[] = {"N", "NE", "E", "SE", "S", "SW", "W", "NW", "N"}; // array with strings for big tickmarks

void setup(void) {
  u8g2.begin(); // start the u8g2 library
  pinMode(A0, INPUT); // set the analog input pin A0 as input
}

void loop(void) {

  compass_degrees = map(analogRead(A0), 0, 1023, 0, 360); // use the potentiometer to set the degrees between 0-360°
  xpos_offset = round((360 - compass_degrees) / 360.0 * 240.0); // calculate the X offset for all the tickmarks, max offset is 10(px)*24(tickmarks) = 240px

  u8g2.clearBuffer();  // clear the internal memory
  u8g2.setDrawColor(1); // set the drawing color to white
  u8g2.setBitmapMode(1); // draw transparent images

  for (int i = 0; i < 24; i++) { // go over all 24 tickmarks

    xpos_with_offset = (64 + (i * 10) + xpos_offset) % 240; // calculate the x offset for all tickmarks, do not go over 240px

    if (xpos_with_offset > 2 && xpos_with_offset < 128) { // only draw tickmarks that are inside the visible area (display width is 128px)

      // adjust the position using the power function
      if (xpos_with_offset < 64) {
        xpos_final = xpos_with_offset / 64.0; // convert 0-64 into 0-1 range to work nicely with the power function
        xpos_final = pow(xpos_final, 2.5); // add easing by having the power function, tweak the exponent for different result
        label_display = round(xpos_final * 1.0 * labels_count); // calculate which scaled label to show based on the x position
        xpos_final = xpos_final * 64.0; // convert 0-1 back into 0-64 (left side of the screen)
      } else {
        xpos_final = (128 - xpos_with_offset) / 64.0; // convert 0-64 into 0-1 range to work nicely with the power function
        xpos_final = pow(xpos_final, 2.5); // add easing by having the power function, tweak the exponent for different result
        label_display = round(xpos_final * 1.0 * labels_count); // calculate which scaled label to show based on the x position
        xpos_final = (64 - (xpos_final * 64.0)) + 64; // convert 1-0 back into 64-128 (right side of the screen)
      }

      xpos_final = round(xpos_final); // round the final x position to integer value

      if (i % 3 == 0) { // if the tickmark number is divisible by 3 == this is the big tickmark, show also the label
        u8g2.drawLine(xpos_final, 7, xpos_final, 15); // draw big tickmark line

        // draw either scaled labels (images) or standard labels (u8g2 font)
        if (SHOW_SCALED_LABEL == 0) { // standard label
          str_width = u8g2.getStrWidth(compass_labels[i / 3]); // calculate the string width
          u8g2.drawStr(xpos_final - str_width / 2, 24, compass_labels[i / 3]); // draw string
        } else { // scaled label
          int bitmap_index = ((i / 3) * (labels_count + 1)) + label_display; // which version of the image to display
          int label_xpos = xpos_final - (26 / 2); // all the images have the same width, the x pos could be easily calculated
          if (xpos_final > (0 + 3) && xpos_final < (128 - 3)) { // only draw labels if the x position is in certain range
            u8g2.drawXBMP(label_xpos, 10 + 7, 26, 12, character_bitmaps[bitmap_index]);
          }
        }

        if (label_display == labels_count) { // if we are drawing the "widest" label, draw the tickmark as 2px line (instead of just 1px line)
          u8g2.drawLine(xpos_final - 1, 7 + 0, xpos_final - 1, 7 + 8);
        }

      } else { // small tickmark without any label
        u8g2.drawLine(xpos_final, 7, xpos_final, 13); // draw tickmark
      }

    }
  }


  u8g2.drawLine(0, 5, 127, 5); // draw horizontal line

  u8g2.setDrawColor(0); // black color
  u8g2.drawXBMP(51, 0, 26, 13, epd_bitmap_img_bubble_outline); // bubble outline
  u8g2.setDrawColor(1); // white color
  u8g2.drawXBMP(51, 0, 26, 13, epd_bitmap_img_bubble_fill); // bubble fill

  u8g2.setDrawColor(0); // black color
  u8g2.setFontDirection(0); // normal font direction
  u8g2.setFont(u8g2_font_squeezed_b7_tr); // set font
  sprintf(buffer, "%d'", compass_degrees); // convert compass degree integer to string, add the ' symbol that (somehow) looks like degree symbol (degree symbol is not present in the font)
  str_width = u8g2.getStrWidth(buffer); // calculate the string width
  u8g2.drawStr(64 - str_width / 2, 8, buffer); // draw centered string

  u8g2.sendBuffer(); // transfer internal memory to the display
}