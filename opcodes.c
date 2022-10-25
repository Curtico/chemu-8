#include "opcodes.h"
#include <stdio.h>
#include <stdint.h>

void print_instruction(uint16_t opcode) {
    uint8_t *bytes = &opcode;
    
    printf("%02x %02x ", bytes[1], bytes[0]);
    
    uint8_t first_nibble = bytes[1] >> 4;
    switch (first_nibble) {
        case 0x00: {
                       if (bytes[0] >> 4 != 0xe) {
                           printf("CALL     0x%x%x\n", bytes[1] - (first_nibble * 16), bytes[0]);
                       }
                       else {
                           switch (bytes[0]) {
                               case 0xe0: printf("DISP_CLR\n"); break;
                               case 0xee: printf("RET\n"); break;
                           }
                       }
                       break;
                   }
        case 0x01: printf("GOTO     0x%01x%02x\n", bytes[1] - (first_nibble * 16), bytes[0]); break;
        case 0x02: printf("CALL     0x%01x%02x\n", bytes[1] - (first_nibble * 16), bytes[0]); break;
        case 0x03: printf("SKE      V%d, 0x%02x\n", bytes[1] - (first_nibble * 16), bytes[0]); break;
        case 0x04: printf("SKNE     V%d, 0x%02x\n", bytes[1] - (first_nibble * 16), bytes[0]); break;
        case 0x05: printf("SKE      V%d, V%d\n", bytes[1] - (first_nibble * 16), bytes[0] >> 4); break;
        case 0x06: printf("SET      V%d, 0x%02x\n", bytes[1] - (first_nibble * 16), bytes[0]); break;
        case 0x07: printf("ADD      V%d, 0x%02x\n", bytes[1] - (first_nibble * 16), bytes[0]); break;
        case 0x08: {
                       uint8_t vx = bytes[1] - (first_nibble * 16);
                       uint8_t vy = bytes[0] >> 4;
                       uint8_t operand = bytes[0] - (vy * 16);

                       switch (operand) {
                           case 0x0: printf("SET      V%d, V%d\n", vx, vy); break;
                           case 0x1: printf("OR       V%d, V%d\n", vx, vy); break;
                           case 0x2: printf("AND      V%d, V%d\n", vx, vy); break;
                           case 0x3: printf("XOR      V%d, V%d\n", vx, vy); break;
                           case 0x4: printf("ADD      V%d, V%d\n", vx, vy); break;
                           case 0x5: printf("SUB      V%d, V%d\n", vx, vy); break;
                           case 0x6: printf("SHIFTR   V%d\n", vx); break;
                           case 0x7: printf("SUBX     V%d, V%d\n", vx, vy); break;
                           case 0xe: printf("SHIFTL   V%d\n", vx); break;
                       }
                   }
                   break;
        case 0x09: printf("SKIP_IF_NOT_EQUAL V%d, V%d\n", bytes[1] - (first_nibble * 16), bytes[0] >> 4); break;
        case 0x0a: printf("SET_I    0x%01x%02x\n", bytes[1] - (first_nibble * 16), bytes[0]); break;
        case 0x0b: printf("GOTO     V0 + 0x%01x%02x\n", bytes[1] - (first_nibble * 16), bytes[0]); break;
        case 0x0c: printf("RAND     V%d, 0x%02x\n", bytes[1] - (first_nibble * 16), bytes[0]); break;
        case 0x0d: printf("DRAW     V%d, V%d, %d\n", bytes[1] - (first_nibble * 16), bytes[0] >> 4, bytes[0] - ((bytes[0] >> 4) * 16)); break;
        case 0x0e: {
                       switch (bytes[0]) {
                           case 0x9e: printf("SKP      V%d\n", bytes[1] - (first_nibble * 16)); break;
                           case 0xa1: printf("SKNP     V%d\n", bytes[1] - (first_nibble * 16)); break;
                       }
                       break;
                   }
        case 0x0f: {
                       uint8_t vx = bytes[1] - (first_nibble * 16);
                       switch (bytes[0]) {
                           case 0x07: printf("SET      V%d, DT\n", vx); break;
                           case 0x0a: printf("SET      V%d\n, KP", vx); break;
                           case 0x15: printf("SET      DT, V%d\n", vx); break;
                           case 0x18: printf("SET      ST, V%d\n", vx); break;
                           case 0x1e: printf("ADD      I,  V%d\n", vx); break;
                           case 0x29: printf("SPRITE   V%d\n", vx); break;
                           case 0x33: printf("BCD      V%d\n", vx); break;
                           case 0x55: printf("STU      V%d\n", vx); break;
                           case 0x65: printf("LDU      V%d\n", vx); break;
                       }
                   }
                   break;
    }
}
