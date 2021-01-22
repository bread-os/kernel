#include "allocator.h"

static size_t getMemorySize(EFI_MEMORY_DESCRIPTOR *mMap, size_t mMapSize, size_t mMapDescriptorSize) {
  const uint64_t mMapEntries = mMapSize / mMapDescriptorSize;
  static uint64_t memorySizeBytes = 0;
  if (memorySizeBytes > 0) return memorySizeBytes;
  for (size_t i = 0; i < mMapEntries; i++) {
    EFI_MEMORY_DESCRIPTOR *descriptor = mMap + i;
    memorySizeBytes += descriptor->numberOfPages * SIZE_4KB;
  }
  return memorySizeBytes;
}

void initBitmap(size_t bitmapSize, uint8_t *bufferAddress) {
  bitmap.size = bitmapSize;
  bitmap.buffer = bufferAddress;
}

int bitmapGet(size_t index) {
  size_t byteIndex = index / 8;
  uint8_t hax = 0b10000000 >> (index % 8);
  if ((bitmap.buffer[byteIndex] & hax) > 0) {
    return 1;
  } else {
    return 0;
  }
}

int bitmapSet(size_t index, int value) {
  const size_t byteIndex = index / 8;
  const uint8_t hax = 0b10000000 >> (index % 8);
  bitmap.buffer[byteIndex] &= ~hax;
  if (value) {
    bitmap.buffer[byteIndex] |= hax;
  }
  return (bitmap.buffer[byteIndex] >> (index % 8));
}

void lockPage(void *address) {
  const size_t index = (uint64_t) address / SIZE_4KB;
  if (bitmapGet(index) == LOCKED) return;
  bitmapSet(index, LOCKED);
  allocator.freeMemory -= SIZE_4KB;
  allocator.usedMemory += SIZE_4KB;
}

void unlockPage(void *address) {
  const size_t index = (uint64_t) address / SIZE_4KB;
  if (bitmapGet(index) == UNLOCK) return;
  bitmapSet(index, UNLOCK);
  allocator.freeMemory += SIZE_4KB;
  allocator.usedMemory -= SIZE_4KB;
}

void initAllocator(EFI_MEMORY_DESCRIPTOR *mMap, size_t mMapSize, size_t mMapDescriptorSize) {
  const uint64_t mMapEntries = mMapSize / mMapDescriptorSize;
  struct LargestFreeMemorySegment {
    uint64_t address;
    size_t size;
  } largestFreeMemorySegment = {0, 0};
  for (size_t i = 0; i < mMapEntries; i++) {
    EFI_MEMORY_DESCRIPTOR *descriptor = mMap + i;
    if (descriptor->type == 7) {
      // EfiConventionalMemory
      if (descriptor->numberOfPages * SIZE_4KB > largestFreeMemorySegment.size) {
        largestFreeMemorySegment.address = descriptor->physicalStart;
        largestFreeMemorySegment.size = descriptor->numberOfPages * SIZE_4KB;
      }
    }
  }
  const size_t memorySize = getMemorySize(mMap, mMapSize, mMapDescriptorSize);
  allocator.freeMemory = memorySize;
  const size_t bitmapSize = memorySize / SIZE_4KB / 8 + 1;
  initBitmap(bitmapSize, (uint8_t *) largestFreeMemorySegment.address);
}
