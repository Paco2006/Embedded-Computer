#!/bin/bash
set -e

NAME="$1"
JUNK_DIR="junk"

mkdir -p "$JUNK_DIR"

# Include path if you have it
INCLUDE_DIR="./libs"

# Compile
arm-none-eabi-g++ -mcpu=cortex-m7 -mthumb -O2 -nostdlib -ffreestanding -fno-exceptions -fno-rtti -fno-builtin \
    -fPIC -fdata-sections -ffunction-sections -fno-merge-constants\
    -I"$INCLUDE_DIR" \
    -c "$NAME.cpp" -o "$JUNK_DIR/$NAME.o"

# Link
arm-none-eabi-ld -T teensy.ld -o "$JUNK_DIR/$NAME.elf" "$JUNK_DIR/$NAME.o"

# Convert to binary
arm-none-eabi-objcopy -O binary "$JUNK_DIR/$NAME.elf" "$NAME.bin"

echo "Build complete: $NAME.bin"
