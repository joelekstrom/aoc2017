#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int sum(int buffer[], int length, int match_offset) {
	int sum = 0;
	for (int i = 0; i < length; ++i) {
		int value = buffer[i];
		int other_value = buffer[(i + match_offset) % length];
		if (value == other_value) {
			sum += value;
		}
	}
	return sum;
}

int main(int argc, char **argv) {
	int buffer[4096];
	int length = 0;
	for (int current = getchar(); isdigit(current); current = getchar()) {
		buffer[length++] = current - '0';
	}
	printf("Part 1: %i\nPart 2: %i", sum(buffer, length, 1), sum(buffer, length, length / 2));
}
