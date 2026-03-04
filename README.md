8085 Microprocessor Emulator
An 8085 CPU emulator written from scratch in C. This project simulates the core hardware functionality of the Intel 8085, allowing it to load and execute 8085 machine code programs.
Simulates the complete 8085 register set, including:
8-bit registers (A, B, C, D, E, H, L)
16-bit registers (SP, PC)
8-bit Flag Register (F)
Fetch-Decode-Execute Cycle: A central while loop continuously fetches opcodes from memory, decodes them with a switch statement, and calls the appropriate function to execute them.
64KB Memory Model: A simple uint8_t memory[65536] array serves as the CPU's full address space.
Accurate Flag Handling: All arithmetic operations update the five key flags (Sign, Zero, Parity, Carry, Aux Carry) with bit-perfect accuracy, including handling borrow logic for SUB.
This emulator currently supports the foundational 8085 instruction set:
Data Transfer (Move): MVI (all registers)
Data Transfer (Memory): LDA, STA
Arithmetic: ADD (all registers), SUB (all registers)
Control: HLT

Added automated testing of add and sub functions using a python script "verify.py" to input random operands and verify the result in accumulator and flags, fixed a crucial error by changing the borrow logic which was pointed out by the randomized testing
For automated testing:
gcc emu8085.c arith.c lsm.c -o emulator
./emulator program.hex
python verify.py

Various programs can be run manually by:
gcc emu8085.c arith.c lsm.c -o emulator
./emulator add.hex  Result: A=8
./emulator sub.hex  Result: A=7
./emulator add_carry.hex  Result: A=0 CY =1
./emulator sub_carry.hex  Result: A=251 CY =1
./emulator memory_load.hex  Result: A=10
./emulator memory_store.hex  Result: A=10
