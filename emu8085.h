#ifndef EMU8085_H
#define EMU8085_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
// registers in CPU
typedef struct{
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t h;
    uint8_t l;
    uint8_t f;  //8bit flag (S, Z, x, AC, x, P, x, CY)
    uint16_t sp;
    uint16_t pc;
}CPUState;

extern uint8_t memory[65536];

void MVI(CPUState *cpu, uint8_t opcode);
void ADD(CPUState *cpu, uint8_t opcode);
void SUB(CPUState *cpu, uint8_t opcode);
void LDA(CPUState *cpu, uint8_t opcode);
void STA(CPUState *cpu, uint8_t opcode);


#endif