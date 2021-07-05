#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

void printInstruction(uint8_t *code, int *pc);
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
		uint8_t *code = &buffer[pc];

		printf("%08x ", pc);
		printInstruction(code, &pc);
		printf ("\n");
	}

	return 0;
}

void printInstruction(uint8_t *code, int *pc) {
	
	// Moves the 8bit integer to get the first 
	// and last 4 bits example: 1010 0010 => 0000 1010
	int8_t first4bits = (code[0] >> 4);
	int8_t last4bits = (code[0] & 0xf); // 0000 0101 & 0000 1111

	switch (first4bits) {
		case 0x0:
			switch (last4bits)
			{
				case 0x0:
					printf("%-10s", "NOP");
					*pc += 1;
					break;
				default:
					printf("Unknown 0x0 (%02x)", *code);
					*pc += 1;
					break;
			}
			break;
		case 0x1:
			switch (last4bits)
			{
				case 0x8:
					printf("%s (0x%02x) \t %02x", "JR s8", code[0], code[1]);
					*pc += 2;
					break;
				default:
					printf("Unknown 0x1 (%02x)", *code);
					*pc += 1;
					break;
			}
			break;
		case 0x2: 
			switch (last4bits)
			{
				case 0x8:
					printf("%s (0x%02x) \t %02x", "JR Z, s8", code[0], code[1]);
					*pc += 2;
					break;
				default:
					printf("Unknown 0x2 (%02x)", *code);
					*pc += 1;
					break;
			}
			break;
		case 0x3:
			switch (last4bits)
			{
				case 0xe:
					printf("%s (0x%02x) \t %02x", "LD A, d8", code[0], code[1]);
					*pc += 2;
					break;
				default:
					printf("Unknown 0x3 (%02x)", *code);
					*pc += 1;
					break;
			}
			break;
		case 0x4: 
			switch (last4bits)
			{
				default:
					printf("Unknown 0x4 (%02x)", *code);
					*pc += 1;
					break;
			}
			break;
		case 0x5: 
			switch (last4bits)
			{
				default:
					printf("Unknown 0x5 (%02x)", *code);
					*pc += 1;
					break;
			}
			break;
		case 0x6: 
			switch (last4bits)
			{
				case 0x6:
					printf("%s (0x%02x) \t %02x", "LD H, (HL)", code[0]);
					*pc += 1;
					break;
				default:
					printf("Unknown 0x6 (%02x)", *code);
					*pc += 1;
					break;
			}
			break;
		case 0x7: 
			switch (last4bits)
			{
				default:
					printf("Unknown 0x7 (%02x)", *code);
					*pc += 1;
					break;
			}
			break;
		case 0x8:
			switch (last4bits)
			{
				default:
					printf("Unknown 0x8 (%02x)", *code);
					*pc += 1;
					break;
			}
			break;
		case 0x9: 
			switch (last4bits)
			{
				default:
					printf("Unknown 0x9 (%02x)", *code);
					*pc += 1;
					break;
			}
			break;
		case 0xa: 
			switch (last4bits)
			{
				case 0xf:
					printf("%s (0x%02x)", "XOR A", code[0]);
					*pc += 1;
					break;
				default:
					printf("Unknown 0xa (%02x)", *code);
					*pc += 1;
					break;
			}
			break;
		case 0xb: 
			switch (last4bits)
			{
				default:
					printf("Unknown 0xb (%02x)", *code);
					*pc += 1;
					break;
			}
			break;
		case 0xc:
			switch (last4bits)
			{
				case 0x3:
					printf("%s (0x%02x) \t %02x%02x", "JP a16", code[0], code[2], code[1]);
					*pc += 3;
					break;
				case 0xe:
					printf("%s (0x%02x) \t %02x", "ADC A, d8", code[0], code[1]);
					*pc += 2;
					break;
				case 0xd:
					printf("%s (0x%02x) \t %02x%02x", "CALL a16", code[0], code[2], code[1]);
					*pc += 3;
					break;
				default:
					printf("Unknown 0xc (%02x)", *code);
					*pc += 1;
					break;
			}
			break;
		case 0xd: 
			switch (last4bits)
			{
				default:
					printf("Unknown 0xd (%02x)", *code);
					*pc += 1;
					break;
			}
			break;
		case 0xe: 
			switch (last4bits)
			{
				case 0x0: 
					printf("%s (0x%02x) \t 0xFF%02X", "LD (a8), A", code[0], code[1]);
					*pc += 2;
					break;
				default:
					printf("Unknown 0xe (%02x)", *code);
					*pc += 1;
					break;
			}
			break;
		case 0xf:
			switch (last4bits)
			{
				case 0xe:
					printf("%s (0x%02x) \t %02x", "CP d8", code[0], code[1]);
					*pc += 2;
					break;
				case 0x3:
					printf("%s (0x%02x)", "DI", code[0]);
					*pc += 2;
					break;
				default:
					printf("Unknown 0xf (%02x)", *code);
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