cmake_minimum_required(VERSION 3.16)
project(kernel C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-ffreestanding -O2 -Wall -Wextra -mno-red-zone")

set(KERNEL_BIN "kernel.bin")

enable_language(ASM_NASM)

include_directories(include)

add_executable(${KERNEL_BIN}
        src/main.c)
set_target_properties(${KERNEL_BIN} PROPERTIES LINK_FLAGS "-T ${CMAKE_SOURCE_DIR}/linker.lds -static -Bsymbolic -nostdlib -ffreestanding -nostdlib")
