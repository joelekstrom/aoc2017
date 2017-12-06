#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct stack_frame {
	int *memory;
	int index;
	struct stack_frame *previous_frame;
} stack_frame;

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

stack_frame *equal_frame_in_stack(stack_frame *stack, int state[], int length) {
	do {
		if (is_equal_memory(stack->memory, state, length)) {
			return stack;
		}
	} while ((stack = stack->previous_frame));
	return NULL;
}

typedef struct {
	int step_count;
	int loop_count;
} result;

result run(stack_frame frame, int length) {
	int memory[length];
	memcpy(memory, frame.memory, length * 4);
	redistribute(memory, length);

	stack_frame *equal_frame = equal_frame_in_stack(&frame, memory, length);
	if (equal_frame) {
		return (result){.step_count = frame.index, .loop_count = frame.index + 1 - equal_frame->index};
	}
	
	stack_frame next_frame = {.memory = memory, .previous_frame = &frame, .index = frame.index + 1};
	return run(next_frame, length);
}

int main(int argc, char **argv) {
	argc -= 1;
	argv += 1;
	
	int memory_bank[argc];
	for (int i = 0; i < argc; ++i) {
		memory_bank[i] = atoi(argv[i]);
	}

	stack_frame frame = {.memory = memory_bank, .previous_frame = NULL, .index = 1};
	result result = run(frame, argc);
	printf("number of steps to redistribute: %i\n"
		   "number of loops to reach same state again: %i\n", result.step_count, result.loop_count);
}
