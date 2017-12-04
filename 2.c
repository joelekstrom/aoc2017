#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define FOREACH_LINE(LINE, FD) char* LINE = NULL; size_t __size; while (getline(& LINE, &__size, FD) != -1)
#define FOREACH_WORD(WORD, STRING) for (char* WORD = strtok(STRING, " \t"); WORD != NULL; WORD = strtok(NULL, " \t"))

int part1() {
	int checksum = 0;
	FOREACH_LINE(line, stdin) {
		int largest = INT_MIN;
		int smallest = INT_MAX;
		FOREACH_WORD(word, line) {
			int number = atoi(word);
			if (number > largest)
				largest = number;
			if (number < smallest)
				smallest = number;
		}
		int difference = largest - smallest;
		checksum += difference;
	}
	return checksum;
}

int part2() {
	int checksum = 0;
	FOREACH_LINE(line, stdin) {
		int row[1000];
		int row_length = 0;
		FOREACH_WORD(word, line) {
			row[row_length++] = atoi(word);
		}
		
		for (int x = 0; x < row_length; ++x) {
			int numerator = row[x];
			for (int y = 0; y < row_length; ++y) {
				int denominator = row[y];
				if (numerator != denominator && numerator % denominator == 0) {
					checksum += numerator / denominator;
				}
			}
		}
	}
	return checksum;
}

int main() {
	printf("checksum: %i", part2());
}
