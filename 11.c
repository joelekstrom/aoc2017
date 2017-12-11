#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define foreach_word(WORD, STRING) for (char* WORD = strtok(STRING, " ,\t\n"); WORD != NULL; WORD = strtok(NULL, " ,\t\n"))
#define is_equal(S1, S2) (strcmp(S1, S2) == 0)
typedef char* string;

enum direction {
	north,
	north_east,
	south_east,
	south,
	south_west,
	north_west
};

enum direction direction_from_string(string s) {
	if (is_equal(s, "n")) return north;
	if (is_equal(s, "ne")) return north_east;
	if (is_equal(s, "se")) return south_east;
	if (is_equal(s, "s")) return south;
	if (is_equal(s, "sw")) return south_west;
	if (is_equal(s, "nw")) return north_west;
	exit(EXIT_FAILURE);
};

int steps[6] = {0};

void step(enum direction d) {
	if (steps[(d + 2) % 6] > 0) {
		steps[(d + 2) % 6] -= 1;
		step((d + 1) % 6);
	} else if (steps[(d - 2) % 6] > 0) {
		steps[(d - 2) % 6] -= 1;
		step((d - 1) % 6);
	} else if (steps[(d + 3) % 6] > 0) {
		steps[(d + 3) % 6] -= 1;
	} else {
		steps[d] += 1;
	}
}

int current_distance() {
	int total_steps = 0;
	for (int i = 0; i < 6; ++i) {
		total_steps += steps[i];
	}
	return total_steps;
}

int main(int argc, string argv[]) {
	int max_distance = 0;
	foreach_word(word, argv[1]) {
		enum direction d = direction_from_string(word);
		step(d);
		int distance = current_distance();
		if (distance > max_distance) {
			max_distance = distance;
		}
	}
	printf("total distance: %i, max distance: %i\n", current_distance(), max_distance);
}
