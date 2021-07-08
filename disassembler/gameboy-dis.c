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
	
	if(*currInstruc == 0xcb) {
		printf("%s (0x%02x)", "CB Instruction", *currInstruc);
		*pc += 2;
		return;
	}

	int8_t first4bits = (currInstruc[0] >> 4);
	int8_t last4bits = (currInstruc[0] & 0xf);

	switch (first4bits) {
		case 0x0:
			switch (last4bits) {
				case 0x0:
					printf("%s (0x%02x)", "NOP", *currInstruc);
					*pc += 1;
					break;
				case 0x1:
					printf("%s (0x%02x) \t %02x%02x", "LD BC, d16", currInstruc[0], currInstruc[2], currInstruc[1]);
					*pc += 3;
					break;
				case 0x2:
					printf("%s (0x%02x)", "LD (BC), A", *currInstruc);
					*pc += 1;
					break;
				case 0x3:
					printf("%s (0x%02x)", "INC BC", *currInstruc);
					*pc += 1;
					break;
				case 0x4:
					printf("%s (0x%02x)", "INC B", *currInstruc);
					*pc += 1;
					break;
				case 0x5:
					printf("%s (0x%02x)", "DEC B", *currInstruc);
					*pc += 1;
					break;
				case 0x6:
					printf("%s (0x%02x) \t %02x", "LD B, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x7:
					printf("%s (0x%02x)", "RLCA", *currInstruc);
					*pc += 1;
					break;
				case 0x8:
					printf("%s (0x%02x) \t %02x%02x", "LD (a16), SP", currInstruc[0], currInstruc[2], currInstruc[1]);
					*pc += 3;
					break;
				case 0x9:
					printf("%s (0x%02x)", "ADD HL, BC", *currInstruc);
					*pc += 1;
					break;
				case 0xa:
					printf("%s (0x%02x)", "LD A, (BC)", *currInstruc);
					*pc += 1;
					break;
				case 0xb:
					printf("%s (0x%02x)", "DEC BC", *currInstruc);
					*pc += 1;
					break;
				case 0xc:
					printf("%s (0x%02x)", "INC C", *currInstruc);
					*pc += 1;
					break;
				case 0xd:
					printf("%s (0x%02x)", "DEC C", *currInstruc);
					*pc += 1;
					break;
				case 0xe:
					printf("%s (0x%02x) \t %02x", "LC B, d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xf:
					printf("%s (0x%02x)", "RRCA", *currInstruc);
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
					printf("%s (0x%02x%02x)", "STOP", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x1:
					printf("%s (0x%02x) \t %02x%02x", "LD DE, d16", currInstruc[0], currInstruc[2], currInstruc[1]);
					*pc += 3;
					break;
				case 0x2:
					printf("%s (0x%02x)", "LD (DE),A", *currInstruc);
					*pc += 1;
					break;
				case 0x3:
					printf("%s (0x%02x)", "INC DE", *currInstruc);
					*pc += 1;
					break;
				case 0x4:
					printf("%s (0x%02x)", "INC D", *currInstruc);
					*pc += 1;
					break;
				case 0x5:
					printf("%s (0x%02x)", "DEC D", *currInstruc);
					*pc += 1;
					break;
				case 0x6:
					printf("%s (0x%02x) \t %02x", "LD D,d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x7:
					printf("%s (0x%02x)", "RLA", *currInstruc);
					*pc += 1;
					break;
				case 0x8:
					printf("%s (0x%02x)", "JR r8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x9:
					printf("%s (0x%02x)", "ADD HL,DE", *currInstruc);
					*pc += 1;
					break;
				case 0xa:
					printf("%s (0x%02x)", "LD A,(DE)", *currInstruc);
					*pc += 1;
					break;
				case 0xb:
					printf("%s (0x%02x)", "DEC DE", *currInstruc);
					*pc += 1;
					break;
				case 0xc:
					printf("%s (0x%02x)", "INC E", *currInstruc);
					*pc += 1;
					break;
				case 0xd:
					printf("%s (0x%02x)", "DEC E", *currInstruc);
					*pc += 1;
					break;
				case 0xe:
					printf("%s (0x%02x) \t %02x", "LD E,d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xf:
					printf("%s (0x%02x) \t %02x", "RRA", currInstruc[0], currInstruc[1]);
					*pc += 2;
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
					printf("%s (0x%02x) \t %02x", "JR NZ,r8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x1:
					printf("%s (0x%02x) \t %02x", "LD HL,d16", currInstruc[0], currInstruc[2], currInstruc[1]);
					*pc += 3;
					break;
				case 0x2:
					printf("%s (0x%02x)", "LD (HL+),A", *currInstruc);
					*pc += 1;
					break;
				case 0x3:
					printf("%s (0x%02x)", "INC HL", *currInstruc);
					*pc += 1;
					break;
				case 0x4:
					printf("%s (0x%02x)", "INC H", *currInstruc);
					*pc += 1;
					break;
				case 0x5:
					printf("%s (0x%02x)", "DEC H", *currInstruc);
					*pc += 1;
					break;
				case 0x6:
					printf("%s (0x%02x) \t %02x", "LD H,d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x7:
					printf("%s (0x%02x)", "DAA", *currInstruc);
					*pc += 1;
					break;
				case 0x8:
					printf("%s (0x%02x) \t %02x", "JR Z,r8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x9:
					printf("%s (0x%02x)", "ADD HL,HL", *currInstruc);
					*pc += 1;
					break;
				case 0xa:
					printf("%s (0x%02x)", "LD A,(HL+)", *currInstruc);
					*pc += 1;
					break;
				case 0xb:
					printf("%s (0x%02x)", "DEC HL", *currInstruc);
					*pc += 1;
					break;
				case 0xc:
					printf("%s (0x%02x)", "INC L", *currInstruc);
					*pc += 1;
					break;
				case 0xd:
					printf("%s (0x%02x)", "DEC L", *currInstruc);
					*pc += 1;
					break;
				case 0xe:
					printf("%s (0x%02x) \t %02x", "LD L,d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xf:
					printf("%s (0x%02x)", "CPL", *currInstruc);
					*pc += 1;
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
					printf("%s (0x%02x) \t %02x", "JR NC,r8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x1:
					printf("%s (0x%02x) \t %02x", "LD SP,d16", currInstruc[0], currInstruc[2], currInstruc[1]);
					*pc += 3;
					break;
				case 0x2:
					printf("%s (0x%02x)", "LD (HL-),A", *currInstruc);
					*pc += 1;
					break;
				case 0x3:
					printf("%s (0x%02x)", "INC SP", *currInstruc);
					*pc += 1;
					break;
				case 0x4:
					printf("%s (0x%02x)", "INC (HL)", *currInstruc);
					*pc += 1;
					break;
				case 0x5:
					printf("%s (0x%02x)", "DEC (HL)", *currInstruc);
					*pc += 1;
					break;
				case 0x6:
					printf("%s (0x%02x)", "LD (HL),d8", *currInstruc);
					*pc += 1;
					break;
				case 0x7:
					printf("%s (0x%02x)", "SCF", *currInstruc);
					*pc += 1;
					break;
				case 0x8:
					printf("%s (0x%02x) \t %02x", "JR C,r8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x9:
					printf("%s (0x%02x)", "ADD HL,SP", *currInstruc);
					*pc += 1;
					break;
				case 0xa:
					printf("%s (0x%02x)", "LD A,(HL-)", *currInstruc);
					*pc += 1;
					break;
				case 0xb:
					printf("%s (0x%02x)", "DEC SP", *currInstruc);
					*pc += 1;
					break;
				case 0xc:
					printf("%s (0x%02x)", "INC A", *currInstruc);
					*pc += 1;
					break;
				case 0xd:
					printf("%s (0x%02x)", "DEC A", *currInstruc);
					*pc += 1;
					break;
				case 0xe:
					printf("%s (0x%02x) \t %02x", "LD A,d8", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xf:
					printf("%s (0x%02x)", "CCF", *currInstruc);
					*pc += 1;
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
				    printf("%s (0x%02x)", "LD B,B", *currInstruc);
					*pc += 1;
					break;
				case 0x1:
				    printf("%s (0x%02x)", "LD B,C", *currInstruc);
					*pc += 1;
					break;
				case 0x2:
				    printf("%s (0x%02x)", "LD B,D", *currInstruc);
					*pc += 1;
					break;
				case 0x3:
				    printf("%s (0x%02x)", "LD B,E", *currInstruc);
					*pc += 1;
					break;
				case 0x4:
				    printf("%s (0x%02x)", "LD B,H", *currInstruc);
					*pc += 1;
					break;
				case 0x5:
				    printf("%s (0x%02x)", "LD B,L", *currInstruc);
					*pc += 1;
					break;
				case 0x6:
				    printf("%s (0x%02x)", "LD B,(HL)", *currInstruc);
					*pc += 1;
					break;
				case 0x7:
				    printf("%s (0x%02x)", "LD B,A", *currInstruc);
					*pc += 1;
					break;
				case 0x8:
				    printf("%s (0x%02x)", "LD C,B", *currInstruc);
					*pc += 1;
					break;
				case 0x9:
				    printf("%s (0x%02x)", "LD C,C", *currInstruc);
					*pc += 1;
					break;
				case 0xa:
				    printf("%s (0x%02x)", "LD C,D", *currInstruc);
					*pc += 1;
					break;
				case 0xb:
				    printf("%s (0x%02x)", "LD C,E", *currInstruc);
					*pc += 1;
					break;
				case 0xc:
				    printf("%s (0x%02x)", "LD C,H", *currInstruc);
					*pc += 1;
					break;
				case 0xd:
				    printf("%s (0x%02x)", "LD C,L", *currInstruc);
					*pc += 1;
					break;
				case 0xe:
				    printf("%s (0x%02x)", "LD C,(HL)", *currInstruc);
					*pc += 1;
					break;
				case 0xf:
				    printf("%s (0x%02x)", "LD C,A", *currInstruc);
					*pc += 1;
					break;
				default:
					printf("Unknown 0x4 (%02x)", *currInstruc);
					*pc += 1;
					break;
			}
			break;
		case 0x5: 
			switch (last4bits) {
				case 0x0:
				    printf("%s (0x%02x)", "LD D,B", *currInstruc);
					*pc += 1;
					break;
				case 0x1:
				    printf("%s (0x%02x)", "LD D,C", *currInstruc);
					*pc += 1;
					break;
				case 0x2:
				    printf("%s (0x%02x)", "LD D,D", *currInstruc);
					*pc += 1;
					break;
				case 0x3:
				    printf("%s (0x%02x)", "LD D,E", *currInstruc);
					*pc += 1;
					break;
				case 0x4:
				    printf("%s (0x%02x)", "LD D,H", *currInstruc);
					*pc += 1;
					break;
				case 0x5:
				    printf("%s (0x%02x)", "LD D,L", *currInstruc);
					*pc += 1;
					break;
				case 0x6:
				    printf("%s (0x%02x)", "LD D,(HL)", *currInstruc);
					*pc += 1;
					break;
				case 0x7:
				    printf("%s (0x%02x)", "LD D,A", *currInstruc);
					*pc += 1;
					break;
				case 0x8:
				    printf("%s (0x%02x)", "LD E,B", *currInstruc);
					*pc += 1;
					break;
				case 0x9:
				    printf("%s (0x%02x)", "LD E,C", *currInstruc);
					*pc += 1;
					break;
				case 0xa:
				    printf("%s (0x%02x)", "LD E,D", *currInstruc);
					*pc += 1;
					break;
				case 0xb:
				    printf("%s (0x%02x)", "LD E,E", *currInstruc);
					*pc += 1;
					break;
				case 0xc:
				    printf("%s (0x%02x)", "LD E,H", *currInstruc);
					*pc += 1;
					break;
				case 0xd:
				    printf("%s (0x%02x)", "LD E,L", *currInstruc);
					*pc += 1;
					break;
				case 0xe:
				    printf("%s (0x%02x)", "LD E,(HL)", *currInstruc);
					*pc += 1;
					break;
				case 0xf:
				    printf("%s (0x%02x)", "LD E,A", *currInstruc);
					*pc += 1;
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
				    printf("%s (0x%02x)", "LD H,B", *currInstruc);
					*pc += 1;
					break;
				case 0x1:
				    printf("%s (0x%02x)", "LD H,C", *currInstruc);
					*pc += 1;
					break;
				case 0x2:
				    printf("%s (0x%02x)", "LD H,D", *currInstruc);
					*pc += 1;
					break;
				case 0x3:
				    printf("%s (0x%02x)", "LD H,E", *currInstruc);
					*pc += 1;
					break;
				case 0x4:
				    printf("%s (0x%02x)", "LD H,H", *currInstruc);
					*pc += 1;
					break;
				case 0x5:
				    printf("%s (0x%02x)", "LD H,L", *currInstruc);
					*pc += 1;
					break;
				case 0x6:
				    printf("%s (0x%02x)", "LD H,(HL)", *currInstruc);
					*pc += 1;
					break;
				case 0x7:
				    printf("%s (0x%02x)", "LD H,A", *currInstruc);
					*pc += 1;
					break;
				case 0x8:
				    printf("%s (0x%02x)", "LD L,B", *currInstruc);
					*pc += 1;
					break;
				case 0x9:
				    printf("%s (0x%02x)", "LD L,C", *currInstruc);
					*pc += 1;
					break;
				case 0xa:
				    printf("%s (0x%02x)", "LD L,D", *currInstruc);
					*pc += 1;
					break;
				case 0xb:
				    printf("%s (0x%02x)", "LD L,E", *currInstruc);
					*pc += 1;
					break;
				case 0xc:
				    printf("%s (0x%02x)", "LD L,H", *currInstruc);
					*pc += 1;
					break;
				case 0xd:
				    printf("%s (0x%02x)", "LD L,L", *currInstruc);
					*pc += 1;
					break;
				case 0xe:
				    printf("%s (0x%02x)", "LD L,(HL)", *currInstruc);
					*pc += 1;
					break;
				case 0xf:
				    printf("%s (0x%02x)", "LD L,A", *currInstruc);
					*pc += 1;
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
				    printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x1:
				    printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x2:
				    printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x3:
				    printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x4:
				    printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x5:
				    printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x6:
				    printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x7:
				    printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x8:
				    printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x9:
				    printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0xa:
				    printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0xb:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0xc:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0xd:
				    printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0xe:
				    printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0xf:
				    printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
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
				    printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x1:
				    printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x2:
				    printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x3:
				    printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x4:
				    printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x5:
				    printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x6:
				    printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x7:
				    printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x8:
				    printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x9:
				    printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0xa:
				    printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0xb:
				    printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0xc:
				    printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0xd:
				    printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0xe:
				    printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0xf:
				    printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
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
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x1:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x2:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x3:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x4:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x5:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x6:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x7:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x8:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x9:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0xa:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0xb:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0xc:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0xd:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0xe:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0xf:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
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
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x1:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x2:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x3:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x4:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x5:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x6:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x7:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x8:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x9:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0xa:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0xb:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0xc:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0xd:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0xe:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0xf:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
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
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x1:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x2:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x3:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x4:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x5:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x6:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x7:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x8:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x9:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0xa:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0xb:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0xc:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0xd:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0xe:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0xf:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
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
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x1:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x2:
					printf("%s (0x%02x) \t %02x", "", currInstruc[0], currInstruc[2], currInstruc[1]);
					*pc += 3;
					break;
				case 0x3:
					printf("%s (0x%02x) \t %02x", "", currInstruc[0], currInstruc[2], currInstruc[1]);
					*pc += 3;
					break;
				case 0x4:
					printf("%s (0x%02x) \t %02x", "", currInstruc[0], currInstruc[2], currInstruc[1]);
					*pc += 3;
					break;
				case 0x5:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x6:
					printf("%s (0x%02x) \t %02x", "", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x7:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x8:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x9:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0xa:
					printf("%s (0x%02x) \t %02x", "", currInstruc[0], currInstruc[2], currInstruc[1]);
					*pc += 3;
					break;
				case 0xc:
					printf("%s (0x%02x) \t %02x", "", currInstruc[0], currInstruc[2], currInstruc[1]);
					*pc += 3;
					break;
				case 0xd:
					printf("%s (0x%02x) \t %02x", "", currInstruc[0], currInstruc[2], currInstruc[1]);
					*pc += 3;
					break;
				case 0xe:
					printf("%s (0x%02x) \t %02x", "", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xf:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
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
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x1:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x2:
					printf("%s (0x%02x) \t %02x", "", currInstruc[0], currInstruc[2], currInstruc[1]);
					*pc += 3;
					break;
				case 0x4:
					printf("%s (0x%02x) \t %02x", "", currInstruc[0], currInstruc[2], currInstruc[1]);
					*pc += 3;
					break;
				case 0x5:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x6:
					printf("%s (0x%02x) \t %02x", "", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x7:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x8:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x9:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0xa:
					printf("%s (0x%02x) \t %02x", "", currInstruc[0], currInstruc[2], currInstruc[1]);
					*pc += 3;
					break;
				case 0xc:
					printf("%s (0x%02x) \t %02x", "", currInstruc[0], currInstruc[2], currInstruc[1]);
					*pc += 3;
					break;
				case 0xe:
					printf("%s (0x%02x) \t %02x", "", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xf:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
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
					printf("%s (0x%02x) \t %02x", "", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x1:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x2:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x5:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x6:
					printf("%s (0x%02x) \t %02x", "", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x7:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x8:
					printf("%s (0x%02x) \t %02x", "", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x9:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0xa:
					printf("%s (0x%02x) \t %02x", "", currInstruc[0], currInstruc[2], currInstruc[1]);
					*pc += 3;
					break;
				case 0xe:
					printf("%s (0x%02x) \t %02x", "", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xf:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
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
					printf("%s (0x%02x) \t %02x", "", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x1:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x2:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x3:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x5:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x6:
					printf("%s (0x%02x) \t %02x", "", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x7:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0x8:
					printf("%s (0x%02x) \t %02x", "", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0x9:
					printf("%s (0x%02x) \t %02x", "", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xa:
					printf("%s (0x%02x) \t %02x", "", currInstruc[0], currInstruc[2], currInstruc[1]);
					*pc += 3;
					break;
				case 0xb:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
					break;
				case 0xe:
					printf("%s (0x%02x) \t %02x", "", currInstruc[0], currInstruc[1]);
					*pc += 2;
					break;
				case 0xf:
					printf("%s (0x%02x)", "", *currInstruc);
					*pc += 1;
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
