#pragma once
#include "share.h"

typedef struct {
  uint64_t freeMemory;
  uint64_t reservedMemory;
  uint64_t usedMemory;
} Allocator;

typedef struct {
  size_t size;
  uint8_t *buffer;
} Bitmap;
static Bitmap bitmap;
static Allocator allocator;

enum PageStatus {
  UNLOCK = 0,
  LOCKED = 1
};

void initBitmap(size_t bitmapSize, uint8_t *bufferAddress);
void initAllocator(EFI_MEMORY_DESCRIPTOR *mMap, size_t mMapSize, size_t mMapDescriptorSize);
void lockPage(void *address);
void unlockPage(void *address);
// todo
void *allocatePage();
// todo
void *freePage(void *address);
