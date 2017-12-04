#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define FOREACH_LINE(LINE, FD) char* LINE = NULL; size_t __size; while (getline(& LINE, &__size, FD) != -1)
#define FOREACH_WORD(WORD, STRING) for (char* WORD = strtok(STRING, " \t\n"); WORD != NULL; WORD = strtok(NULL, " \t\n"))

bool is_equal(char *word1, char *word2) {
	return strcmp(word1, word2) == 0;
}

int compare_chars(const void *a, const void *b) {
	return *(char *)a - *(char *)b;
}

bool is_anagram(char *word1, char *word2) {
	qsort(word1, strlen(word1), sizeof(char), &compare_chars);
	qsort(word2, strlen(word2), sizeof(char), &compare_chars);
	return is_equal(word1, word2);
}

void validate(bool (*test_function)(char *a, char *b)) {
	int valid_phrase_count = 0;
	FOREACH_LINE(line, stdin) {
		char *words[100];
		int word_count = 0;
		bool is_valid = true;
		FOREACH_WORD(word, line) {
			for (int i = 0; i < word_count; ++i) {
				char *test_word = words[i];
				if (test_function(word, test_word))
					is_valid = false;
			}
			words[word_count++] = word;
		}
		if (is_valid && word_count > 1)
			++valid_phrase_count;
	}
	printf("valid phrase count: %i", valid_phrase_count);
}

int main() {
	//validate(&is_equal);
	validate(&is_anagram);
}
