# Bluetooth-Notice-Board-LPC2129
Bluetooth-based Wireless Notice Board using LPC2129 ARM7, HC-05 Bluetooth Module, 4×8×8 Dot Matrix Display, and UART Communication. Messages received from a mobile application are displayed as scrolling text on the LED dot matrix.

## Overview
This project implements a **Bluetooth-based Wireless Notice Board** using the **LPC2129 (ARM7TDMI-S)** microcontroller. Messages sent from a smartphone via the **HC-05 Bluetooth module** are received through UART and displayed as scrolling text on a **4×8×8 LED Dot Matrix Display**.

The system eliminates the need for wired communication, allowing users to update notices instantly using a mobile Bluetooth terminal application.

## Features
- 📱 Wireless message transmission using HC-05 Bluetooth module
- 🔄 Smooth scrolling text on a 4×8×8 LED Dot Matrix display
- ⚡ UART communication between LPC2129 and HC-05
- 💡 Real-time display update
- 🛠️ Developed using Embedded C in Keil µVision
- 📟 Modular driver implementation for UART, Dot Matrix, and 74LS164 Shift Registers

## Hardware Used
- LPC2129 ARM7 Microcontroller
- HC-05 Bluetooth Module
- 4 × 8×8 LED Dot Matrix Display
- 74LS164 Shift Registers
- 74HC573 Latch
- 5V Power Supply

## Software Used
- Keil µVision
- Embedded C
- Flash Magic
- Bluetooth Terminal Mobile Application

## Working
1. Pair the mobile phone with the HC-05 Bluetooth module.
2. Send a text message using a Bluetooth terminal application.
3. LPC2129 receives the message through UART.
4. The message is processed and displayed as scrolling text on the 4×8×8 LED Dot Matrix display.
