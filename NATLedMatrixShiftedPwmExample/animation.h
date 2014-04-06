int animationFrames = 15;

int animationDelays[] = { 200, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40 };

// Animation is designed for 8x8 pixels
uint8_t animation[][32] = {
  { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
  { 0x0, 0x0, 0xee, 0xee, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xee, 0xee, 0x0, 0x0 },
  { 0x0, 0x0, 0xcc, 0xcc, 0x0, 0x0, 0xee, 0xee, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xee, 0xee, 0x0, 0x0, 0xcc, 0xcc, 0x0, 0x0 },
  { 0x0, 0x0, 0xaa, 0xaa, 0x0, 0x0, 0xcc, 0xcc, 0x0, 0x0, 0xee, 0xee, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xee, 0xee, 0x0, 0x0, 0xcc, 0xcc, 0x0, 0x0, 0xaa, 0xaa, 0x0, 0x0 },
  { 0x0, 0x0, 0x88, 0x88, 0x0, 0x0, 0xaa, 0xaa, 0x0, 0x0, 0xcc, 0xcc, 0x0, 0x0, 0xee, 0xee, 0xee, 0xee, 0x0, 0x0, 0xcc, 0xcc, 0x0, 0x0, 0xaa, 0xaa, 0x0, 0x0, 0x88, 0x88, 0x0, 0x0 },
  { 0x0, 0x0, 0x66, 0x66, 0x0, 0x0, 0x88, 0x88, 0x0, 0x0, 0xaa, 0xaa, 0xee, 0xee, 0xcc, 0xcc, 0xcc, 0xcc, 0xee, 0xee, 0xaa, 0xaa, 0x0, 0x0, 0x88, 0x88, 0x0, 0x0, 0x66, 0x66, 0x0, 0x0 },
  { 0x0, 0x0, 0x44, 0x44, 0x0, 0x0, 0x66, 0x66, 0xee, 0xee, 0x88, 0x88, 0xcc, 0xcc, 0xaa, 0xaa, 0xaa, 0xaa, 0xcc, 0xcc, 0x88, 0x88, 0xee, 0xee, 0x66, 0x66, 0x0, 0x0, 0x44, 0x44, 0x0, 0x0 },
  { 0x0, 0x0, 0x22, 0x22, 0xee, 0xee, 0x44, 0x44, 0xcc, 0xcc, 0x66, 0x66, 0xaa, 0xaa, 0x88, 0x88, 0x88, 0x88, 0xaa, 0xaa, 0x66, 0x66, 0xcc, 0xcc, 0x44, 0x44, 0xee, 0xee, 0x22, 0x22, 0x0, 0x0 },
  { 0xee, 0xee, 0x0, 0x0, 0xcc, 0xcc, 0x22, 0x22, 0xaa, 0xaa, 0x44, 0x44, 0x88, 0x88, 0x66, 0x66, 0x66, 0x66, 0x88, 0x88, 0x44, 0x44, 0xaa, 0xaa, 0x22, 0x22, 0xcc, 0xcc, 0x0, 0x0, 0xee, 0xee },
  { 0xcc, 0xcc, 0x0, 0x0, 0xaa, 0xaa, 0x0, 0x0, 0x88, 0x88, 0x22, 0x22, 0x66, 0x66, 0x44, 0x44, 0x44, 0x44, 0x66, 0x66, 0x22, 0x22, 0x88, 0x88, 0x0, 0x0, 0xaa, 0xaa, 0x0, 0x0, 0xcc, 0xcc },
  { 0xaa, 0xaa, 0x0, 0x0, 0x88, 0x88, 0x0, 0x0, 0x66, 0x66, 0x0, 0x0, 0x44, 0x44, 0x22, 0x22, 0x22, 0x22, 0x44, 0x44, 0x0, 0x0, 0x66, 0x66, 0x0, 0x0, 0x88, 0x88, 0x0, 0x0, 0xaa, 0xaa },
  { 0x88, 0x88, 0x0, 0x0, 0x66, 0x66, 0x0, 0x0, 0x44, 0x44, 0x0, 0x0, 0x22, 0x22, 0x0, 0x0, 0x0, 0x0, 0x22, 0x22, 0x0, 0x0, 0x44, 0x44, 0x0, 0x0, 0x66, 0x66, 0x0, 0x0, 0x88, 0x88 },
  { 0x66, 0x66, 0x0, 0x0, 0x44, 0x44, 0x0, 0x0, 0x22, 0x22, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x22, 0x22, 0x0, 0x0, 0x44, 0x44, 0x0, 0x0, 0x66, 0x66 },
  { 0x44, 0x44, 0x0, 0x0, 0x22, 0x22, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x22, 0x22, 0x0, 0x0, 0x44, 0x44 },
  { 0x22, 0x22, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x22, 0x22 }
};

