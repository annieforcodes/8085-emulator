#include "emu8085.h"
static uint8_t parity(uint8_t value){ //odd parity
    int count=0;
    for(int i=0;i<8;i++){
        if((value>>i)&1){
            count++;
        }
    }
    return (count%2 == 0)?1:0; // returns 1 if even parity
    } 



static uint8_t read_reg(CPUState *cpu, uint8_t code){
    uint8_t data;
     switch(code){
        case 0:data=cpu->b; printf("data read from b\n"); break;
        case 1:data=cpu->c; printf("data read from c\n"); break;
        case 2:data=cpu->d; printf("data read from d\n"); break;
        case 3:data=cpu->e; printf("data read from e\n"); break;
        case 4:data=cpu->h; printf("data read from h\n"); break;
        case 5:data=cpu->l; printf("data read from l\n"); break;
        case 6:
             {
                uint16_t address = (((uint16_t)cpu->h)<<8)|cpu->l;
                data = memory[address];
                printf("data read from m\n"); 
                break;
             }
        case 7:data=cpu->a; printf("data read from a\n"); break;
            }
        return data;

     }


void ADD(CPUState *cpu, uint8_t opcode){
uint8_t code = opcode&0x07;
uint8_t reg_data = read_reg(cpu, code); // passed as cpu, not as &cpu , as we already have the point in the ADD call before
uint16_t sum = (uint16_t)cpu->a + (uint16_t)reg_data;
// cpu->f = 0x02; // bit at LSB+1 is always 1, rest set to zero
cpu->f = (1<<1); //better
if((uint8_t)sum == 0){
    cpu->f |= (1<<6); // set zero flag
}
if(((uint8_t)sum & 0x80)!=0){ //sign bit 1000 0000 = 0x80
    cpu->f |= (1<<7); // set sign flag
}
if(parity((uint8_t)sum)){ // if even number of ones
    cpu->f |= (1<<2); // set parity flag
}
if(sum>0xFF){ // carry
    cpu->f |= (1<<0); // set carry flag
}
//AC (carry from bit 3 to 4)
if (((cpu->a & 0x0F) + (reg_data & 0x0F)) > 0x0F) { // adding the lower nibbles to see if they overflow to higher nibble
    cpu->f |= (1 << 4); // Set AC 
    }
cpu->a = (uint8_t)sum;
cpu->pc +=1;
printf("executed ADD with result 0x%02X in acc\n", cpu->a);

}

void SUB(CPUState *cpu, uint8_t opcode){
uint8_t code = opcode&0x07;
uint8_t reg_data = read_reg(cpu, code);
uint8_t twocomp_reg_data = ~reg_data+1;
uint16_t sum = (uint16_t)cpu->a + (uint16_t)twocomp_reg_data;
// cpu->f = 0x02; // bit at LSB+1 is always 1, rest set to zero
cpu->f = (1<<1); //better
if((uint8_t)sum == 0){
    cpu->f |= (1<<6); // set zero flag
}
if(((uint8_t)sum & 0x80)!=0){ //sign bit 1000 0000 = 0x80
    cpu->f |= (1<<7); // set sign flag
}
if(parity((uint8_t)sum)){ // if even number of ones
    cpu->f |= (1<<2); // set parity flag
}
if(sum<=0xFF){ // borrow
    cpu->f |= (1<<0); // set carry flag
}
//AC (carry from bit 3 to 4)
if (!(((cpu->a & 0x0F) + (twocomp_reg_data & 0x0F)) > 0x0F)) { // adding the lower nibbles to see if they overflow to higher nibble
    cpu->f |= (1 << 4); // Set AC (Bit 4)
    }
cpu->a = (uint8_t)sum;
cpu->pc +=1;
printf("executed SUB with result 0x%02X in acc\n", cpu->a);

}

