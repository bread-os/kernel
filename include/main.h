#pragma once
#include <stddef.h>
#include <stdint.h>

#include "allocator.h"
#include "share.h"
#include "renderer.h"
#include "exception.h"

void kernel_start(BootInfo *boot_info);
