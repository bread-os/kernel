#include "renderer.h"

void initRenderer(FrameBuffer *framebuffer,
                  PSF1_FONT *psf_1_font) {
  renderer.frameBuffer = framebuffer;
  renderer.psf_1_font = psf_1_font;
  renderer.color = 0xffffffff;
  renderer.point = (Point) {0, 0};
}

static void putchar(const char ch, const size_t xOff, const size_t yOff) {
  const PSF1_FONT *psf = renderer.psf_1_font;
  const void *baseAddress = renderer.frameBuffer->BaseAddress;
  char *fontAddress = (char *) psf->glyphBuffer + (ch * psf->psf1_Header->charsize);
  for (size_t y = yOff; y < (yOff + 16); y++) {
    for (size_t x = xOff; x < (xOff + 16); x++) {
      if ((*fontAddress & (0b10000000 >> (x - xOff))) > 0) {
        *(uint32_t *) (baseAddress + x + (y * renderer.frameBuffer->PixelsPerScanLine)) = renderer.color;
      }
      fontAddress++;
    }
  }
}

// kernel print
void kprint(const char *str, ...) {
  int pos = 0;
  while (str[pos++] != '\0') {
    if (renderer.point.x > renderer.frameBuffer->Width) {
      renderer.point.x = 0;
    }
    if (renderer.point.y > renderer.frameBuffer->Height) {
      renderer.point.y = 0;
    }
    putchar(str[pos], renderer.point.x, renderer.point.y);
    renderer.point.x += 8;
    renderer.point.y += 16;
  }
}
