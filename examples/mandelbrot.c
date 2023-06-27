/*
    TODO: Maybe mul() here is a good candidate for asm().
    A handwritten implementation that uses the working stack is faster:

    @mul_
        ( xx yy )
        LIT2r 0001
        SWP2 DUP2 #8000 LTH2 ?&posx
        #0000 SWP2 SUB2 LIT2r ffff MUL2r &posx
        SWP2 DUP2 #8000 LTH2 ?&posy
        #0000 SWP2 SUB2 LIT2r ffff MUL2r &posy
        ( xx yy )
        OVR2k OVR2k
        ( xx yy xx yy xx yy xx yy )
        #00ff AND2 SWP2 #00ff AND2 MUL2 #08 SFT2
        ( xx yy xx yy xx yy AA )
        ROT2 #08 SFT2 ROT2 #00ff AND2 MUL2 ADD2
        ( xx yy xx yy AA+BB )
        ROT2 #00ff AND2 ROT2 #08 SFT2 MUL2 ADD2
        ( xx yy AA+BB+CC )
        ROT2 #08 SFT2 ROT2 #08 SFT2 MUL2 #80 SFT2 ADD2
        ( AA+BB+CC+DD )
        STH2r MUL2
        JMP2r
*/

#include <uxn.h>

// Multiply two 8.8 fixed point numbers.
int mul(unsigned x, unsigned y) {
  int sign = 1;
  if (x & 0x8000)
    x = -x, sign *= -1;
  if (y & 0x8000)
    y = -y, sign *= -1;
  return sign * (((y & 0xff) * (x & 0xff) >> 8) + (y & 0xff) * (x >> 8) +
                 (y >> 8) * (x & 0xff) + ((y >> 8) * (x >> 8) << 8));
}

int x0, y0, x, y, i, xx, yy, tmp;

void main(void) {
  set_palette(0x08df, 0x12bf, 0x549d);
  set_screen_size(320, 288);
  for (x0 = -256; x0 < 64; ++x0) {
    for (y0 = -144; y0 <= 0; ++y0) {
      x = 0;
      y = 0;
      for (i = 0; i < 25; ++i) {
        if ((xx = mul(x, x)) + (yy = mul(y, y)) > 4 * 256)
          break;
        tmp = xx - yy + x0 * 2;
        y = 2 * mul(x, y) + y0 * 2;
        x = tmp;
      }
      tmp = (unsigned)(i + (x0 + y0 & 1)) / 8;
      set_screen_xy(x0 + 256, y0 + 144);
      draw_pixel(tmp);
      set_screen_y(144 - y0);
      draw_pixel(tmp);
    }
  }
}
