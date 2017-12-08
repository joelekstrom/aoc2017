#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define FOREACH_LINE(LINE, FD) char* LINE = NULL; size_t __size; while (getline(& LINE, &__size, FD) != -1)
#define FOREACH_WORD(WORD, STRING) for (char* WORD = strtok(STRING, " ,\t\n"); WORD != NULL; WORD = strtok(NULL, " ,\t\n"))
#define is_equal(A, B) (strcmp(A, B) == 0)
typedef char * string;

struct program {
	string name;
	int weight;
	int child_count;
	string child_names[20];
	struct program *parent;
	struct program *children[20];
};

struct program *find_program(struct program programs[], int program_count, string name) {
	for (int i = 0; i < program_count; ++i) {
		if (is_equal(programs[i].name, name))
			return &programs[i];
	}
	exit(EXIT_FAILURE);
}

int program_weight(struct program *program) {
	int weight = program->weight;
	for (int i = 0; i < program->child_count; ++i) {
		weight += program_weight(program->children[i]);
	}
	return weight;
}

int compare_programs(const void *a, const void *b) {
	return program_weight(*(struct program **)a) - program_weight(*(struct program **)b);
}

bool is_balanced(struct program *tree, struct program **culprit) {
	int child_count = tree->child_count;
	for (int i = 0; i < child_count; ++i) {
		if (!is_balanced(tree->children[i], culprit))
			return false;
	}

	if (child_count > 2) {
		qsort(&tree->children[0], child_count, sizeof(tree->children[0]), &compare_programs);
		if (program_weight(tree->children[0]) != program_weight(tree->children[1]))
			*culprit = tree->children[0];
		else if (program_weight(tree->children[child_count - 1]) != program_weight(tree->children[child_count - 2]))
			*culprit = tree->children[child_count - 1];
	}
	
	return *culprit == NULL;
}

int main() {
	struct program programs[10000];
	int program_count = 0;
	
	FOREACH_LINE(line, stdin) {
		struct program program = {0};
		FOREACH_WORD(word, line) {
			if (program.name == NULL) {
				asprintf(&program.name, "%s", word);
				continue;
			}

			if (word[0] == '(') {
				*strchr(++word, ')') = '\0';
				program.weight = atoi(word);
				continue;
			}

			if (is_equal(word, "->")) {
				continue;
			}
			
			asprintf(&program.child_names[program.child_count++], "%s", word);
		}
		programs[program_count++] = program;
	}

	// Setup parent/child relationships
	for (int i = 0; i < program_count; ++i) {
		struct program *parent = &programs[i];
		for (int j = 0; j < parent->child_count; ++j) {
			struct program *child = find_program(programs, program_count, parent->child_names[j]);
			child->parent = parent;
			parent->children[j] = child;
		}
	}

	struct program *root = &programs[0];
	while (root->parent != NULL) { root = root->parent; };
	printf("%s has no parent :(\n", root->name);

	struct program *unbalanced_program = NULL;
	if (!is_balanced(root, &unbalanced_program)) {
		printf("%s has incorrect weight! (%i)\n", unbalanced_program->name, unbalanced_program->weight);
		for (int i = 0; i < unbalanced_program->parent->child_count; ++i) {
			struct program *sibling = unbalanced_program->parent->children[i];
			if (sibling != unbalanced_program) {
				printf("It should weigh (%i) to be correct.\n", unbalanced_program->weight + program_weight(sibling) - program_weight(unbalanced_program));
				break;
			}
		}
	}
}
