#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

typedef struct position {
	int x;
	int y;
	int value;
} position;

typedef int (*value_function)(int x, int y, position grid[], int size);

void fill_grid(position grid[], int size, value_function value_function) {
	grid[0] = (position){.x = 0, .y = 0, .value = 1};
	int x = 1;
	int y = 1;
	int direction_x = 0;
	int direction_y = -1;
	int border_limit = 1;
	for (int i = 1; i < size; ++i) {
		x += direction_x;
		y += direction_y;
		position p = {.x = x, .y = y};
		if (value_function)
			p.value = value_function(x, y, grid, i);
		grid[i] = p;
		
		if (direction_y < 0 && y == -border_limit) {
			direction_y = 0;
			direction_x = -1;
		} else if (direction_x < 0 && x == -border_limit) {
			direction_y = 1;
			direction_x = 0;
		} else if (direction_y > 0 && y == border_limit) {
			direction_x = 1;
			direction_y = 0;
		} else if (direction_x > 0 && x == border_limit && y == border_limit) {
			++border_limit;
		} else if (direction_x > 0 && x == border_limit) {
			direction_x = 0;
			direction_y = -1;
		}
	}
}

int adjacent_sum(int x, int y, position grid[], int grid_size) {
	position adjacent[] = {
		{.x = x + 1, .y = y},
		{.x = x + 1, .y = y - 1},
		{.x = x, .y = y - 1},
		{.x = x - 1, .y = y - 1},
		{.x = x - 1, .y = y},
		{.x = x - 1, .y = y + 1},
		{.x = x, .y = y + 1},
		{.x = x + 1, .y = y + 1},
	};

	int sum = 0;
	for (int i = 0; i < 8; i++) {
		position test = adjacent[i];
		for (int j = grid_size - 1; j >= 0; j--) {
			position p = grid[j];
			if (test.x == p.x && test.y == p.y) {
				sum += p.value;
				break;
			}
		}
	}
	return sum;
}

void part1() {
	int target = 368078;
	position grid[target];
	fill_grid(grid, target, NULL);
	position target_pos = grid[target - 1];
	int steps = abs(target_pos.x) + abs(target_pos.y);
	printf("Number of steps for %i: %i\n", target, steps);
}

void part2() {
	int size = 100;
	int target_value = 368078; 
	position grid[size];
	fill_grid(grid, size, &adjacent_sum);
	for (int i = 0; i < size; ++i) {
		position p = grid[i];
		if (p.value > target_value) {
			printf("First value larger than %i: %i\n", target_value, p.value);
			break;
		}
	}
}
	
int main() {
	part1();
	part2();
}
