#include "emu8085.h"
uint8_t memory[65536]; // final global array


int main(){
    CPUState cpu = {0}; // zero all regs
    cpu.pc = 0;
    cpu.h = 0x00;
    cpu.l = 0xAF;
    //other storage 
    memory[0x2000]= 0x01; //for add
    memory[0]= 0x16;//mvi d
    memory[1]= 0x13;
    memory[2]= 0x06; //mvi b
    memory[3]= 0x0A;
    memory[4]= 0x36;// mvi m
    memory[5]= 0xFF;
    memory[6]= 0x3E;//mvi a
    memory[7]= 0x55;
    memory[8]= 0x90; //sub b, 55h - 0a
    memory[9]= 0x32;// sta
    memory[10]=0x00;
    memory[11]=0x10;
    memory[12]=0x0E; //mvi c
    memory[13]=0xFF;
    memory[14]=0x3A; //lda
    memory[15]=0x00;
    memory[16]=0x20; 
    memory[17]=0x81; //add c
    memory[18]=0x32;// sta
    memory[19]=0x00;
    memory[20]=0x20;
    memory[21]=0x76;//hlt


   

    while(1){
        uint8_t curr_opcode = memory[cpu.pc];
        printf("Fetched opcode 0x%02X at PC=%u\n", curr_opcode, cpu.pc);
    switch(curr_opcode){
        //mvi
        case 0x06:
        case 0x0E:
        case 0x16:
        case 0x1E:
        case 0x26:
        case 0x2E:
        case 0x36:
        case 0x3E:
         {MVI(&cpu,curr_opcode);
          break;
         }
        //add
        case 0x80:
        case 0x81:
        case 0x82:
        case 0x83:
        case 0x84:
        case 0x85: 
        case 0x86:
        case 0x87:
         {
            ADD(&cpu, curr_opcode);
            break;
         }
        //sub
        case 0x90:
        case 0x91:
        case 0x92:
        case 0x93:
        case 0x94:
        case 0x95: 
        case 0x96:
        case 0x97:
         {
            SUB(&cpu, curr_opcode);
            break;
         }
        //lda
        case 0x3A:
        {
            LDA(&cpu,curr_opcode);
            break;
        }
        //sta
        case 0x32:
        {
            STA(&cpu,curr_opcode);
            break;
        }
        case 0x76:
            printf("HLT instruction. Stopping.\n");
            exit(0);
        default:
            printf("Error: Unimplemented opcode 0x%02X\n", curr_opcode);
            exit(1);
        }
        printf("the regs a = 0x%02X; b = 0x%02X; c = 0x%02X; d = 0x%02X; e = 0x%02X; h = 0x%02X; l = 0x%02X;\n",cpu.a,cpu.b,cpu.c,cpu.d,cpu.e,cpu.h,cpu.l);
        printf("the flags = 0x%02X\n", cpu.f);
    } 
    return 0;
}