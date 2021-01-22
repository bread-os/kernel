#include "main.h"

extern uint64_t kernel_start_address;
extern uint64_t kernel_end_address;

void kernel_start(BootInfo *boot_info) {
  initRenderer(boot_info->framebuffer, boot_info->psf_1_font);
  initAllocator(boot_info->mMap, boot_info->mMapSize, boot_info->mMapDescriptorSize);
  uint64_t mMapEntries = boot_info->mMapSize / boot_info->mMapDescriptorSize;
}
