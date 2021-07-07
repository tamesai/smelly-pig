#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

void printInstruction(uint8_t *currInstruc, int *pc);
int getFileSize(long from, FILE *f);
uint8_t* readFile(FILE *file, int fileSize);

int main (int argc, char**argv) {
	FILE *file;
	int fileSize, pc;
	uint8_t *buffer;

	if ((file = fopen(argv[1], "rb")) == NULL) {
		printf("error: Couldn't open %s\n", argv[1]);
		exit(1);
	}
	
	fileSize = getFileSize(0, file);
	buffer = readFile(file, fileSize);

	pc = 0x100;
	while (pc < (fileSize)) {
		uint8_t *currInstruc = &buffer[pc];

		printf("%08x ", pc);
		printInstruction(currInstruc, &pc);
		printf ("\n");
	}

	return 0;
}

void printInstruction(uint8_t *currInstruc, int *pc) {
	
	int8_t first4bits = (currInstruc[0] >> 4);
	int8_t last4bits = (currInstruc[0] & 0xf);

	switch (first4bits) {
		case 0x0:
			switch (last4bits) {
				case 0x0:
					printf("%s", "NOP");
					*pc += 1;
					break;
				case 0x1:
					printf("%s (0x%02x) \t %02x%02x", "LD BC, d16", currInstruc[0], currInstruc[2], currInstruc[1]);
					*pc += 3;
					break;
				case 0x2:
					printf("%s", "LD (BC), A");
					*pc += 1;
					break;
				case 0x3:
					printf("%s", "INC BC");
					*pc += 1;
					break;
				case 0x4:
					printf("%s", "INC B");
					*pc += 1;
					break;
				case 0x5:
					printf("%s", "DEC B");
					*pc += 1;
					break;
				case 0x6:
					printf("%s (0x%02x) \t %02x", "LD B, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x7:
					printf("%s", "RLCA");
					*pc += 1;
					break;
				case 0x8:
					printf("%s (0x%02x) \t %02x%02x", "LD (a16), SP", currInstruc[0], currInstruc[2], currInstruc[1]);
					*pc += 3;
					break;
				case 0x9:
					printf("%s", "ADD HL, BC");
					*pc += 1;
					break;
				case 0xa:
					printf("%s", "LD A, (BC)");
					*pc += 1;
					break;
				case 0xb:
					printf("%s", "DEC BC");
					*pc += 1;
					break;
				case 0xc:
					printf("%s", "INC C");
					*pc += 1;
					break;
				case 0xd:
					printf("%s", "DEC C");
					*pc += 1;
					break;
				case 0xe:
					printf("%s (0x%02x) \t %02x", "LC B, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xf:
					printf("%s", "RRCA");
					*pc += 1;
					break;
				default:
					printf("Unknown 0x0 (%02x)", *currInstruc);
					*pc += 1;
					break;
			}
			break;
		case 0x1:
			switch (last4bits) {
				case 0x0:
					printf("%s (0x%02x) \t %02x", "JR s8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x1:
					printf("%s (0x%02x) \t %02x", "JR s8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x2:
					printf("%s (0x%02x) \t %02x", "JR s8", currInstruc[0], currInstruc[1]);
					*pc += 3;
					break;
				case 0x3:
					printf("%s", "JR s8");
					*pc += 1;
					break;
				case 0x4:
					printf("%s (0x%02x)", "JR s8", *currInstruc);
					*pc += 1;
					break;
				case 0x5:
					printf("%s", "JR s8");
					*pc += 1;
					break;
				case 0x6:
					printf("%s (0x%02x) \t %02x", "JR s8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x7:
					printf("%s (0x%02x) \t %02x", "JR s8", currInstruc[0], currInstruc[1]);
					*pc += 1;
					break;
				case 0x8:
					printf("%s (0x%02x) \t %02x", "JR s8", currInstruc[0], currInstruc[1]);
					*pc += 3;
					break;
				case 0x9:
					printf("%s (0x%02x) \t %02x", "JR s8", currInstruc[0], currInstruc[1]);
					*pc += 1;
					break;
				case 0xa:
					printf("%s (0x%02x) \t %02x", "JR s8", currInstruc[0], currInstruc[1]);
					*pc += 1;
					break;
				case 0xb:
					printf("%s (0x%02x) \t %02x", "JR s8", currInstruc[0], currInstruc[1]);
					*pc += 1;
					break;
				case 0xc:
					printf("%s (0x%02x) \t %02x", "JR s8", currInstruc[0], currInstruc[1]);
					*pc += 1;
					break;
				case 0xd:
					printf("%s (0x%02x) \t %02x", "JR s8", currInstruc[0], currInstruc[1]);
					*pc += 1;
					break;
				case 0xe:
					printf("%s (0x%02x) \t %02x", "JR s8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xf:
					printf("%s (0x%02x) \t %02x", "JR s8", currInstruc[0], currInstruc[1]);
					*pc += 1;
					break;
				default:
					printf("Unknown 0x1 (%02x)", *currInstruc);
					*pc += 1;
					break;
			}
			break;
		case 0x2: 
			switch (last4bits) {
				case 0x0:
					printf("%s (0x%02x) \t %02x", "JR Z, s8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x1:
					printf("%s (0x%02x) \t %02x", "JR Z, s8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x2:
					printf("%s (0x%02x) \t %02x", "JR Z, s8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x3:
					printf("%s (0x%02x) \t %02x", "JR Z, s8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x4:
					printf("%s (0x%02x) \t %02x", "JR Z, s8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x5:
					printf("%s (0x%02x) \t %02x", "JR Z, s8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x6:
					printf("%s (0x%02x) \t %02x", "JR Z, s8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x7:
					printf("%s (0x%02x) \t %02x", "JR Z, s8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x8:
					printf("%s (0x%02x) \t %02x", "JR Z, s8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x9:
					printf("%s (0x%02x) \t %02x", "JR Z, s8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xa:
					printf("%s (0x%02x) \t %02x", "JR Z, s8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xb:
					printf("%s (0x%02x) \t %02x", "JR Z, s8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xc:
					printf("%s (0x%02x) \t %02x", "JR Z, s8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xd:
					printf("%s (0x%02x) \t %02x", "JR Z, s8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xe:
					printf("%s (0x%02x) \t %02x", "JR Z, s8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xf:
					printf("%s (0x%02x) \t %02x", "JR Z, s8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				default:
					printf("Unknown 0x2 (%02x)", *currInstruc);
					*pc += 1;
					break;
			}
			break;
		case 0x3:
			switch (last4bits) {
				case 0x0:
					printf("%s (0x%02x) \t %02x", "JR Z, s8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x1:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x2:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x3:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x4:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x5:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x6:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x7:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x8:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x9:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xa:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xb:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xc:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xd:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xe:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xf:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				default:
					printf("Unknown 0x3 (%02x)", *currInstruc);
					*pc += 1;
					break;
			}
			break;
		case 0x4: 
			switch (last4bits) {
				case 0x0:
					printf("%s (0x%02x) \t %02x", "JR Z, s8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x1:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x2:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x3:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x4:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x5:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x6:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x7:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x8:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x9:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xa:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xb:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xc:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xd:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xe:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xf:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				default:
					printf("Unknown 0x3 (%02x)", *currInstruc);
					*pc += 1;
					break;
			
			}
			break;
		case 0x5: 
			switch (last4bits) {
				case 0x0:
					printf("%s (0x%02x) \t %02x", "JR Z, s8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x1:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x2:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x3:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x4:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x5:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x6:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x7:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x8:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x9:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xa:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xb:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xc:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xd:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xe:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xf:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				default:
					printf("Unknown 0x3 (%02x)", *currInstruc);
					*pc += 1;
					break;
			}
			break;
		case 0x6: 
			switch (last4bits) {
				case 0x0:
					printf("%s (0x%02x) \t %02x", "JR Z, s8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x1:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x2:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x3:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x4:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x5:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x6:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x7:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x8:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x9:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xa:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xb:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xc:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xd:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xe:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xf:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				default:
					printf("Unknown 0x3 (%02x)", *currInstruc);
					*pc += 1;
					break;
			}
			break;
		case 0x7: 
			switch (last4bits) {
				case 0x0:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x1:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x2:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x3:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x4:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x5:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x6:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x7:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x8:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x9:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xa:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xb:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xc:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xd:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xe:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xf:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				default:
					printf("Unknown 0x3 (%02x)", *currInstruc);
					*pc += 1;
					break;
			}
			break;
		case 0x8:
			switch (last4bits) {
				case 0x0:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x1:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x2:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x3:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x4:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x5:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x6:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x7:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x8:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x9:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xa:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xb:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xc:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xd:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xe:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xf:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				default:
					printf("Unknown 0x3 (%02x)", *currInstruc);
					*pc += 1;
					break;
			}
			break;
		case 0x9: 
			switch (last4bits) {
				case 0x0:
					printf("%s (0x%02x) \t %02x", "JR Z, s8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x1:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x2:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x3:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x4:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x5:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x6:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x7:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x8:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x9:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xa:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xb:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xc:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xd:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xe:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xf:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				default:
					printf("Unknown 0x3 (%02x)", *currInstruc);
					*pc += 1;
					break;
			}
			break;
		case 0xa: 
			switch (last4bits) {
				case 0x0:
					printf("%s (0x%02x) \t %02x", "JR Z, s8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x1:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x2:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x3:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x4:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x5:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x6:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x7:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x8:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x9:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xa:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xb:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xc:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xd:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xe:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xf:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				default:
					printf("Unknown 0x3 (%02x)", *currInstruc);
					*pc += 1;
					break;
			}
			break;
		case 0xb: 
			switch (last4bits) {
				case 0x0:
					printf("%s (0x%02x) \t %02x", "JR Z, s8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x1:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x2:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x3:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x4:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x5:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x6:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x7:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x8:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x9:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xa:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xb:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xc:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xd:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xe:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xf:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				default:
					printf("Unknown 0x3 (%02x)", *currInstruc);
					*pc += 1;
					break;
			}
			break;
		case 0xc:
			switch (last4bits) {
				case 0x0:
					printf("%s (0x%02x) \t %02x", "JR Z, s8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x1:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x2:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x3:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x4:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x5:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x6:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x7:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x8:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x9:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xa:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xb:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xc:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xd:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xe:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xf:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				default:
					printf("Unknown 0x3 (%02x)", *currInstruc);
					*pc += 1;
					break;
			}
			break;
		case 0xd: 
			switch (last4bits) {
				case 0x0:
					printf("%s (0x%02x) \t %02x", "JR Z, s8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x1:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x2:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x3:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x4:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x5:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x6:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x7:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x8:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x9:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xa:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xb:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xc:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xd:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xe:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xf:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				default:
					printf("Unknown 0x3 (%02x)", *currInstruc);
					*pc += 1;
					break;
			}
			break;
		case 0xe: 
			switch (last4bits) {
				case 0x0:
					printf("%s (0x%02x) \t %02x", "JR Z, s8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x1:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x2:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x3:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x4:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x5:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x6:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x7:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x8:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x9:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xa:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xb:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xc:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xd:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xe:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xf:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				default:
					printf("Unknown 0x3 (%02x)", *currInstruc);
					*pc += 1;
					break;
			}
			break;
		case 0xf:
			switch (last4bits) {
				case 0x0:
					printf("%s (0x%02x) \t %02x", "JR Z, s8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x1:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x2:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x3:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x4:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x5:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x6:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x7:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x8:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x9:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xa:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xb:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xc:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xd:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xe:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xf:
					printf("%s (0x%02x) \t %02x", "LD A, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				default:
					printf("Unknown 0x3 (%02x)", *currInstruc);
					*pc += 1;
					break;
			}
			break;
	}
}

uint8_t *readFile(FILE *file, int fileSize) {
	uint8_t *buffer = malloc(fileSize);
	fread(buffer, fileSize, 1, file);
	fclose(file);
	return buffer;
}

int getFileSize(long from, FILE *f) {
	fseek(f, from, SEEK_END);
	int fileSize = ftell(f);
	fseek(f, from, SEEK_SET);

	return fileSize;
}
