//uncomment this if using PROTON
//#define __PROTON__

#ifdef __PROTON__
#include "FMop.h"
#endif
#include "notedefs.h"
#include "FMSynth.h"
#ifdef __PROTON__
#include "Arduboy.h"
Arduboy arduboy;
#define DUR_UNIT (1000)
#else
#include "Arduboy2.h"
Arduboy2 arduboy;
#define DUR_UNIT (39136 / 2)
#endif

#define DRAW_PIXEL(x,y,c)    arduboy.drawPixel((x), (y), (c));
#define GET_PIXEL(x,y)      arduboy.getPixel((x), (y))
#define DRAW_LINE(fx,fy,tx,ty,c) arduboy.drawLine((fx),(fy),(tx),(ty),(c))
#define DRAW_BITMAP(x,y,b,w,h,c) arduboy.drawBitmap((x), (y), (b), (w), (h), (c))
#define DRAW_RECT(x,y,w,h,c)  arduboy.drawRect((x), (y), (w), (h), (c))
#define FILL_RECT(x,y,w,h,c)  arduboy.fillRect((x), (y), (w), (h), (c))
#define DRAW_H_LINE(x,y,l,c)  arduboy.drawFastHLine((x),(y),(l),(c))
#define DRAW_V_LINE(x,y,l,c)  arduboy.drawFastVLine((x),(y),(l),(c))
#define G_TXT_CURSOR(c,r)   arduboy.setCursor((c),(r))
#define G_PRINT(s)        arduboy.print((s))
#define G_DRAWCHAR(x, y, ch, c)    arduboy.drawChar(x,y,ch,c,((c)==0),1)
#define G_CLEAR()   arduboy.clear()

#define KEY_PRESSED(k)    arduboy.pressed((k))
#define KEY_NOT_PRESSED(k)  arduboy.notPressed((k))

void draw_string(uint8_t x, uint8_t y, const char *s, uint8_t color) {
  char c;
  while ((c = pgm_read_byte(s++)) != 0) {
    G_DRAWCHAR(x, y, c, color);
    x += 6;
  }
}

void draw_2digit(uint8_t x, uint8_t y, uint8_t n, uint8_t color) {
  G_DRAWCHAR(x, y, '0' + n / 10, color);
  G_DRAWCHAR(x + 6, y, '0' + n % 10, color);
}


const unsigned char PROGMEM synth_img[] =
{
  //width = 128, height = 64
  0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0x02, 0x01, 0xc2, 0xe4, 0xc2, 0x01, 0x02, 0xa4, 0xf2, 0xf1,
  0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1,
  0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1,
  0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1,
  0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1,
  0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1,
  0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1,
  0xf2, 0xf4, 0x02, 0x11, 0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11,
  0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0x80, 0x00, 0x86, 0x4e, 0x86, 0x00, 0x80, 0x4a, 0x9f, 0x1f,
  0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f,
  0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f,
  0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f,
  0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f,
  0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f,
  0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f,
  0x9f, 0x5f, 0x80, 0x11, 0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11,
  0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11, 0x02, 0xa4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1,
  0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0x01, 0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11,
  0x02, 0xa4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0x01,
  0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11, 0x02, 0xa4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1,
  0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0x01, 0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11,
  0x02, 0xa4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0x01,
  0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11, 0x02, 0xa4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0xf1,
  0xf2, 0xf4, 0xf2, 0xf1, 0xf2, 0xf4, 0xf2, 0x01, 0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11,
  0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11, 0x80, 0x4a, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f,
  0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x00, 0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11,
  0x80, 0x4a, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x00,
  0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11, 0x80, 0x4a, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f,
  0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x00, 0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11,
  0x80, 0x4a, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x00,
  0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11, 0x80, 0x4a, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x1f,
  0x9f, 0x5f, 0x9f, 0x1f, 0x9f, 0x5f, 0x9f, 0x00, 0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11,
  0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0xf1, 0x7a, 0x1c, 0x0e, 0x07, 0x06, 0x03, 0x03, 0x03,
  0x03, 0x03, 0x06, 0x07, 0x0e, 0x1c, 0x7a, 0xf1, 0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0xf1,
  0x7a, 0x1c, 0x0e, 0x07, 0x06, 0x03, 0x03, 0x03, 0x03, 0x03, 0x06, 0x07, 0x0e, 0x1c, 0x7a, 0xf1,
  0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0xf1, 0x7a, 0x1c, 0x0e, 0x07, 0x06, 0x03, 0x03, 0x03,
  0x03, 0x03, 0x06, 0x07, 0x0e, 0x1c, 0x7a, 0xf1, 0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0xf1,
  0x7a, 0x1c, 0x0e, 0x07, 0x06, 0x03, 0x03, 0x03, 0x03, 0x03, 0x06, 0x07, 0x0e, 0x1c, 0x7a, 0xf1,
  0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0xf1, 0x7a, 0x1c, 0x0e, 0x07, 0x06, 0x03, 0x03, 0x03,
  0x03, 0x03, 0x06, 0x07, 0x0e, 0x1c, 0x7a, 0xf1, 0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11,
  0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaf, 0x3f, 0xf0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xf0, 0x3f, 0xaf, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaf, 0x3f,
  0xf0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xf0, 0x3f,
  0xaf, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaf, 0x3f, 0xf0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xf0, 0x3f, 0xaf, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaf, 0x3f,
  0xf0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xf0, 0x3f,
  0xaf, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaf, 0x3f, 0xf0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xf0, 0x3f, 0xaf, 0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11,
  0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x04, 0x2a, 0x11, 0x2a, 0x85, 0xab, 0x93, 0xab, 0x86, 0xae, 0x16,
  0xae, 0x86, 0xab, 0x93, 0xab, 0x85, 0x2a, 0x11, 0x2a, 0x04, 0x2a, 0x51, 0x2a, 0x04, 0xaa, 0x11,
  0x2a, 0x05, 0xab, 0x13, 0xab, 0x86, 0x2e, 0x96, 0xae, 0x06, 0xab, 0x93, 0x2b, 0x85, 0xaa, 0x91,
  0xaa, 0x04, 0x2a, 0x51, 0x2a, 0x04, 0x2a, 0x11, 0x2a, 0x85, 0xab, 0x93, 0xab, 0x86, 0xae, 0x16,
  0x2e, 0x86, 0xab, 0x13, 0x2b, 0x05, 0x2a, 0x11, 0x2a, 0x04, 0x2a, 0x51, 0x2a, 0x04, 0x2a, 0x91,
  0xaa, 0x85, 0xab, 0x93, 0xab, 0x06, 0x2e, 0x96, 0xae, 0x86, 0xab, 0x93, 0x2b, 0x05, 0x2a, 0x91,
  0xaa, 0x04, 0x2a, 0x51, 0x2a, 0x04, 0xaa, 0x91, 0xaa, 0x85, 0xab, 0x93, 0x2b, 0x06, 0xae, 0x96,
  0xae, 0x86, 0xab, 0x13, 0x2b, 0x05, 0xaa, 0x91, 0xaa, 0x04, 0x2a, 0x11, 0xaa, 0x44, 0xaa, 0x11,
  0xaa, 0x44, 0xaa, 0x11, 0xaa, 0x00, 0x80, 0x00, 0x80, 0x3f, 0xbf, 0x04, 0x84, 0x04, 0x80, 0x00,
  0xbf, 0x3f, 0xa4, 0x24, 0xa4, 0x3f, 0x9b, 0x00, 0x80, 0x00, 0x80, 0x55, 0x80, 0x00, 0xbf, 0x3f,
  0x8e, 0x3f, 0xbf, 0x00, 0x9f, 0x3f, 0xa0, 0x3f, 0x9f, 0x00, 0xbf, 0x3f, 0xa0, 0x00, 0xbf, 0x3f,
  0x80, 0x00, 0x80, 0x55, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x3f, 0xbf, 0x00, 0x80, 0x00,
  0x80, 0x3f, 0xbf, 0x20, 0xa0, 0x20, 0xa0, 0x00, 0x80, 0x00, 0x80, 0x55, 0x80, 0x00, 0x80, 0x20,
  0xbf, 0x3f, 0xa0, 0x20, 0xbf, 0x1f, 0x80, 0x3f, 0xbf, 0x0c, 0x9c, 0x37, 0xa3, 0x00, 0x81, 0x3f,
  0xbf, 0x00, 0x80, 0x55, 0x80, 0x00, 0xa0, 0x3f, 0xbf, 0x20, 0xa0, 0x3f, 0x9f, 0x00, 0xbf, 0x3f,
  0x8c, 0x1c, 0xb7, 0x23, 0x80, 0x31, 0xb9, 0x2c, 0xa7, 0x23, 0x80, 0x00, 0xaa, 0x44, 0xaa, 0x11,
};

const unsigned char PROGMEM sequencer_img[] =
{
  //width = 128, height = 64
  0x00, 0x00, 0xd8, 0xdc, 0xd8, 0x00, 0x00, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe,
  0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x00, 0xaa, 0x15, 0xca, 0xe5,
  0x22, 0xe5, 0xca, 0x15, 0xaa, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff,
  0xff, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff,
  0xff, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff,
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff,
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff,
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xaa, 0x55,
  0xa8, 0x50, 0xa8, 0x51, 0xa8, 0x50, 0xa8, 0x53, 0xab, 0x53, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
  0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xab, 0x53, 0xab, 0x53, 0xab, 0x50, 0xaa, 0x00, 0x7f, 0xff,
  0x80, 0xff, 0x7f, 0x00, 0xaa, 0x00, 0xff, 0xff, 0xfc, 0x00, 0xfc, 0xff, 0xfc, 0x00, 0xfc, 0xff,
  0xff, 0x00, 0xff, 0xff, 0xfc, 0x00, 0xfc, 0xff, 0xfc, 0x00, 0xfc, 0xff, 0xfc, 0x00, 0xfc, 0xff,
  0xff, 0x00, 0xff, 0xff, 0xfc, 0x00, 0xfc, 0xff, 0xfc, 0x00, 0xfc, 0xff, 0xff, 0x00, 0xff, 0xff,
  0xfc, 0x00, 0xfc, 0xff, 0xfc, 0x00, 0xfc, 0xff, 0xfc, 0x00, 0xfc, 0xff, 0xff, 0x00, 0xff, 0xff,
  0xfc, 0x00, 0xfc, 0xff, 0xfc, 0x00, 0xfc, 0xff, 0xff, 0x00, 0xff, 0xff, 0xfc, 0x00, 0xfc, 0xff,
  0xfc, 0x00, 0xfc, 0xff, 0xfc, 0x00, 0xfc, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xaa, 0x55,
  0xaa, 0x55, 0x2a, 0x15, 0x2a, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0x28, 0x14, 0x28, 0x54, 0xa8, 0x54,
  0xa8, 0x54, 0x28, 0x14, 0x28, 0x54, 0xaa, 0x55, 0xaa, 0x55, 0x2a, 0x15, 0x2a, 0x55, 0xaa, 0x54,
  0xaa, 0x54, 0x2a, 0x15, 0x2a, 0x54, 0xa9, 0x55, 0xa9, 0x54, 0x29, 0x15, 0x29, 0x54, 0xa9, 0x55,
  0xa9, 0x54, 0x29, 0x15, 0x29, 0x54, 0xa9, 0x55, 0xa9, 0x54, 0x29, 0x15, 0x29, 0x54, 0xa9, 0x55,
  0xa9, 0x54, 0x29, 0x15, 0x29, 0x54, 0xa9, 0x55, 0xa9, 0x54, 0x29, 0x15, 0x29, 0x54, 0xa9, 0x55,
  0xa9, 0x54, 0x29, 0x15, 0x29, 0x54, 0xa9, 0x55, 0xa9, 0x54, 0x29, 0x15, 0x29, 0x54, 0xa9, 0x55,
  0xa9, 0x54, 0x29, 0x15, 0x29, 0x54, 0xa9, 0x55, 0xa9, 0x54, 0x29, 0x15, 0x29, 0x54, 0xa9, 0x55,
  0xa9, 0x54, 0x29, 0x15, 0x29, 0x54, 0xa9, 0x55, 0xa9, 0x54, 0x29, 0x15, 0x29, 0x54, 0xaa, 0x55,
  0x00, 0xfe, 0xff, 0x01, 0xff, 0xfe, 0x00, 0x55, 0x00, 0xfe, 0xff, 0x01, 0xff, 0xfe, 0x00, 0x55,
  0x00, 0xfe, 0xff, 0x01, 0xff, 0xfe, 0x00, 0x55, 0x00, 0xfe, 0xff, 0x01, 0xff, 0xfe, 0x00, 0x01,
  0x00, 0xfe, 0xff, 0x01, 0xff, 0xfe, 0x00, 0x55, 0x00, 0xfe, 0xff, 0x01, 0xff, 0xfe, 0x00, 0x55,
  0x00, 0xfe, 0xff, 0x01, 0xff, 0xfe, 0x00, 0x55, 0x00, 0xfe, 0xff, 0x01, 0xff, 0xfe, 0x00, 0x01,
  0x00, 0xfe, 0xff, 0x01, 0xff, 0xfe, 0x00, 0x55, 0x00, 0xfe, 0xff, 0x01, 0xff, 0xfe, 0x00, 0x55,
  0x00, 0xfe, 0xff, 0x01, 0xff, 0xfe, 0x00, 0x55, 0x00, 0xfe, 0xff, 0x01, 0xff, 0xfe, 0x00, 0x01,
  0x00, 0xfe, 0xff, 0x01, 0xff, 0xfe, 0x00, 0x55, 0x00, 0xfe, 0xff, 0x01, 0xff, 0xfe, 0x00, 0x55,
  0x00, 0xfe, 0xff, 0x01, 0xff, 0xfe, 0x00, 0x55, 0x00, 0xfe, 0xff, 0x01, 0xff, 0xfe, 0x00, 0x55,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x00,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x00,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x00,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x00,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x00,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x00,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x00,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x00,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x00,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55,
  0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x55,
  0x80, 0x3f, 0x7f, 0x60, 0x7f, 0x3f, 0xc0, 0x55, 0x80, 0x3f, 0x7f, 0x60, 0x7f, 0x3f, 0xc0, 0x5d,
  0x80, 0x3f, 0x7f, 0x60, 0x7f, 0x3f, 0xc0, 0x55, 0x80, 0x3f, 0x7f, 0x60, 0x7f, 0x3f, 0xc0, 0x50,
  0x80, 0x3f, 0x7f, 0x60, 0x7f, 0x3f, 0xc0, 0x55, 0x80, 0x3f, 0x7f, 0x60, 0x7f, 0x3f, 0xc0, 0x55,
  0x80, 0x3f, 0x7f, 0x60, 0x7f, 0x3f, 0xc0, 0x55, 0x80, 0x3f, 0x7f, 0x60, 0x7f, 0x3f, 0xc0, 0x50,
  0x80, 0x3f, 0x7f, 0x60, 0x7f, 0x3f, 0xc0, 0x55, 0x80, 0x3f, 0x7f, 0x60, 0x7f, 0x3f, 0xc0, 0x55,
  0x80, 0x3f, 0x7f, 0x60, 0x7f, 0x3f, 0xc0, 0x55, 0x80, 0x3f, 0x7f, 0x60, 0x7f, 0x3f, 0xc0, 0x50,
  0x80, 0x3f, 0x7f, 0x60, 0x7f, 0x3f, 0xc0, 0x55, 0x80, 0x3f, 0x7f, 0x60, 0x7f, 0x3f, 0xc0, 0x55,
  0x80, 0x3f, 0x7f, 0x60, 0x7f, 0x3f, 0xc0, 0x55, 0x80, 0x3f, 0x7f, 0x60, 0x7f, 0x3f, 0xc0, 0x55,
};

const uint8_t panel[] PROGMEM =
{
  //width = 68, height = 12
  0x7f, 0xe0, 0xee, 0xe0, 0xff, 0xe0, 0x71, 0x60, 0xff, 0xe0, 0x6a, 0xee, 0x7f, 0xff, 0x7f, 0xe0,
  0x7a, 0xe0, 0x7f, 0x60, 0x6f, 0xef, 0xff, 0xe0, 0xef, 0xef, 0x7f, 0xff, 0x7f, 0xe0, 0xee, 0xe0,
  0xff, 0xe0, 0x71, 0x60, 0xff, 0xe0, 0x6a, 0x6e, 0x7f, 0xff, 0x7f, 0x60, 0x7a, 0xe0, 0x7f, 0xe0,
  0x6f, 0xef, 0xff, 0xe0, 0xef, 0xef, 0x7f, 0xff, 0xff, 0x68, 0xea, 0x62, 0xff, 0x60, 0x7a, 0x60,
  0xff, 0x70, 0xef, 0x70, 0xfc, 0xfd, 0xfd, 0xfd, 0xfd, 0xff, 0xf0, 0xf7, 0xf8, 0xff, 0xf0, 0xf7,
  0xf0, 0xff, 0xf0, 0xfc, 0xf0, 0xff, 0xf0, 0xfd, 0xfc, 0xff, 0xfd, 0xfd, 0xfd, 0xfd, 0xfc, 0xff,
  0xfc, 0xfd, 0xfd, 0xfd, 0xfd, 0xff, 0xf0, 0xfd, 0xf2, 0xff, 0xf0, 0xf5, 0xf5, 0xff, 0xf0, 0xf7,
  0xf7, 0xff, 0xf8, 0xf7, 0xf8, 0xff, 0xfd, 0xfd, 0xfd, 0xfd, 0xfc, 0xff, 0xff, 0xf0, 0xfc, 0xf0,
  0xff, 0xf0, 0xf5, 0xf5, 0xff, 0xf0, 0xfc, 0xf0,
};

const uint8_t cancelbutton[] PROGMEM =
{
  //width = 27, height = 8
  0x00, 0x7e, 0x66, 0x5a, 0x5a, 0x7e, 0x42, 0x6a, 0x42, 0x7e, 0x42, 0x66, 0x42, 0x7e, 0x66, 0x5a,
  0x5a, 0x7e, 0x42, 0x52, 0x5a, 0x7e, 0x42, 0x5e, 0x5e, 0x7e, 0x00,
};

const uint8_t waitingmsg[] PROGMEM =
{
  //width = 29, height = 8
  0xff, 0xe0, 0xf3, 0xe0, 0xff, 0xe0, 0xfa, 0xe0, 0xff, 0xe0, 0xff, 0xfe, 0xe0, 0xfe, 0xff, 0xe0,
  0xff, 0xe0, 0xf1, 0xe0, 0xff, 0xf1, 0xee, 0xe2, 0xff, 0xef, 0xff, 0xef, 0xff,
};


const int8_t dial_x[32] PROGMEM =
{
  -3, -4, -5, -6, -6, -7, -7, -7,
  -7, -6, -5, -4, -3, -2, -1, -1,
  0, 1, 2, 3, 4, 5, 6, 7,
  7, 7, 7, 7, 6, 5, 4, 3
};
const int8_t dial_y[32] PROGMEM =
{
  6, 5, 4, 3, 2, 1, 0, -1,
  -2, -3, -4, -5, -6, -6, -6, -7,
  -7, -7, -6, -6, -5, -4, -3, -2,
  -1, 0, 1, 2, 3, 4, 5, 6
};


#define NUM_INST (8)

const int8_t preset_progs[NUM_INST][5] PROGMEM = {
  //
  // +---- OP0 ----+  OP1
  // FB MULT  TL  DR  DR 
  { 5,  2,  27,  1,  2 }, // Acoustic Piano
  { 7,  5,  38,  5,  2 }, // Electric Piano
  { 5,  9,  32,  2,  2 }, // Tubular Bells
  { 0,  8,  34,  8,  7 }, // Marimba
  { 7,  3,  32,  1,  2 }, // Jazz Guitar
  { 4,  1,  16,  1,  2 }, // Finger Bass
  { 4,  1,   8,  3,  2 }, // Slap Bass
  { 2,  12,  0,  7,  7 }, // Percussion
};

const char progname[NUM_INST][16] PROGMEM = {
  "Acoustic Piano",
  "Electric Piano",
  "Tubular Bells",
  "Marimba",
  "Jazz Guitar",
  "Finger Bass",
  "Slap Bass",
  "Percussion",
};

#define Param1st  0
#define ParamProg 1
#define ParamFB   2
#define ParamMult 3
#define ParamTL   4
#define ParamDR1  5
#define ParamDR2  6
#define ParamLast 7

#define Seq1st    0
#define SeqTempo  1
#define SeqTrans  2
#define SeqNotes  3
#define SeqLast   19

#define Pat1st    0
#define Pat01   1
#define Pat16   16
#define PatDump1  17
#define PatDumpAll  18
#define PatLoad1  19
#define PatLoadAll  20
#define PatSave   21
#define PatLast   22

const uint8_t selectorindicator[8][4] PROGMEM = {
  { 0, 0, 0, 0 },
  { 6, 3, 7, 11 },
  { 5, 54, 22, 9 },
  { 28, 54, 23, 9 },
  { 52, 54, 23, 9 },
  { 76, 54, 23, 9 },
  { 100, 54, 24, 9 },
  { 0, 0, 0, 0 },
};

struct SynthNumericParam {
  int8_t max;
  uint8_t x;
  uint8_t y;
  uint8_t c_x;
  uint8_t c_y;
};

const struct SynthNumericParam g_params[5] PROGMEM =
{
  { 7, 11, 21, 15, 41 },
  { 15, 35, 21, 39, 41 },
  { 63, 59, 21, 63, 41 },
  { 15, 83, 21, 87, 41 },
  { 15, 107, 21, 111, 41 },
};

enum Mode {
  Synthesizer,
  Sequencer,
  Pattern,
  Communication
} g_mode, g_prev_mode;

#define SEQ_LEN (16)
#define SEQ_NUM (16)

#define MAXNOTE (84)
#define MINNOTE (M_C4)
#define M_TIE (-2)

#define MAXTEMPO (240)
#define MINTEMPO (56)

#define MAXTRANSPOSE  (2)
#define MINTRANSPOSE  (-2)


const int8_t song01[SEQ_LEN] PROGMEM =
{
  M_C5, M_C5, M_G5, M_G5,
  M_A5, M_A5, M_G5, M_TIE,
  M_F5, M_F5, M_E5, M_E5,
  M_D5, M_D5, M_C5, M_TIE
};
const int8_t song02[SEQ_LEN] PROGMEM =
{
  M_G5, M_G5, M_F5, M_F5,
  M_E5, M_E5, M_D5, M_TIE,
  M_G5, M_G5, M_F5, M_F5,
  M_E5, M_E5, M_D5, M_TIE,
};
const int8_t song03[SEQ_LEN] PROGMEM =
{
  0x40, 0x40, 0x40, 0xFE,
  0x40, 0x40, 0x40, 0xFE,
  0x40, 0x43, 0x3C, 0x3E,
  0x40, 0xFE, 0xFF, 0xFF,
};
const int8_t song04[SEQ_LEN] PROGMEM =
{
  0x41, 0x41, 0x41, 0x41,
  0x41, 0x40, 0x40, 0x40,
  0x40, 0x3E, 0x3E, 0x40,
  0x3E, 0xFF, 0x43, 0xFE,
};
const int8_t song05[SEQ_LEN] PROGMEM =
{
  0x41, 0x41, 0x41, 0x41,
  0x41, 0x40, 0x40, 0x40,
  0x43, 0x43, 0x41, 0x3E,
  0x3C, 0xFF, 0xFF, 0xFF
};
const int8_t song06[SEQ_LEN] PROGMEM =
{
  0x41, 0x45, 0x48, 0x4C,
  0x41, 0x45, 0x47, 0x4A,
  0x40, 0x43, 0x47, 0x4A,
  0x40, 0x43, 0x45, 0x48
};
const int8_t song07[SEQ_LEN] PROGMEM =
{
  0x43, 0x43, 0x43, 0x43,
  0xFF, 0x46, 0x46, 0x46,
  0x46, 0xFF, 0x46, 0x46,
  0xFF, 0x46, 0x46, 0x46
};
const int8_t song08[SEQ_LEN] PROGMEM =
{
  0x3C, 0x48, 0x3C, 0x45,
  0x3C, 0x41, 0x3C, 0x43,
  0x3C, 0x48, 0x3C, 0x4A,
  0x3C, 0x47, 0x3C, 0x48
};
const int8_t song09[SEQ_LEN] PROGMEM =
{
  M_E4, M_A4, M_C5, M_A5,
  M_B4, M_Eb5, M_G5, M_Eb5,
  M_Gb5, M_TIE, M_E5, M_TIE,
  M_B4, M_TIE, M_G4, M_TIE,
};
const int8_t song10[SEQ_LEN] PROGMEM =
{
  0x3C, 0x48, 0x4B, 0x4A,
  0x48, 0x46, 0x44, 0x43,
  0x41, 0x3F, 0x3E, 0x3F,
  0x3B, 0x3C, 0x3E, 0x37
};
const int8_t song11[SEQ_LEN] PROGMEM =
{
  M_C5, M_C5, M_REST, M_C5,
  M_G5, M_G5, M_REST, M_G5,
  M_A5, M_TIE, M_C5, M_A5,
  M_F5, M_TIE, M_A5, M_F5,
};
const int8_t song12[SEQ_LEN] PROGMEM =
{
  0x3C, 0x3E, 0x40, 0x42,
  0x44, 0x46, 0x48, 0x4A,
  0x4C, 0x4A, 0x48, 0x46,
  0x44, 0x42, 0x40, 0x3E
};
const int8_t song13[SEQ_LEN] PROGMEM =
{
  M_D5, M_D5, M_D5, M_D5,
  M_D5, M_D5, M_D5, M_D5,
  M_F5, M_F5, M_F5, M_F5,
  M_C5, M_C5, M_C5, M_E5
};
const int8_t song14[SEQ_LEN] PROGMEM =
{
  0x3C, 0xFE, 0xFE, 0x3C,
  0xFF, 0x37, 0x37, 0x37,
  0x3C, 0xFE, 0xFE, 0x3C,
  0xFF, 0xFF, 0x3C, 0x3F
};
const int8_t song15[SEQ_LEN] PROGMEM =
{
  M_E4, M_REST, M_A5, M_REST,
  M_E4, M_REST, M_A5, M_E4,
  M_REST, M_E4, M_A5, M_REST,
  M_E4, M_REST, M_A5, M_E4
};
const int8_t song16[SEQ_LEN] PROGMEM =
{
  0x34, 0xFF, 0x45, 0xFF,
  0x34, 0xFF, 0x45, 0x34,
  0xFF, 0x34, 0x45, 0x34,
  0x45, 0x45, 0x34, 0x44
};

#define SEQ_FLAGS_DEFAULT (0x80)

struct Sequencer {
  uint8_t tempo = 120;
  int8_t transpose = 0;
  uint8_t flags = SEQ_FLAGS_DEFAULT; //reserved
  uint8_t synth_param[5];
  int8_t notes[SEQ_LEN];
  uint8_t pos = 0;
  uint8_t prev = 0;
  uint8_t prev2 = 0;
  int16_t dur_cnt = 0;
  bool  playing = true;
}g_sequencer[SEQ_NUM];

uint8_t g_seq_cur = 0;
uint8_t g_seq_nxt = 0;

int8_t g_selector_syn;
int8_t g_selector_seq;
int8_t g_selector_pat;
int8_t g_command_com;

bool g_blink_state;
uint8_t g_blinkcount;
int8_t g_program;
FMop g_fm_operator[2];


#define EEPROM_TOP  (EEPROM_STORAGE_SPACE_START + 256)
#define EEPROM_SIG  (EEPROM_TOP)
#define EEPROM_VER  (EEPROM_TOP+4)
#define EEPROM_NSEQ (EEPROM_TOP+5)
#define EEPROM_SEQ  (EEPROM_TOP+6)
#define SIGNATURE "abFM"
#define VERSION   (1)

#define EEPROM_SEQ_SIZE (24)

bool check_eeprom() {
  char sig[4];
  sig[0] = EEPROM.read(EEPROM_SIG);
  sig[1] = EEPROM.read(EEPROM_SIG + 1);
  sig[2] = EEPROM.read(EEPROM_SIG + 2);
  sig[3] = EEPROM.read(EEPROM_SIG + 3);
  return (memcmp(sig, SIGNATURE, 4) == 0);
}

void regulate_seq(struct Sequencer *s) {
  s->tempo = max(s->tempo, MINTEMPO);
  s->tempo = min(s->tempo, MAXTEMPO);
  s->transpose = max(s->transpose, MINTRANSPOSE);
  s->transpose = min(s->transpose, MAXTRANSPOSE);
  for (uint8_t i = 0; i < 5; i++)
    s->synth_param[i] = min(s->synth_param[i], pgm_read_byte(&g_params[i].max));
  for (uint8_t j = 0; j < SEQ_LEN; j++) {
    int8_t n = s->notes[j];
    if ((MINNOTE > n) && (n >= 0))
      s->notes[j] = MINNOTE;
    else if (n > MAXNOTE)
      s->notes[j] = MAXNOTE;
  }
  s->flags = 0x80; //reserved
}

void read_seq_from_eeprom(struct Sequencer *s, uint16_t index) {
  for (uint8_t i = 0; i < EEPROM_SEQ_SIZE; i++)
    *((uint8_t *)s + i) = EEPROM.read(index + i);
  regulate_seq(s);
}

bool read_eeprom() {
  if (!check_eeprom())
    return false;
  if (EEPROM.read(EEPROM_VER) > VERSION)
    return false;

  uint8_t nseq = EEPROM.read(EEPROM_NSEQ);
  if (nseq > SEQ_NUM) nseq = SEQ_NUM;
  for (uint8_t i = 0; i < nseq; i++)
    read_seq_from_eeprom(&g_sequencer[i], EEPROM_SEQ + i * EEPROM_SEQ_SIZE);
  return true;
}

void write_seq_to_eeprom(struct Sequencer *s, uint16_t index) {
  for (uint8_t i = 0; i < EEPROM_SEQ_SIZE; i++)
    EEPROM.update(index + i, *((byte *)s + i));
}

void write_eeprom() {
  EEPROM.update(EEPROM_TOP, SIGNATURE[0]);
  EEPROM.update(EEPROM_TOP + 1, SIGNATURE[1]);
  EEPROM.update(EEPROM_TOP + 2, SIGNATURE[2]);
  EEPROM.update(EEPROM_TOP + 3, SIGNATURE[3]);
  EEPROM.update(EEPROM_VER, VERSION);
  EEPROM.update(EEPROM_NSEQ, SEQ_NUM);
  for (uint8_t i = 0; i < SEQ_NUM; i++)
    write_seq_to_eeprom(&g_sequencer[i], EEPROM_SEQ + i * EEPROM_SEQ_SIZE);
}

#define COMM_CLOSED   0
#define COMM_OPEN   1
#define COMM_CONNECTED  2
#define COMM_READNUM  11
#define COMM_READNL   13
#define NOTE_END_MARK (0x80)
//note end mark position is just after tempo(1)+transpose(1)+flags(1)
// + synth_params[5]+ notes[SEQ_LEN]
#define END_MARK_POS  (8 + SEQ_LEN) 

uint8_t g_comm_state;

void draw_communication() {
  DRAW_RECT(39, 19, 49, 23, BLACK);
  FILL_RECT(40, 20, 47, 21, WHITE);
  FILL_RECT(49, 24, 29, 8, BLACK);
  DRAW_BITMAP(49, 24, waitingmsg, 29, 8, WHITE);
  FILL_RECT(50, 32, 27, 8, BLACK);
  DRAW_BITMAP(50, 32, cancelbutton, 27, 8, WHITE);
}

void serial_print_hex_2(uint8_t n) {
#ifndef __PROTON__
  if (n < 0x10)
    Serial.print(F("0"));
  Serial.print(n, HEX);
  Serial.print(F(" "));
#endif
}

void dump_seq_header(uint8_t nseq) {
  serial_print_hex_2(SIGNATURE[0]);
  serial_print_hex_2(SIGNATURE[1]);
  serial_print_hex_2(SIGNATURE[2]);
  serial_print_hex_2(SIGNATURE[3]);
  serial_print_hex_2(VERSION);
  serial_print_hex_2(nseq);
}

void dump_seq_to_serial(struct Sequencer *s) {
  for (uint8_t i = 0; i < EEPROM_SEQ_SIZE; i++)
    serial_print_hex_2(*((byte *)s + i));
  serial_print_hex_2(NOTE_END_MARK);
}

bool dump_seq(bool all) {
  bool result = false;
  switch (g_comm_state) {
  case COMM_CLOSED:
#ifndef __PROTON__
    Serial.begin(9600);
#endif
    g_comm_state = COMM_OPEN;
    break;
  case COMM_OPEN:
#ifndef __PROTON__
    if (Serial)
#endif
      g_comm_state = COMM_CONNECTED;
    break;
  case COMM_CONNECTED:
    dump_seq_header(all ? 16 : 1);
#ifndef __PROTON__
    Serial.println();
#endif
    if (all) {
      for (uint8_t i = 0; i < SEQ_NUM; i++) {
#ifndef __PROTON__
        if (i == 0)
          Serial.println(F("#Sequence 1-8"));
        else if (i == 8)
          Serial.println(F("#Sequence 9-16"));
#endif
        dump_seq_to_serial(&g_sequencer[i]);
#ifndef __PROTON__
        Serial.println();
#endif
      }
    }
    else {
      dump_seq_to_serial(&g_sequencer[g_seq_cur]);
#ifndef __PROTON__
      Serial.println();
#endif
    }
#ifndef __PROTON__
    Serial.end();
#endif
    g_comm_state = COMM_CLOSED;
    result = true;
    break;
  default:
    break;
  }
  return result;
}


struct Parser {
  int8_t state;
  int8_t num1st;
  int8_t num2nd;
  int16_t count;
  bool err;
  int8_t nseq;
  struct Sequencer seq;
  int8_t seq_offset;
  int8_t seq_count;
}g_parser;

#define TOKEN_WAIT_NEXT 0
#define TOKEN_READING 1
#define TOKEN_COMMENT 2
#define CHR_TO_NUM(c) (((c) > '9') ? (c) - 'A' + 10 : (c) - '0')

bool recv_token(char ch) {
  bool result = false; // true if a token has been received

  if (('a' <= ch) && (ch <= 'f'))
    ch = ch - 0x20;

  if (g_parser.state == TOKEN_COMMENT) {
    if ((ch == '\n') || (ch == '\r'))
      g_parser.state = TOKEN_WAIT_NEXT;
  }
  else if (ch == '#') {
    g_parser.state = TOKEN_COMMENT;
    if (g_parser.state == TOKEN_READING)
      result = true;
  }
  else if ((('0' <= ch) && (ch <= '9')) ||
    (('A' <= ch) && (ch <= 'F'))) {
    switch (g_parser.state) {
    case TOKEN_WAIT_NEXT:
      g_parser.state = TOKEN_READING;
      g_parser.num2nd = 0;
    case TOKEN_READING:
      g_parser.num1st = g_parser.num2nd;
      g_parser.num2nd = CHR_TO_NUM(ch);
      break;
    }
  }
  else if ((ch == ' ') ||
    (ch == '\n') ||
    (ch == '\r')) {
    switch (g_parser.state) {
    case TOKEN_WAIT_NEXT:
      break;;
    case TOKEN_READING:
      result = true;
      g_parser.state = TOKEN_WAIT_NEXT;
      break;
    default: //ERROR
      g_parser.err = true;
      result = true;
      break;
    }
  }
  return result;
}

bool recv_seq_header(char ch) {
  bool result = false; //true if header has been received

  if (recv_token(ch)) {
    uint8_t c = ((g_parser.num1st << 4) | g_parser.num2nd);
#ifndef __PROTON__
    Serial.print(c, HEX);
    Serial.print(F(" "));
#endif
    switch (g_parser.count) {
    case 0:
    case 1:
    case 2:
    case 3:
      if (c != SIGNATURE[g_parser.count]) {
        g_parser.err = true;
        result = true;
      }
      break;
    case 4:
      if (c < VERSION) {
        g_parser.err = true;
        result = true;
      }
      break;
    case 5:
      g_parser.nseq = c;
      g_parser.err = false;
      result = true;
      break;
    default:
      break;
    }
    g_parser.count++;
  }
  return result;
}

bool recv_seq_body(char ch) {
  bool result = false; //true if one sequence has been received
  uint8_t *p = (uint8_t *)&g_parser.seq;

  if (recv_token(ch)) {
    uint8_t c = ((g_parser.num1st << 4) | g_parser.num2nd);
#ifndef __PROTON__
    Serial.print(c, HEX);
    Serial.print(F(" "));
#endif
    switch (g_parser.seq_offset) {
    case 0:
      if ((c > MAXTEMPO) || (c < MINTEMPO)) {
        g_parser.err = true;
        result = true;
      }
      break;
    case 1:
      if ((((int8_t)c) > MAXTRANSPOSE) || (((int8_t)c) < MINTRANSPOSE)) {
        g_parser.err = true;
        result = true;
      }
      break;
    case 2:
      if (c != SEQ_FLAGS_DEFAULT) {
        g_parser.err = true;
        result = true;
      }
      break;
    case END_MARK_POS:
      if (c == NOTE_END_MARK) {
        result = true;
#ifndef __PROTON__
        Serial.print(F("\r\n1 sequence received.\r\n"));
#endif
      }
      break;
    default:
      break;
    }
    if (!result)
      *(p + g_parser.seq_offset++) = c;
    g_parser.count++;
  }
  return result;
}

void copy_seq(struct Sequencer *s1, const struct Sequencer *s2) {
  s1->tempo = s2->tempo;
  s1->transpose = s2->transpose;
  s1->flags = s2->flags;
  for (uint8_t i = 0; i < 5; i++)
    s1->synth_param[i] = s2->synth_param[i];
  for (uint8_t i = 0; i < SEQ_LEN; i++)
    s1->notes[i] = s2->notes[i];
  s1->playing = false;
}

bool recv_seq(bool all) {
  bool result = false;  // true if done receiving sequences 
  char ch;

#ifdef __PROTON__
  static char dummy1[] = "#\r\n61 62 46 4D 01 01 4A FF 80 05 09 20 02 02 41 45 48 4C 41 45 47 4A 40 43 47 4A 40 43 45 48 80 ";
  static char dummy2[] = "#\r\n61 62 46 4D 01 10 \r\n"
    "3C 00 80 05 02 1B 01 02 43 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 80\r\n"
    "3C 00 80 05 02 1B 01 02 3C 43 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 80\r\n"
    "3C 00 80 05 02 1B 01 02 3C 3C 43 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 80\r\n"
    "3C 00 80 05 02 1B 01 02 3C 3C 3C 43 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 80\r\n"
    "3C 00 80 05 02 1B 01 02 3C 3C 3C 3C 43 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 80\r\n"
    "3C 00 80 05 02 1B 01 02 3C 3C 3C 3C 3C 43 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 80\r\n"
    "3C 00 80 05 02 1B 01 02 3C 3C 3C 3C 3C 3C 43 3C 3C 3C 3C 3C 3C 3C 3C 3C 80\r\n"
    "3C 00 80 05 02 1B 01 02 3C 3C 3C 3C 3C 3C 3C 43 3C 3C 3C 3C 3C 3C 3C 3C 80\r\n"
    "3C 00 80 05 02 1B 01 02 3C 3C 3C 3C 3C 3C 3C 3C 43 3C 3C 3C 3C 3C 3C 3C 80\r\n"
    "3C 00 80 05 02 1B 01 02 3C 3C 3C 3C 3C 3C 3C 3C 3C 43 3C 3C 3C 3C 3C 3C 80\r\n"
    "3C 00 80 05 02 1B 01 02 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 43 3C 3C 3C 3C 3C 80\r\n"
    "3C 00 80 05 02 1B 01 02 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 43 3C 3C 3C 3C 80\r\n"
    "3C 00 80 05 02 1B 01 02 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 43 3C 3C 3C 80\r\n"
    "3C 00 80 05 02 1B 01 02 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 43 3C 3C 80\r\n"
    "3C 00 80 05 02 1B 01 02 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 43 3C 80\r\n"
    "3C 00 80 05 02 1B 01 02 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 3C 43 80\r\n";
  static int16_t dummycount;
  static uint8_t *dummy;
  static int16_t dummysize;
#endif
  switch (g_comm_state) {
  case COMM_CLOSED:
#ifndef __PROTON__
    Serial.begin(9600);
#endif
    g_comm_state = COMM_OPEN;
    break;
  case COMM_OPEN:
#ifndef __PROTON__
    if (Serial)
#endif
    {
#ifndef __PROTON__
      Serial.print(F("send sequences\r\n"));
#endif
      g_comm_state = COMM_CONNECTED;
      g_parser.state = TOKEN_WAIT_NEXT;
      g_parser.count = 0;
      g_parser.err = false;
      g_parser.seq_count = 0;
#ifdef __PROTON__
      dummycount = 0;
#endif
    }
    break;
  case COMM_CONNECTED:
#ifndef __PROTON__
    while (Serial.available() && (g_comm_state == COMM_CONNECTED)) {
      ch = Serial.read();
#else
    if (!all) {
      dummy = (uint8_t *)dummy1;
      dummysize = sizeof(dummy1);
    }
    else {
      dummy = (uint8_t *)dummy2;
      dummysize = sizeof(dummy2);
    }
    while (dummycount < dummysize) {
      ch = dummy[dummycount++];
#endif
      if (g_parser.count < 5)
        result = recv_seq_header(ch); // if header is correct, return value is false
      else if (g_parser.count == 5) {
        result = recv_seq_header(ch) || g_parser.err;
        if (result && (g_parser.count == 6)) {
          result = false;
          g_parser.seq_offset = 0;
#ifndef __PROTON__
          Serial.print(F("\r\nheader is OK\r\n"));
#endif
        }
      }
      else {
        if (recv_seq_body(ch) && !g_parser.err) {
          if (all) {
            copy_seq(&g_sequencer[g_parser.seq_count], &g_parser.seq);
            if (++g_parser.seq_count >= g_parser.nseq)
              result = true;
            else
              g_parser.seq_offset = 0;
          }
          else {
            copy_seq(&g_sequencer[g_seq_cur], &g_parser.seq);
            result = true;
          }
        }
        if (g_parser.err) {
#ifndef __PROTON__
          Serial.print(F("\r\error at position "));
          Serial.print(g_parser.count, DEC);
          Serial.println();
#endif
          result = true;
        }
        if (result) {
#ifndef __PROTON__
          Serial.print(F("\r\ndone.\r\n"));
          Serial.end();
#else
          dummycount = dummysize;
#endif
          g_comm_state = COMM_CLOSED;
        }
      }
    }
    break;
  default:
    break;
    }
  return result;
  }

void blink_indicator_syn(uint8_t s) {
  g_blink_state = !g_blink_state;
  uint8_t x = pgm_read_byte(&selectorindicator[s][0]);
  uint8_t y = pgm_read_byte(&selectorindicator[s][1]);
  uint8_t w = pgm_read_byte(&selectorindicator[s][2]);
  uint8_t h = pgm_read_byte(&selectorindicator[s][3]);
  uint8_t c = g_blink_state ? WHITE : BLACK;
  DRAW_RECT(x, y, w, h, c);
}

void copy_param_to_synth(FMop op[2]) {
  uint8_t *p = g_sequencer[g_seq_cur].synth_param;
  for (uint8_t i = 0; i < 5; i++) {
    if (p[i] > pgm_read_byte(&g_params[i].max)) {
      p[i] = pgm_read_byte(&g_params[i].max);
    }
  }
  op[0].FB = p[0];
  op[0].MULT = p[1];
  op[0].TL = p[2];
  op[0].DR = p[3];
  op[1].DR = p[4];
}

void draw_dial(uint8_t value, const struct SynthNumericParam *p, uint8_t color) {
  long v;
  v = value;
  v = 31 * v / pgm_read_byte(&p->max);
  int8_t dx = pgm_read_byte(&dial_x[v]);
  int8_t dy = pgm_read_byte(&dial_y[v]);
  DRAW_LINE(pgm_read_byte(&p->c_x), pgm_read_byte(&p->c_y), pgm_read_byte(&p->c_x) + dx, pgm_read_byte(&p->c_y) + dy, color);
}

void set_param(uint8_t *value, const struct SynthNumericParam *p, int8_t v) {
  draw_dial(*value, p, BLACK);
  if (v < 0) v = 0;
  if (v > pgm_read_byte(&p->max)) v = pgm_read_byte(&p->max);
  *value = v;
  FILL_RECT(pgm_read_byte(&p->x), pgm_read_byte(&p->y), 12, 7, WHITE);
  draw_2digit(pgm_read_byte(&p->x), pgm_read_byte(&p->y), v, BLACK);
  copy_param_to_synth(g_fm_operator);
  draw_dial(v, p, WHITE);
}

void set_program(int8_t p) {
  if (p < 0) p = 0;
  if (p >= NUM_INST) p = NUM_INST - 1;
  g_program = p;
  FILL_RECT(13, 4, 101, 9, WHITE);
  draw_string(15, 5, progname[p], BLACK);
  uint8_t *param = g_sequencer[g_seq_cur].synth_param;
  for (uint8_t i = 0; i < 5; i++) {
    set_param(param + i, &g_params[i], pgm_read_byte(&preset_progs[p][i]));
  }
}

void set_selector_syn(int8_t s) {
  if (g_blink_state)
    blink_indicator_syn(g_selector_syn);
  if (s >= ParamLast)
    s = ParamDR2;
  if (s <= Param1st)
    s = ParamProg;
  g_selector_syn = s;
  blink_indicator_syn(g_selector_syn);
}

struct KeyStatus {
  bool up;
  bool down;
  bool left;
  bool right;
  bool a;
  bool b;
  uint8_t up_repeat;
  uint8_t down_repeat;
  uint8_t a_repeat;
  uint8_t b_repeat;
} g_keystat;

void change_syn_value(int8_t delta) {
  uint8_t *v = g_sequencer[g_seq_cur].synth_param;
  switch (g_selector_syn) {
  case ParamProg:
    set_program(g_program + delta);
    break;
  case ParamFB:
    set_param(v, &g_params[0], *v + delta);
    break;
  case ParamMult:
    v += 1;
    set_param(v, &g_params[1], *v + delta);
    break;
  case ParamTL:
    v += 2;
    set_param(v, &g_params[2], *v + delta);
    break;
  case ParamDR1:
    v += 3;
    set_param(v, &g_params[3], *v + delta);
    break;
  case ParamDR2:
    v += 4;
    set_param(v, &g_params[4], *v + delta);
    break;
  default:
    break;
  }
}

void draw_playing(struct Sequencer *s) {
  const static uint8_t play[6] PROGMEM = { 0x41, 0x41, 0x63, 0x63, 0x77, 0x77 };
  const static uint8_t stop[6] PROGMEM = { 0x7f, 0x63, 0x63, 0x63, 0x7f, 0x7f };
  FILL_RECT(14, 11, 6, 7, WHITE);
  if (s->playing)
    DRAW_BITMAP(14, 11, play, 6, 7, BLACK);
  else
    DRAW_BITMAP(14, 11, stop, 6, 7, BLACK);
}

void draw_transpose_slider(struct Sequencer *s) {
  const static uint8_t line[5] PROGMEM = { 1, 1, 1, 1, 1 };
  uint8_t y = 10 - 2 * s->transpose;
  DRAW_BITMAP(30, y, line, 5, 1, 3);
}

void draw_keyboard_marker(uint8_t n) {
  const static uint8_t marker[3] PROGMEM = { 2, 7, 2 };
  if ((n >= M_C4) && (n <= (M_B6 + 1))) {
    uint8_t k = (n - M_C4) % 12;
    uint8_t x, y;
    switch (k) {
    case 0: x = 38; y = 12; break;
    case 1: x = 40; y = 4; break;
    case 2: x = 42; y = 12; break;
    case 3: x = 44; y = 4; break;
    case 4: x = 46; y = 12; break;
    case 5: x = 50; y = 12; break;
    case 6: x = 52; y = 4; break;
    case 7: x = 54; y = 12; break;
    case 8: x = 56; y = 4; break;
    case 9: x = 58; y = 12; break;
    case 10: x = 60; y = 4; break;
    case 11: x = 62; y = 12; break;
    }
    x += (n - M_C4) / 12 * 28;
    DRAW_BITMAP(x, y, marker, 3, 3, 3);
  }
}

void blink_indicator_seq(uint8_t s) {
  const static uint8_t marker[7] PROGMEM = { 1, 0, 3, 0x0c, 3, 0, 1 };

  g_blink_state = !g_blink_state;
  if (s == SeqTempo) {
    if (g_blink_state)
      DRAW_RECT(0, 0, 7, 11, WHITE);
    else
      DRAW_RECT(0, 0, 7, 11, BLACK);
  }
  else {
    uint8_t x, y;
    if (s == SeqTrans) {
      x = 29;
      y = 0;
    }
    else {
      x = 8 * (s - SeqNotes);
      y = 19;
    }
    DRAW_BITMAP(x, y, marker, 7, 4, 3);
  }
}

void draw_seq_marker(struct Sequencer *s, uint8_t n) {
  const static uint8_t marker[5] PROGMEM = { 0, 5, 2, 5, 0 };
  if (s->notes[n] > M_REST) {
    uint8_t x = 1 + 8 * n;
    uint8_t y = 24 + (MAXNOTE - s->notes[n]);
    DRAW_BITMAP(x, y, marker, 5, 3, 3);
    draw_keyboard_marker(s->notes[n]);
  }
}

void draw_seq_slider(struct Sequencer *s, uint8_t n) {
  const static uint8_t line[5] PROGMEM = { 2, 2, 2, 2, 2 };
  const static uint8_t tie[5] PROGMEM = { 0, 2, 7, 2, 0 };
  uint8_t x = 1 + 8 * n;

  if (s->notes[n] > M_REST) {
    uint8_t y = 24 + (MAXNOTE - s->notes[n]);
    DRAW_BITMAP(x, y, line, 5, 3, 3);
  }
  else if (s->notes[n] == M_TIE) {
    DRAW_BITMAP(x, 24 + 17, tie, 5, 3, 3);
  }
}

void change_tempo(uint8_t delta) {
  uint8_t t = g_sequencer[g_seq_cur].tempo += delta;
  if (t > MAXTEMPO) t = MAXTEMPO;
  if (t < MINTEMPO) t = MINTEMPO;
  FILL_RECT(8, 2, 18, 7, WHITE);
  if (t > 99) {
    G_DRAWCHAR(8, 2, '0' + t / 100, BLACK);
  }
  draw_2digit(14, 2, t % 100, BLACK);
  g_sequencer[g_seq_cur].tempo = t;
}

void change_trans(int8_t delta) {
  int8_t t = g_sequencer[g_seq_cur].transpose + delta;
  if (t > MAXTRANSPOSE) t = MAXTRANSPOSE;
  if (t < MINTRANSPOSE) t = MINTRANSPOSE;
  draw_transpose_slider(&g_sequencer[g_seq_cur]);
  g_sequencer[g_seq_cur].transpose = t;
  draw_transpose_slider(&g_sequencer[g_seq_cur]);
}

void play_cur_note(struct Sequencer *s, FMop op[2]) {
  if (M_REST < s->notes[s->pos])
    for (uint8_t i = 0; i < 2; i++)
      op[i].gate_on(s->notes[s->pos] + s->transpose * 12, 127);
  else if (M_REST == s->notes[s->pos])
    for (uint8_t i = 0; i < 2; i++)
      op[i].mute();
}

void change_note(int8_t delta) {
  uint8_t idx = g_selector_seq - SeqNotes;
  int8_t n = g_sequencer[g_seq_cur].notes[idx];
  int8_t n2 = n + delta;

  if ((n == M_REST) && (delta > 0))
    n2 = MINNOTE;
  if ((n <= M_TIE) && (delta < 0))
    n2 = MAXNOTE;
  if (n > M_REST) {
    if (n2 < MINNOTE)
      n2 = M_REST;
    else if (n2 > MAXNOTE)
      n2 = M_TIE;
  }

  if (idx == g_sequencer[g_seq_cur].prev2)
    draw_seq_marker(&g_sequencer[g_seq_cur], g_sequencer[g_seq_cur].prev2);
  draw_seq_slider(&g_sequencer[g_seq_cur], idx);
  g_sequencer[g_seq_cur].notes[idx] = n2;
  draw_seq_slider(&g_sequencer[g_seq_cur], idx);
  if (idx == g_sequencer[g_seq_cur].prev2) {
    draw_seq_marker(&g_sequencer[g_seq_cur], g_sequencer[g_seq_cur].prev2);
    play_cur_note(&g_sequencer[g_seq_cur], g_fm_operator);
  }
}


void change_seq_value(uint8_t delta) {
  switch (g_selector_seq) {
  case SeqTempo:
    change_tempo(delta);
    break;
  case SeqTrans:
    change_trans(delta);
    break;
  case Seq1st:
  case SeqLast:
    break;
  default:
    change_note(delta);
    break;
  }

}

void set_selector_seq(int8_t s) {
  if (g_blink_state)
    blink_indicator_seq(g_selector_seq);
  if (s >= SeqLast)
    s = SeqNotes;
  if (s <= SeqTempo)
    s = SeqTempo;
  g_selector_seq = s;
  blink_indicator_seq(g_selector_seq);

  if (!g_sequencer[g_seq_cur].playing && (s >= SeqNotes)) {
    draw_seq_marker(&g_sequencer[g_seq_cur], g_sequencer[g_seq_cur].prev2);
    uint8_t i = s - SeqNotes;
    g_sequencer[g_seq_cur].pos = i;
    g_sequencer[g_seq_cur].prev = i;
    g_sequencer[g_seq_cur].prev2 = i;
    draw_seq_marker(&g_sequencer[g_seq_cur], g_sequencer[g_seq_cur].prev2);
    play_cur_note(&g_sequencer[g_seq_cur], g_fm_operator);
  }
}

void finish_seq(struct Sequencer *s) {
  s->pos = SEQ_LEN;
  s->dur_cnt = 0;
}

bool update_seq(struct Sequencer *s, FMop op[2]) {
  bool done = false;
  if (s->playing) {
    if (0 > (--(s->dur_cnt))) {
      if (s->pos < SEQ_LEN) {
        play_cur_note(s, op);
        int16_t unit_dur = (((DUR_UNIT / (s->tempo)) + 1));
        s->dur_cnt = L_4 * unit_dur - 1;
        s->prev = s->pos++;
      }
      else
        done = true;
    }
  }
  return done;
}

void blink_indicator_pat(uint8_t s) {
  g_blink_state = !g_blink_state;
  if ((Pat16 >= s) && (s >= Pat01)) {
    uint8_t x = 29 + ((s - 1) % 4) * 17;
    uint8_t y = 5 + ((s - 1) / 4) * 10;

    if (g_blink_state)
      DRAW_RECT(x, y, 18, 11, BLACK);
    else {
      DRAW_RECT(x, y, 18, 11, WHITE);
      DRAW_PIXEL(x, y, BLACK);
      DRAW_PIXEL(x + 17, y, BLACK);
      DRAW_PIXEL(x, y + 10, BLACK);
      DRAW_PIXEL(x + 17, y + 10, BLACK);
    }
  }
  else if (PatLast > s) {
    uint8_t x = 28 + (s - PatDump1) * 14;
    uint8_t y = 46;

    if (g_blink_state)
      DRAW_RECT(x, y, 15, 9, BLACK);
    else {
      DRAW_RECT(x, y, 15, 9, WHITE);
    }
  }
}

void set_selector_pat(int8_t s) {
  if (g_blink_state)
    blink_indicator_pat(g_selector_pat);
  if (s >= PatLast)
    s = PatSave;
  if (s <= Pat1st)
    s = Pat01;
  g_selector_pat = s;
  blink_indicator_pat(g_selector_pat);
}


void up_released() {
  switch (g_mode) {
  case Synthesizer:
    change_syn_value(1);
    break;
  case Sequencer:
    change_seq_value(1);
    break;
  case Pattern:
    if (g_selector_pat == Pat1st)
      set_selector_pat(Pat01 + g_seq_cur);
    else
      set_selector_pat(g_selector_pat - 4 - (g_selector_pat == PatSave));
    break;
  default:
    break;
  }
}

void down_released() {
  switch (g_mode) {
  case Synthesizer:
    change_syn_value(-1);
    break;
  case Sequencer:
    change_seq_value(-1);
    break;
  case Pattern:
    if (g_selector_pat == Pat1st)
      set_selector_pat(Pat01 + g_seq_cur);
    else
      set_selector_pat(g_selector_pat + 4);
    break;
  default:
    break;
  }
}

void left_released() {
  switch (g_mode) {
  case Synthesizer:
    set_selector_syn(g_selector_syn - 1);
    break;
  case Sequencer:
    set_selector_seq(g_selector_seq - 1);
    break;
  case Pattern:
    if (g_selector_pat == Pat1st)
      set_selector_pat(Pat01 + g_seq_cur);
    else
      set_selector_pat(g_selector_pat - 1);
    break;
  default:
    break;
  }
}

void right_released() {
  switch (g_mode) {
  case Synthesizer:
    set_selector_syn(g_selector_syn + 1);
    break;
  case Sequencer:
    set_selector_seq(g_selector_seq + 1);
    break;
  case Pattern:
    if (g_selector_pat == Pat1st)
      set_selector_pat(Pat01 + g_seq_cur);
    else
      set_selector_pat(g_selector_pat + 1);
    break;
  default:
    break;
  }
}


bool process_button(bool *state, uint8_t *repeat_count, uint8_t keycode, void(*release_func)(), void(*repeat_func)()) {
  uint8_t dummy = 255;
  bool  result = false;

  if (repeat_count == NULL) {
    repeat_count = &dummy;
  }

  if (*state) {
    if (KEY_NOT_PRESSED(keycode)) {
      *state = false;
      release_func();
      result = true;
    }
    else if ((*repeat_count)-- == 0) {
      *repeat_count = 1;
      repeat_func();
      result = true;
    }
  }
  else if (KEY_PRESSED(keycode)) {
    *state = true;
    *repeat_count = 5;
  }
  return result;
}

void init_globals() {
  setup_synth(g_fm_operator);
  g_selector_syn = ParamProg;
  g_selector_seq = SeqTempo;
  g_program = 0;
  g_keystat = { false, false, false, false, false, false, 0, 0, 0, 0 };
}

void setup_sequence(struct Sequencer *s, const int8_t synth[], uint8_t t, int8_t o, const int8_t *song) {
  s->tempo = t;
  s->transpose = o;
  s->flags = 0;
  for (uint8_t i = 0; i < 5; i++)
    s->synth_param[i] = pgm_read_byte(&synth[i]);
  for (uint8_t i = 0; i < SEQ_LEN; i++)
    s->notes[i] = pgm_read_byte(song + i);
  s->dur_cnt = 0;
  s->playing = 0;
  s->pos = 0;
}

void setup_all_seq() {
  setup_sequence(&g_sequencer[0], preset_progs[0], 60, 0, song01);
  setup_sequence(&g_sequencer[1], preset_progs[0], 60, 0, song02);
  setup_sequence(&g_sequencer[2], preset_progs[1], 96, 1, song03);
  setup_sequence(&g_sequencer[3], preset_progs[1], 96, 1, song04);
  setup_sequence(&g_sequencer[4], preset_progs[1], 96, 1, song05);
  setup_sequence(&g_sequencer[5], preset_progs[2], 74, -1, song06);
  setup_sequence(&g_sequencer[6], preset_progs[3], 192, 0, song07);
  setup_sequence(&g_sequencer[7], preset_progs[3], 148, 0, song08);
  setup_sequence(&g_sequencer[8], preset_progs[4], 76, 0, song09);
  setup_sequence(&g_sequencer[9], preset_progs[4], 126, 0, song10);
  setup_sequence(&g_sequencer[10], preset_progs[5], 130, -1, song11);
  setup_sequence(&g_sequencer[11], preset_progs[5], 240, 0, song12);
  setup_sequence(&g_sequencer[12], preset_progs[6], 120, -1, song13);
  setup_sequence(&g_sequencer[13], preset_progs[6], 115, -1, song14);
  setup_sequence(&g_sequencer[14], preset_progs[7], 130, -1, song15);
  setup_sequence(&g_sequencer[15], preset_progs[7], 130, -1, song16);
}

void draw_seq_thumb(uint8_t x, uint8_t y, uint8_t s) {
  for (uint8_t i = 0; i < SEQ_LEN; i++) {
    int8_t n = g_sequencer[s].notes[i];
    if (n > M_REST) {
      DRAW_PIXEL(x + i, y + (MAXNOTE - n) / 4, BLACK);
    }
  }
}

void draw_sequencer_sliders(uint8_t s) {
  draw_transpose_slider(&g_sequencer[s]);
  for (uint8_t i = 0; i < SEQ_LEN; i++)
    draw_seq_slider(&g_sequencer[s], i);
}

void draw_screen() {
  uint8_t *param = g_sequencer[g_seq_cur].synth_param;
  g_blink_state = false;
  g_blinkcount = 0;

  switch (g_mode) {
  case Synthesizer:
    G_CLEAR();
    arduboy.drawBitmap(0, 0, synth_img, 128, 64, WHITE);
    draw_string(15, 5, progname[g_program], BLACK);
    for (uint8_t i = 0; i < 5; i++) {
      set_param(param + i, &g_params[i], param[i]);
    }
    blink_indicator_syn(g_selector_syn);
    break;
  case Sequencer:
    G_CLEAR();
    arduboy.drawBitmap(0, 0, sequencer_img, 128, 64, WHITE);
    draw_playing(&g_sequencer[g_seq_cur]);
    draw_sequencer_sliders(g_seq_cur);
    change_tempo(0);
    draw_seq_marker(&g_sequencer[g_seq_cur], g_sequencer[g_seq_cur].prev2);
    blink_indicator_seq(g_selector_seq);
    break;
  case Pattern:
    DRAW_RECT(25, 1, 77, 62, BLACK);
    DRAW_RECT(26, 2, 75, 60, BLACK);
    FILL_RECT(27, 3, 73, 58, WHITE);
    for (uint8_t j = 0; j < (SEQ_NUM / 4); j++)
      for (uint8_t i = 0; i < 4; i++) {
        uint8_t x = 29 + 17 * i;
        uint8_t y = 5 + 10 * j;
        DRAW_PIXEL(x, y, BLACK);
        DRAW_PIXEL(x + 17, y, BLACK);
        DRAW_PIXEL(x, y + 10, BLACK);
        DRAW_PIXEL(x + 17, y + 10, BLACK);
        draw_seq_thumb(x, y, i + 4 * j);
      }
    FILL_RECT(29, 48, 68, 12, BLACK);
    DRAW_BITMAP(29, 48, panel, 68, 12, WHITE);
    break;
  }
}

void a_released() {
  switch (g_mode) {
  case Pattern:
    switch (g_selector_pat) {
    case Pat1st:
      g_selector_pat = Pat01 + g_seq_cur;
      blink_indicator_pat(g_selector_pat);
      break;
    case PatDump1:
    case PatDumpAll:
    case PatLoad1:
    case PatLoadAll:
      g_sequencer[g_seq_cur].playing = false;
      g_mode = Communication;
      g_command_com = g_selector_pat;
      g_comm_state = COMM_CLOSED;
      draw_communication();
      break;
    case PatSave:
      write_eeprom();
      read_eeprom();
      g_mode = g_prev_mode;
      draw_screen();
      break;
    default:
      g_seq_nxt = g_selector_pat - Pat01;
      if (!g_sequencer[g_seq_cur].playing) {
        finish_seq(&g_sequencer[g_seq_cur]);
        g_sequencer[g_seq_cur].playing = true;
        g_sequencer[g_seq_nxt].playing = false;
      }
      else {
        g_sequencer[g_seq_nxt].playing = true;
      }
      g_mode = g_prev_mode;
      draw_screen();
    }
    break;
  case Communication:
#ifndef __PROTON__
    Serial.println();
    Serial.print(g_parser.count, DEC);
    Serial.print(F(" bytes received.\r\naborted."));
    Serial.end();
#endif
    g_mode = Pattern;
    draw_screen();
    break;
  default:
    g_sequencer[g_seq_cur].playing = !g_sequencer[g_seq_cur].playing;
    if (g_mode == Sequencer) {
      draw_playing(&g_sequencer[g_seq_cur]);
    }
  }
}

void b_released() {
  g_keystat = { false, false, false, false, false, false, 0, 0, 0, 0 };
  switch (g_mode) {
  case Synthesizer:
    g_mode = Sequencer;
    draw_screen();
    break;
  case Sequencer:
    g_mode = Synthesizer;
    draw_screen();
    break;
  case Pattern:
    g_mode = g_prev_mode;
    draw_screen();
    break;
  case Communication:
#ifndef __PROTON__
    Serial.println();
    Serial.print(g_parser.count, DEC);
    Serial.print(F(" bytes received.\r\naborted."));
    Serial.end();
#endif
    g_mode = Pattern;
    draw_screen();
    break;
  default:
    break;
  }
}

void a_long_press() {
  if ((g_mode == Synthesizer) || (g_mode == Sequencer)) {
    g_prev_mode = g_mode;
    g_mode = Pattern;
    g_selector_pat = Pat1st;
    draw_screen();
  }
}

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(15);

  g_mode = Synthesizer;
  init_globals();
  if (KEY_PRESSED(A_BUTTON))
    setup_all_seq();
  else if (!read_eeprom())
    setup_all_seq();
  g_seq_cur = 0;
  g_sequencer[g_seq_cur].playing = true;

  draw_screen();
  set_program(g_program);
  arduboy.display();
}

void loop() {
  if (update_synth(g_fm_operator)) {
    static bool seq_changed = false;
    static uint8_t prev_seq;

    if (update_seq(&g_sequencer[g_seq_cur], g_fm_operator)) {
      if (g_seq_cur == g_seq_nxt) {
        g_sequencer[g_seq_cur].pos = 0;
        g_sequencer[g_seq_cur].dur_cnt = 0;
      }
      else {
        seq_changed = true;
        prev_seq = g_seq_cur;
        g_sequencer[g_seq_cur].playing = false;
        g_sequencer[g_seq_nxt].pos = 0;
        g_sequencer[g_seq_nxt].prev = g_sequencer[g_seq_cur].prev;
        g_seq_cur = g_seq_nxt;
        copy_param_to_synth(g_fm_operator);
      }
    }

    if (!(arduboy.nextFrame()))
      return;

    static bool scrn_update = false;

    if (scrn_update) {
      arduboy.display();
      scrn_update = false;
    }

    scrn_update |= process_button(&g_keystat.up, &g_keystat.up_repeat, UP_BUTTON, up_released, up_released);
    scrn_update |= process_button(&g_keystat.down, &g_keystat.down_repeat, DOWN_BUTTON, down_released, down_released);
    scrn_update |= process_button(&g_keystat.left, NULL, LEFT_BUTTON, left_released, left_released);
    scrn_update |= process_button(&g_keystat.right, NULL, RIGHT_BUTTON, right_released, right_released);
    scrn_update |= process_button(&g_keystat.a, &g_keystat.a_repeat, A_BUTTON, a_released, a_long_press);
    scrn_update |= process_button(&g_keystat.b, NULL, B_BUTTON, b_released, b_released);

    switch (g_mode) {
    case Synthesizer:
      if (seq_changed) {
        for (uint8_t i = 0; i < 5; i++) {
          draw_dial(g_sequencer[prev_seq].synth_param[i], &g_params[i], BLACK);
          draw_dial(g_sequencer[g_seq_cur].synth_param[i], &g_params[i], WHITE);
        }
        seq_changed = false;
        scrn_update = true;
      }
      break;
    case Sequencer:
      if (g_sequencer[g_seq_cur].prev != g_sequencer[g_seq_cur].pos) {
        draw_seq_marker(&g_sequencer[g_seq_cur], g_sequencer[g_seq_cur].prev2);
        if (seq_changed) {
          draw_seq_marker(&g_sequencer[prev_seq], g_sequencer[prev_seq].prev2);
          if (prev_seq != g_seq_cur) {
            draw_sequencer_sliders(prev_seq);
            draw_sequencer_sliders(g_seq_cur);
          }
          seq_changed = false;
          change_tempo(0);
          draw_seq_marker(&g_sequencer[g_seq_cur], g_sequencer[g_seq_cur].prev2);
          blink_indicator_seq(g_selector_seq);
        }
        draw_seq_marker(&g_sequencer[g_seq_cur], g_sequencer[g_seq_cur].prev);
        g_sequencer[g_seq_cur].prev2 = g_sequencer[g_seq_cur].prev;
        g_sequencer[g_seq_cur].prev = g_sequencer[g_seq_cur].pos;
        scrn_update = true;
      }
      break;
    case Communication:
      switch (g_command_com) {
      case PatDump1:
        if (dump_seq(false)) {
          g_mode = g_prev_mode;
          draw_screen();
          scrn_update = true;
        }
        break;
      case PatDumpAll:
        if (dump_seq(true)) {
          g_mode = g_prev_mode;
          draw_screen();
          scrn_update = true;
        }
        break;
      case PatLoad1:
        if (recv_seq(false)) {
          g_mode = g_prev_mode;
          draw_screen();
          scrn_update = true;
          if (g_mode != Synthesizer)
            copy_param_to_synth(g_fm_operator);
        }
        break;
      case PatLoadAll:
        if (recv_seq(true)) {
          g_mode = g_prev_mode;
          draw_screen();
          scrn_update = true;
          if (g_mode != Synthesizer)
            copy_param_to_synth(g_fm_operator);
        }
        break;
      }
      break;
    }
  }
}

