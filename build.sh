#!/bin/bash
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=../cmake/gcc-arm-none-eabi.cmake
cmake --build build
cd build
arm-none-eabi-objcopy -O binary my_rtos.elf my_rtos.bin
arm-none-eabi-objcopy -O ihex   my_rtos.elf my_rtos.hex
cd ..
