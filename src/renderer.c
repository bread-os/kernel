#include "renderer.h"

void initRenderer(FrameBuffer *framebuffer,
                       PSF1_FONT *psf_1_font) {
  renderer.frameBuffer = framebuffer;
  renderer.psf_1_font = psf_1_font;
  renderer.color = 0xffffffff;
  renderer.point = (Point) {0, 0};
}
