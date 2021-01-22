#pragma once
#include <stddef.h>
#include <stdint.h>

#define SIZE_4KB 0x00001000

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

// see edk2/MdePkg/Include/Uefi/UefiSpec.h
typedef struct {
  uint32_t type;
  uint64_t physicalStart;
  uint64_t virtualStart;
  uint64_t numberOfPages;
  uint64_t attribute;
} EFI_MEMORY_DESCRIPTOR;

typedef struct {
  FrameBuffer *framebuffer;
  PSF1_FONT *psf_1_font;
  EFI_MEMORY_DESCRIPTOR *mMap;
  uint64_t mMapSize;
  uint64_t mMapDescriptorSize;
  void *rsdp;
} BootInfo;
