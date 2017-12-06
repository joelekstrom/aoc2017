#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>

#define is_equal_memory(A, B, S) (memcmp(A, B, sizeof(A[0]) * S) == 0)

void redistribute(int memory[], int length) {
	int bank = 0;
	int blocks = memory[0];
	for (int i = 1; i < length; ++i) {
		if (memory[i] > blocks) {
			bank = i;
			blocks = memory[i];
		}
	}
	
	memory[bank] = 0;
	for (++bank; blocks > 0; ++bank, --blocks) {
		memory[bank % length] += 1;
	}
}

/**
 Enumerate the stack downwards, comparing the initial `memory` to the `memory` on each frame.
 If a match is found, the variable pointed to by frame_index on that frame is returned.
 */
int *find_equal_stack_frame(int *memory, int length, int *frame_index, ptrdiff_t frame_offset) {
	ptrdiff_t memory_offset = frame_index - memory;
	while (*frame_index > 1) {
		frame_index -= frame_offset;
		int *stack_frame_memory = frame_index - memory_offset;
		if (is_equal_memory(memory, stack_frame_memory, length)) {
			return frame_index;
		}
	}
	return NULL;
}

typedef struct {
	int step_count;
	int loop_count;
} result;

result run(int *previous_memory, int length, int steps) {
	int memory[length];
	memcpy(memory, previous_memory, length * 4);
	redistribute(memory, length);

	int *equal_frame_index = find_equal_stack_frame(memory, length, &steps, memory - previous_memory);
	if (equal_frame_index) {
		return (result){.step_count = steps, .loop_count = steps - *equal_frame_index};
	}
	return run(&memory[0], length, steps + 1);
}

int main(int argc, char **argv) {
	argc -= 1;
	argv += 1;
	
	int memory_bank[argc];
	for (int i = 0; i < argc; ++i) {
		memory_bank[i] = atoi(argv[i]);
	}

	result result = run(memory_bank, argc, 1);
	printf("number of steps to redistribute: %i\n"
		   "number of loops to reach same state again: %i\n", result.step_count, result.loop_count);
}
