int animationFrames = 28;

int animationDelays[] = { 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 2000 };

// Animation is designed for 8x8 pixels
uint8_t animation[][16] = {
  { 0x3, 0x0, 0x3, 0x0, 0x3, 0x0, 0x3, 0x0, 0x3, 0x0, 0x3, 0x0, 0x3, 0x0, 0x3, 0x0 },
  { 0xf, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0x0 },
  { 0x3f, 0x0, 0x3f, 0x0, 0x3f, 0x0, 0x3f, 0x0, 0x3f, 0x0, 0x3f, 0x0, 0x3f, 0x0, 0x3f, 0x0 },
  { 0xff, 0x0, 0xff, 0x0, 0xff, 0x0, 0xff, 0x0, 0xff, 0x0, 0xff, 0x0, 0xff, 0x0, 0xff, 0x0 },
  { 0xff, 0x3, 0xff, 0x3, 0xff, 0x3, 0xff, 0x3, 0xff, 0x3, 0xff, 0x3, 0xff, 0x3, 0xff, 0x3 },
  { 0xff, 0xf, 0xff, 0xf, 0xff, 0xf, 0xff, 0xf, 0xff, 0xf, 0xff, 0xf, 0xff, 0xf, 0xff, 0xf },
  { 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f },
  { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff },
  { 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa },
  { 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55 },
  { 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x45, 0x51 },
  { 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x45, 0x51, 0x0, 0x0 },
  { 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x45, 0x51, 0x0, 0x0, 0x0, 0x0 },
  { 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x45, 0x51, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
  { 0x55, 0x55, 0x55, 0x55, 0x45, 0x51, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
  { 0x55, 0x55, 0x45, 0x51, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
  { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
  { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x0 },
  { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0x40, 0x0, 0x40, 0x0 },
  { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x80, 0x0, 0x40, 0x0, 0x40, 0x0, 0x0, 0x0 },
  { 0x0, 0x0, 0x0, 0x0, 0xc0, 0x0, 0x80, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
  { 0x0, 0x0, 0x0, 0x0, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
  { 0x0, 0x0, 0xc0, 0x0, 0xf0, 0x3, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
  { 0xc0, 0x0, 0x10, 0x1, 0xcc, 0xc, 0x10, 0x1, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
  { 0x60, 0x2, 0x8, 0x8, 0x4, 0x4, 0x8, 0x8, 0x60, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
  { 0x4, 0x4, 0x1, 0x10, 0x0, 0x0, 0x1, 0x10, 0x4, 0x4, 0x10, 0x1, 0x0, 0x0, 0x0, 0x0 },
  { 0x1, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x10, 0x0, 0x0, 0x0, 0x0 },
  { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 }
};
