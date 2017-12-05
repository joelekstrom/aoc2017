#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	argc -= 1;
	argv += 1;
	int maze[argc];
	for (int i = 0; i < argc; ++i) {
		maze[i] = atoi(argv[i]);
	}

	int step_count = 0;
	for (int index = 0; index < argc; ++step_count) {
		int steps = maze[index];
		maze[index] += steps >= 3 ? -1 : 1;
		index += steps;
	}
	printf("Maze was exited in %i steps", step_count);
	return step_count;
}
