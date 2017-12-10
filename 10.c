#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char **argv) {
	int count = 256;
	unsigned char numbers[count];
	for (int i = 0; i < count; ++i) {
		numbers[i] = i;
	}

	char *input;
	asprintf(&input, "%s%c%c%c%c%c", argv[1], 17, 31, 73, 47, 23);
	int input_length = strlen(input);

	int index = 0;
	int skip_size = 0;
	for (int round = 0; round < 64; ++round) { 
		for (int c = 0; c < input_length; ++c) {
			unsigned char length = input[c];
			for (int i = 0; i < length / 2; ++i) {
				unsigned char *a = &numbers[(index + i) % count];
				unsigned char *b = &numbers[(index + (length - (i + 1))) % count];
				char tmp = *a;
				*a = *b;
				*b = tmp;
			}
			index += length + skip_size++;
		}
	}

	for (int i = 0; i < 16; ++i) {
		unsigned char c = 0;
		for (int j = i * 16; j < i * 16 + 16; ++j) {
			c ^= numbers[j];
		}
		printf("%02x", c);
	}
}
