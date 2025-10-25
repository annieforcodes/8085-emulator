#include "emu8085.h"
void LDA(CPUState *cpu, uint8_t opcode){
    uint16_t address = (((uint16_t)memory[cpu->pc+2])<<8)|memory[cpu->pc+1];
    cpu->a = memory[address];
    printf("Executed LDA of data 0x%0X2 from memory 0x%04X ", cpu->a, address);
    cpu->pc +=3;
}

void STA(CPUState *cpu, uint8_t opcode){
    uint16_t address = (((uint16_t)memory[cpu->pc+2])<<8)|memory[cpu->pc+1];
    memory[address] = cpu->a;
    printf("Executed STA of data 0x%0X2 to memory 0x%04X ", memory[address], address);
    cpu->pc +=3;
}

void MVI(CPUState *cpu, uint8_t opcode){
    uint8_t data = memory[cpu->pc+1]; // immediate data
    uint8_t reg  = (opcode>>3)&0x07; // register number from 3 mid bits
    switch(reg){
        case 0: cpu->b = data;printf("Executed MVI B, 0x%02X\n", data); break;
        case 1: cpu->c = data; printf("Executed MVI C, 0x%02X\n", data); break;
        case 2: cpu->d = data; printf("Executed MVI D, 0x%02X\n", data); break;
        case 3: cpu->e = data; printf("Executed MVI E, 0x%02X\n", data); break;
        case 4: cpu->h = data; printf("Executed MVI H, 0x%02X\n", data); break;
        case 5: cpu->l = data; printf("Executed MVI L, 0x%02X\n", data); break;
        case 7: cpu->a = data; printf("Executed MVI A, 0x%02X\n", data); break;
        case 6: 
        {
            uint16_t address = ((((uint16_t)cpu->h)<<8)|cpu->l);
            memory[address] = data;
            printf("Executed MVI M, 0x%02X (at addr %04X)\n", data, address);
            printf("memory location data 0x%02X\n",memory[address]);
            break;  
        }

}cpu->pc +=2;
}