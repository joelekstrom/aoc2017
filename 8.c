#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define FOREACH_LINE(LINE, FD) char* LINE = NULL; size_t __size; while (getline(& LINE, &__size, FD) != -1)
#define is_equal(A, B) (strcmp(A, B) == 0)
typedef char * string;

struct cpu_register {
	string name;
	int value;
};

struct cpu_register registers[100];
int active_registers = 0;
int highest_register_value = INT_MIN;

struct cpu_register *get_register(string name) {
	for (int i = 0; i < active_registers; ++i) {
		if (is_equal(registers[i].name, name))
			return &registers[i];
	}

	struct cpu_register *new = &registers[active_registers++];
	asprintf(&new->name, "%s", name);
	new->value = 0;
	return new;
}

struct instruction {
	struct cpu_register *target_register;
	struct cpu_register *condition_register;
	int modifier;
	string condition;
	int condition_value;
};

void execute(struct instruction instruction) {
    #define test_condition(CONDITION) if (is_equal(instruction.condition, #CONDITION) && instruction.condition_register->value CONDITION instruction.condition_value) { goto perform; }
	test_condition(>);
	test_condition(<);
	test_condition(>=);
	test_condition(<=);
	test_condition(==);
	test_condition(!=);
    #undef test_condition
	return;
 perform:
	instruction.target_register->value += instruction.modifier;
	if (instruction.target_register->value > highest_register_value)
		highest_register_value = instruction.target_register->value;
}

int main() {	
	FOREACH_LINE(line, stdin) {
		string delimiters = " \t\n";
		struct instruction instruction;
		instruction.target_register = get_register(strtok(line, delimiters));
		
		string instruction_type = strtok(NULL, delimiters);
		int value = atoi(strtok(NULL, delimiters));
		instruction.modifier = is_equal(instruction_type, "inc") ? value : -value;
		
		strtok(NULL, delimiters); // Skip "if"
		instruction.condition_register = get_register(strtok(NULL, delimiters));
		asprintf(&instruction.condition, "%s", strtok(NULL, delimiters));
		instruction.condition_value = atoi(strtok(NULL, delimiters));
		
		execute(instruction);
	}

	int max_register_value = registers[0].value;
	for (int i = 0; i < active_registers; ++i) {
		struct cpu_register *r = &registers[i];
		max_register_value = registers[i].value > max_register_value ? registers[i].value : max_register_value;
	}

	printf("Largest register after execution: %i\n"
		   "Largest held value during exection: %i\n", max_register_value, highest_register_value);
}
