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
                           printf("CALL 0x%x%x\n", bytes[1] - (first_nibble * 16), bytes[0]);
                       }
                       else {
                           switch (bytes[0]) {
                               case 0xe0: printf("DISP_CLR\n"); break;
                               case 0xee: printf("RETURN\n"); break;
                           }
                       }
                       break;
                   }
        case 0x01: printf("GOTO 0x%01x%02x\n", bytes[1] - (first_nibble * 16), bytes[0]); break;
        case 0x02: printf("CALL 0x%01x%02x\n", bytes[1] - (first_nibble * 16), bytes[0]); break;
        case 0x03: printf("SKIP_IF_EQUAL V%d, 0x%02x\n", bytes[1] - (first_nibble * 16), bytes[0]); break;
        case 0x04: printf("SKIP_IF_NOT_EQUAL V%d, 0x%02x\n", bytes[1] - (first_nibble * 16), bytes[0]); break;
        case 0x05: printf("SKIP_IF_EQUAL V%d, V%d\n", bytes[1] - (first_nibble * 16), bytes[0] >> 4); break;
        case 0x06: printf("SET_REGISTER V%d, 0x%02x\n", bytes[1] - (first_nibble * 16), bytes[0]); break;
        case 0x07: printf("ADD_REGISTER V%d, 0x%02x\n", bytes[1] - (first_nibble * 16), bytes[0]); break;
        case 0x08: printf("Undetermined opcode\n"); break; // TODO
        case 0x09: printf("SKIP_IF_NOT_EQUAL V%d, V%d\n", bytes[1] - (first_nibble * 16), bytes[0] >> 4); break;
        case 0x0a: printf("SET_I 0x%01x%02x\n", bytes[1] - (first_nibble * 16), bytes[0]); break;
        case 0x0b: printf("GOTO V0 + 0x%01x%02x\n", bytes[1] - (first_nibble * 16), bytes[0]); break;
        case 0x0c: printf("SET_RAND V%d, 0x%02x\n", bytes[1] - (first_nibble * 16), bytes[0]); break;
        case 0x0d: printf("DRAW V%d, V%d, %d\n", bytes[1] - (first_nibble * 16), bytes[0] >> 4, bytes[0] - ((bytes[0] >> 4) * 16)); break;
        case 0x0e: printf("Undetermined opcode\n"); break;
        case 0x0f: printf("Undetermined opcode\n"); break;
    }
}
