8085 Microprocessor Emulator
A lightweight, portable 8085 CPU emulator written from scratch in C. This project simulates the core hardware functionality of the Intel 8085, allowing it to load and execute 8085 machine code programs.

The primary goal of this project was to gain a deep, practical understanding of computer architecture and low-level systems programming.

Key Features
Core CPU Emulation: Simulates the complete 8085 register set, including:

8-bit registers (A, B, C, D, E, H, L)

16-bit registers (SP, PC)

8-bit Flag Register (F)

Fetch-Decode-Execute Cycle: A central while loop continuously fetches opcodes from memory, decodes them with a switch statement, and calls the appropriate function to execute them.

64KB Memory Model: A simple uint8_t memory[65536] array serves as the CPU's full address space.

Accurate Flag Handling: All arithmetic operations update the five key flags (Sign, Zero, Parity, Carry, Aux Carry) with bit-perfect accuracy, including handling borrow logic for SUB.

Modular Code: The project is organized into multiple files for scalability and clean separation of the CPU loop from the instruction logic.

Implemented Instruction Groups
This emulator currently supports the foundational 8085 instruction set:

Data Transfer (Move): MVI (all registers)

Data Transfer (Memory): LDA, STA

Arithmetic: ADD (all registers), SUB (all registers)

Control: HLT

Technical Skills Demonstrated
Low-Level C Programming: Extensive use of structs for CPU state, uint8_t for byte-level data, and pointer management.

Bitwise Operations: Heavy reliance on bitwise operators (&, |, ^, <<, >>) for opcode decoding, register selection, and flag manipulation.

Computer Architecture: Practical application of concepts like instruction sets, opcodes, memory addressing (little-endian), and the function of a CPU's flags and registers.

