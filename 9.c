#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int parse_group(int character, int score, int *garbage_count) {
	bool is_group = character == '{';
	bool is_garbage = character == '<';
	int group_score = score;

	bool ignore_next = false;
	while ((character = getchar()) != EOF) {
		if (ignore_next) {
			ignore_next = false;
			continue;
		}
		if ((character == '{' || character == '<') && !is_garbage)
			group_score += parse_group(character, score + 1, garbage_count);
		else if (character == '}' && is_group)
			return group_score;
		else if (character == '>' && is_garbage)
			return 0;
		else if (character == '!')
			ignore_next = true;
		else if (is_garbage)
			*garbage_count += 1;
	}
	exit(EXIT_FAILURE);
}

int main() {
	int garbage_count = 0;
	int total = parse_group(getchar(), 1, &garbage_count);
	printf("Total group score: %i\n"
		   "Total garbage characters: %i\n", total, garbage_count);
}
