#include <stddef.h>
#include <stdint.h>

typedef struct {
  void *BaseAddress;
  size_t BufferSize;
  unsigned int Width;
  unsigned int Height;
  unsigned int PixelsPerScanLine;
} FrameBuffer;

typedef struct {
  unsigned char magic[2];
  unsigned char mode;
  unsigned char charsize;
} PSF1_HEADER;

typedef struct {
  PSF1_HEADER *psf1_Header;
  void *glyphBuffer;
} PSF1_FONT;

typedef struct {
  FrameBuffer *framebuffer;
  PSF1_FONT *psf_1_font;
  void *mMap;
  uint64_t mMapSize;
  uint64_t mMapDescriptorSize;
  void *rsdp;
} BootInfo;
