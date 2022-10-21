#include "opcodes.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: ./test <rom.ch8>\n");
    }
    FILE *fd = fopen(argv[1], "rb");
    if (fd == NULL) {
        printf("Error: Could not find %s\n", argv[1]);
        exit(1);
    }

    fseek(fd, 0L, SEEK_END);
    int file_size = ftell(fd);
    rewind(fd);

    uint8_t *buffer = malloc(file_size + 0x200);
    fread(buffer, file_size, 1, fd);
    
    for (int i = 0; i < file_size; i += 2) {
        uint16_t opcode = buffer[i];
        opcode = opcode << 8;
        opcode += buffer[i + 1];
        print_instruction(opcode);
    }

    return 0;
}
