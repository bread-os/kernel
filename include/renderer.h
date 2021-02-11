#pragma once
#include "share.h"

typedef struct {
  uint32_t x;
  uint32_t y;
} Point;

typedef struct {
  FrameBuffer *frameBuffer;
  PSF1_FONT *psf_1_font;
  uint32_t color;
  Point point;
} Renderer;
static Renderer renderer;

void initRenderer(FrameBuffer *framebuffer,
                  PSF1_FONT *psf_1_font);

// kernel print
void kprint(const char *str, ...);
