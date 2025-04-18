# Embedded-Computer
## What is this project?

This project is a low-level runtime and operating system for the Teensy 4.0 microcontroller that enables dynamic loading and execution of compiled code directly from RAM. Instead of flashing all code to flash memory, this system lets you upload compiled binaries to a known memory location (such as OCRAM), pass in a hardware API (via function pointers), and then execute logic dynamically with full access to Serial, SPI, I2C, and other features.

It acts as both a bootloader/host and a minimal RAM-executed operating system, allowing for modular, runtime-loadable programs to run directly from memory.

## Core Concept

We compile C++ code into raw binaries that live in RAM and call back into the main Teensy code using an exposed API wrapper (RamApiWrapper). These modules are standalone and can manipulate GPIOs, print messages over USB, and interface with SPI/I2C via host functions.

## !!!! IMPORTANT !!!!
Due to how the Teensy is setup by default in order to run code from the RAM2(the OCRAM; ram where memmory can be dynamically alocated and where the bootloader/os is loaded) you will have to:
Look for the configure_cache() function in startup.c, around line [310](https://github.com/PaulStoffregen/cores/blob/601e8014b32621cbf03f3d52c98a674648d1fce0/teensy4/startup.c#L310).
Remove "NOEXEC" from the pair of register writes for the memory region where you wish to execute code.

## Project Components

### 1. teensy files/ - PlatformIO Project (Main Teensy Host)

Acts as the host for running code from RAM

Initializes interfaces and populates RamApiWrapper

Loads raw compiled binaries from SD card or internal buffer

Copies and executes RAM code safely

### 2. os/ - RAM Executables and Builders

Contains builder scripts(build.sh - individual files; compile.py - whole project) for compiling RAM-loadable code

Uses custom linker script (teensy.ld) to place code and .rodata in predictable RAM regions

Outputs .bin file that the Teensy can load and run

### 3. RamApiWrapper Interface

A flat C-style struct passed into the RAM-loaded code

Contains function pointers to Serial.print, digitalWrite, SPI.transfer, etc.

Avoids name mangling and ensures ABI compatibility

### 4. Hardware Setup

Breadboarded setup with Teensy 4.0 and communication bus

Low leves system  IO (buttons and Leds)

USB serial connected to PC 
![Image of the breadboard](https://github.com/Paco2006/Embedded-Computer/blob/main/images/Breadboard.jpg)

## Current state of the project:
Currently the project is able to load up the code onto RAM and execute the code but the code lacks any kind of functionality
This is how the roadmap is looking for now:
1. Make the bootloader load the Kernel and run it
2. Make the Kernel initialise the system
3. Make the Kernel run tasks
4. Make the Kernel be able to run multiple tasks at once
5. Make the Kernel have tasks that run on startup (services)
6. Make the Kernel have "drivers" to control peripherals
7. Make the Kernel have a way for task to communicate between themselves(something like the DBUS on linux)
8. Make some kind of userspace and an official way to have a connection (something like the ttyX)
9. Maybe make peripherals that control a monitor via VGA and a keyboard input
