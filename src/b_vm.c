#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "b_vm.h"

struct b_vm_t* b_vm_new_default() {
	struct b_vm_t* self = (struct b_vm_t*) calloc(1, sizeof(struct b_vm_t));
	if (!self) {
		return 0;
	}
	self->maxStack = 1024;
	return self;
}

struct b_vm_opcode_unary {
	unsigned char op;
	unsigned int r1;
};

struct {
	unsigned char op;
	unsigned int r1;
	unsigned int r2;
} b_vm_opcode_binary;

b_vm_error_t b_vm_compile(unsigned char* opcodes) {
	for (;;) {
		switch (*opcodes++) {
		case B_VM_OPCODE_STACK_INC: {
			*((unsigned int*) opcodes) = (opcodes[0] << 24) + (opcodes[1] << 16) + (opcodes[2] << 8) + opcodes[3];
			opcodes += sizeof(unsigned int);
			break;
		}
		case B_VM_OPCODE_STACK_DEC: {
			*((unsigned int*) opcodes) = (opcodes[0] << 24) + (opcodes[1] << 16) + (opcodes[2] << 8) + opcodes[3];
			opcodes += sizeof(unsigned int);
			break;
		}
		case B_VM_OPCODE_STACK_DOUBLE: {
			*((double*) opcodes) = (opcodes[0] << 24) + (opcodes[1] << 16) + (opcodes[2] << 8) + opcodes[3];
			opcodes += sizeof(double);
			break;
		}
		case B_VM_OPCODE_STACK_INTEGER: {
			*((unsigned int*) opcodes) = (opcodes[0] << 24) + (opcodes[1] << 16) + (opcodes[2] << 8) + opcodes[3];
			opcodes += sizeof(unsigned int);
			break;
		}
		case B_VM_OPCODE_STACK_TRUE: {
			break;
		}
		case B_VM_OPCODE_STACK_FALSE: {
			break;
		}
		case B_VM_OPCODE_STACK_STRING: {
			unsigned length = *((unsigned int*) opcodes) = (opcodes[0] << 24) + (opcodes[1] << 16) + (opcodes[2] << 8) + opcodes[3];
			opcodes += sizeof(unsigned int);
			opcodes += (length + 1) * sizeof(unsigned char);
			break;
		}
		case B_VM_OPCODE_STACK_NULL: {
			break;
		}
		case B_VM_OPCODE_NUMBER_SUM: {
			break;
		}
		case B_VM_OPCODE_NUMBER_SUB: {
			break;
		}
		case B_VM_OPCODE_NUMBER_MUL: {
			break;
		}
		case B_VM_OPCODE_NUMBER_DIV: {
			break;
		}
		case B_VM_OPCODE_NUMBER_EQ: {
			break;
		}
		case B_VM_OPCODE_NUMBER_NEQ: {
			break;
		}
		case B_VM_OPCODE_NUMBER_COMPARE: {
			break;
		}
		case B_VM_OPCODE_NUMBER_GT: {
			break;
		}
		case B_VM_OPCODE_NUMBER_GE: {
			break;
		}
		case B_VM_OPCODE_NUMBER_LT: {
			break;
		}
		case B_VM_OPCODE_NUMBER_LE: {
			break;
		}
		case B_VM_OPCODE_NUMBER_MOD: {
			break;
		}
		case B_VM_OPCODE_NUMBER_INT_DIV: {
			break;
		}
		case B_VM_OPCODE_NUMBER_TO_STRING: {
			break;
		}
		case B_VM_OPCODE_NUMBER_IS_NAN: {
			break;
		}
		case B_VM_OPCODE_NUMBER_IS_INFINITY: {
			break;
		}
		case B_VM_OPCODE_NUMBER_IS_INFINITY_NEGATIVE: {
			break;
		}
		case B_VM_OPCODE_NUMBER_HASH: {
			break;
		}
		case B_VM_OPCODE_NUMBER_NEG: {
			break;
		}
		case B_VM_OPCODE_NUMBER_INC: {
			break;
		}
		case B_VM_OPCODE_NUMBER_DEC: {
			break;
		}
		case B_VM_OPCODE_INTEGER_SUM: {
			break;
		}
		case B_VM_OPCODE_INTEGER_SUB: {
			break;
		}
		case B_VM_OPCODE_INTEGER_MUL: {
			break;
		}
		case B_VM_OPCODE_INTEGER_DIV: {
			break;
		}
		case B_VM_OPCODE_INTEGER_EQ: {
			break;
		}
		case B_VM_OPCODE_INTEGER_NEQ: {
			break;
		}
		case B_VM_OPCODE_INTEGER_COMPARE: {
			break;
		}
		case B_VM_OPCODE_INTEGER_GT: {
			break;
		}
		case B_VM_OPCODE_INTEGER_GE: {
			break;
		}
		case B_VM_OPCODE_INTEGER_LT: {
			break;
		}
		case B_VM_OPCODE_INTEGER_LE: {
			break;
		}
		case B_VM_OPCODE_INTEGER_AND: {
			break;
		}
		case B_VM_OPCODE_INTEGER_OR: {
			break;
		}
		case B_VM_OPCODE_INTEGER_MOD: {
			break;
		}
		case B_VM_OPCODE_INTEGER_TO_STRING: {
			break;
		}
		case B_VM_OPCODE_INTEGER_HASH: {
			break;
		}
		case B_VM_OPCODE_INTEGER_NEG: {
			break;
		}
		case B_VM_OPCODE_INTEGER_INC: {
			break;
		}
		case B_VM_OPCODE_INTEGER_DEC: {
			break;
		}
		case B_VM_OPCODE_BOOLEAN_NOT: {
			break;
		}
		case B_VM_OPCODE_BOOLEAN_AND: {
			break;
		}
		case B_VM_OPCODE_BOOLEAN_OR: {
			break;
		}
		case B_VM_OPCODE_STRING_SUM: {
			break;
		}
		case B_VM_OPCODE_CONTROL_JUMP: {
			break;
		}
		case B_VM_OPCODE_CONTROL_JUMP_TRUE: {
			break;
		}
		case B_VM_OPCODE_CONTROL_JUMP_FALSE: {
			break;
		}
		case B_VM_OPCODE_CONTROL_JUMP_INT: {
			break;
		}
		case B_VM_OPCODE_CONTROL_RETURN: {
			break;
		}
		case B_VM_OPCODE_DATABASE_OPEN_READ: {
			break;
		}
		case B_VM_OPCODE_DATABASE_OPEN_WRITE: {
			break;
		}
		case B_VM_OPCODE_DATABASE_FETCH: {
			break;
		}
		case B_VM_OPCODE_DATABASE_CLOSE: {
			break;
		}
		case B_VM_OPCODE_DATABASE_FIND_ID: {
			break;
		}
		case B_VM_OPCODE_HALF: {
			return 0;
		}
		default: {
			return 1;
		}
		}
	}
	return 1;
}

b_vm_error_t b_vm_execute(unsigned char* opcode, int length, struct b_vm_object_t** resultObject, double* resultNumber, struct b_vm_object_t** exception) {
	unsigned char* current_opcode = opcode;
	void* object_stack[1024];
	void** current_object_stack = object_stack;
	double number_stack[1024];
	double* current_number_stack = number_stack;
	struct b_vm_table_t* table_stack[32];
	struct b_vm_table_t** current_table_stack = table_stack;
	for (;;) {
		switch (*current_opcode++) {
		case B_VM_OPCODE_STACK_INC: {
			unsigned int count = *((unsigned int*) current_opcode);
			current_object_stack += count;
			current_opcode += sizeof(unsigned int);
			break;
		}
		case B_VM_OPCODE_STACK_DEC: {
			unsigned int count = *((unsigned int*) current_opcode);
			current_object_stack -= count;
			current_opcode += sizeof(unsigned int);
			break;
		}
		case B_VM_OPCODE_STACK_DOUBLE: {
			double value = *((double*) current_opcode);
			current_number_stack++;
			*current_number_stack = value;
			current_opcode += sizeof(double);
			break;
		}
		case B_VM_OPCODE_STACK_INTEGER: {
			unsigned int value = *((unsigned int*) current_opcode);
			current_number_stack++;
			*current_number_stack = value;
			current_opcode += sizeof(unsigned int);
			break;
		}
		case B_VM_OPCODE_STACK_TRUE: {
			current_number_stack++;
			*current_number_stack = 1;
			break;
		}
		case B_VM_OPCODE_STACK_FALSE: {
			current_number_stack++;
			*current_number_stack = 0;
			break;
		}
		case B_VM_OPCODE_STACK_STRING: {
			unsigned int length = *((unsigned int*) current_opcode);
			current_opcode += sizeof(unsigned int);
			current_object_stack++;
			*current_object_stack = current_opcode;
			current_opcode += (length + 1) * sizeof(unsigned char);
			break;
		}
		case B_VM_OPCODE_STACK_NULL: {
			current_object_stack++;
			*current_object_stack = current_opcode;
			break;
		}
		case B_VM_OPCODE_NUMBER_SUM: {
			double value = *current_number_stack;
			current_number_stack--;
			*current_number_stack += value;
			break;
		}
		case B_VM_OPCODE_NUMBER_SUB: {
			double value = *current_number_stack;
			current_number_stack--;
			*current_number_stack -= value;
			break;
		}
		case B_VM_OPCODE_NUMBER_MUL: {
			double value = *current_number_stack;
			current_number_stack--;
			*current_number_stack *= value;
			break;
		}
		case B_VM_OPCODE_NUMBER_DIV: {
			double value = *current_number_stack;
			current_number_stack--;
			if (*current_number_stack != 0.) {
				*current_number_stack /= value;
			}
			break;
		}
		case B_VM_OPCODE_NUMBER_EQ: {
			double value = *current_number_stack;
			current_number_stack--;
			*current_number_stack = *current_number_stack == value ? 1 : 0;
			break;
		}
		case B_VM_OPCODE_NUMBER_NEQ: {
			double value = *current_number_stack;
			current_number_stack--;
			*current_number_stack = *current_number_stack != value ? 1 : 0;
			break;
		}
		case B_VM_OPCODE_NUMBER_COMPARE: {
			double value = *current_number_stack;
			current_number_stack--;
			*current_number_stack -= value;
			break;
		}
		case B_VM_OPCODE_NUMBER_GT: {
			double value = *current_number_stack;
			current_number_stack--;
			*current_number_stack = *current_number_stack > value ? 1 : 0;
			break;
		}
		case B_VM_OPCODE_NUMBER_GE: {
			double value = *current_number_stack;
			current_number_stack--;
			*current_number_stack = *current_number_stack >= value ? 1 : 0;
			break;
		}
		case B_VM_OPCODE_NUMBER_LT: {
			double value = *current_number_stack;
			current_number_stack--;
			*current_number_stack = *current_number_stack < value ? 1 : 0;
			break;
		}
		case B_VM_OPCODE_NUMBER_LE: {
			double value = *current_number_stack;
			current_number_stack--;
			*current_number_stack = *current_number_stack <= value ? 1 : 0;
			break;
		}
		case B_VM_OPCODE_NUMBER_MOD: {
			double value = *current_number_stack;
			current_number_stack--;
			*current_number_stack = (int) *current_number_stack % (int) value;
			break;
		}
		case B_VM_OPCODE_NUMBER_INT_DIV: {
			double value = *current_number_stack;
			current_number_stack--;
			*current_number_stack = (int) *current_number_stack / value;
			break;
		}
		case B_VM_OPCODE_NUMBER_TO_STRING: {
			break;
		}
		case B_VM_OPCODE_NUMBER_IS_NAN: {
			double value = *current_number_stack;
			*current_number_stack = isnan(value) ? 1 : 0;
			break;
		}
		case B_VM_OPCODE_NUMBER_IS_INFINITY: {
			double value = *current_number_stack;
			*current_number_stack = isinf(value) == 1 ? 1 : 0;
			break;
		}
		case B_VM_OPCODE_NUMBER_IS_INFINITY_NEGATIVE: {
			double value = *current_number_stack;
			*current_number_stack = isinf(value) == -1 ? 1 : 0;
			break;
		}
		case B_VM_OPCODE_NUMBER_HASH: {
			double value = *current_number_stack;
			*current_number_stack = (int) value;
			break;
		}
		case B_VM_OPCODE_NUMBER_NEG: {
			*current_number_stack = -*current_number_stack;
			break;
		}
		case B_VM_OPCODE_NUMBER_INC: {
			(*current_number_stack)++;
			break;
		}
		case B_VM_OPCODE_NUMBER_DEC: {
			(*current_number_stack)--;
			break;
		}
//		case B_VM_OPCODE_INTEGER_SUM: {
//			break;
//		}
//		case B_VM_OPCODE_INTEGER_SUB: {
//			break;
//		}
//		case B_VM_OPCODE_INTEGER_MUL: {
//			break;
//		}
//		case B_VM_OPCODE_INTEGER_DIV: {
//			break;
//		}
//		case B_VM_OPCODE_INTEGER_EQ: {
//			break;
//		}
//		case B_VM_OPCODE_INTEGER_NEQ: {
//			break;
//		}
//		case B_VM_OPCODE_INTEGER_COMPARE: {
//			break;
//		}
//		case B_VM_OPCODE_INTEGER_GT: {
//			break;
//		}
//		case B_VM_OPCODE_INTEGER_GE: {
//			break;
//		}
//		case B_VM_OPCODE_INTEGER_LT: {
//			break;
//		}
//		case B_VM_OPCODE_INTEGER_LE: {
//			break;
//		}
//		case B_VM_OPCODE_INTEGER_AND: {
//			break;
//		}
//		case B_VM_OPCODE_INTEGER_OR: {
//			break;
//		}
//		case B_VM_OPCODE_INTEGER_MOD: {
//			break;
//		}
//		case B_VM_OPCODE_INTEGER_TO_STRING: {
//			break;
//		}
//		case B_VM_OPCODE_INTEGER_HASH: {
//			break;
//		}
//		case B_VM_OPCODE_INTEGER_NEG: {
//			break;
//		}
//		case B_VM_OPCODE_INTEGER_INC: {
//			break;
//		}
//		case B_VM_OPCODE_INTEGER_DEC: {
//			break;
//		}
		case B_VM_OPCODE_BOOLEAN_NOT: {
			*current_number_stack = *current_number_stack ? 0 : 1;
			break;
		}
		case B_VM_OPCODE_BOOLEAN_AND: {
			double right = *current_number_stack;
			current_number_stack--;
			*current_number_stack = *current_number_stack && right ? 1 : 0;
			break;
		}
		case B_VM_OPCODE_BOOLEAN_OR: {
			double right = *current_number_stack;
			current_number_stack--;
			*current_number_stack = *current_number_stack || right ? 1 : 0;
			break;
		}
		case B_VM_OPCODE_STRING_SUM: {
			const char* rightChars = *current_object_stack;
			int rightLength = *(unsigned int*) (rightChars - sizeof(unsigned int));
			current_number_stack--;
			const char* leftChars = *current_object_stack;
			int leftLength = *(unsigned int*) (leftChars - sizeof(unsigned int));
			int length = leftLength + rightLength;
			char* value = (char*) malloc((length + 1) * sizeof(char) + sizeof(unsigned int));
			strncpy(value, leftChars, leftLength);
			strncpy(value + leftLength, rightChars, rightLength);
			value[length] = 0;
			*(unsigned int*) (value - sizeof(unsigned int)) = length;
			*current_object_stack = value;
			break;
		}
		case B_VM_OPCODE_CONTROL_JUMP: {
			unsigned int pc = *((unsigned int*) current_opcode);
			current_opcode = opcode + pc;
			current_opcode += sizeof(unsigned int);
			break;
		}
		case B_VM_OPCODE_CONTROL_JUMP_TRUE: {
			if (*current_number_stack == 1) {
				unsigned int pc = *((unsigned int*) current_opcode);
				current_opcode = opcode + pc;
			}
			current_number_stack--;
			current_opcode += sizeof(unsigned int);
			break;
		}
		case B_VM_OPCODE_CONTROL_JUMP_FALSE: {
			if (*current_number_stack == 0) {
				unsigned int pc = *((unsigned int*) current_opcode);
				current_opcode = opcode + pc;
			}
			current_number_stack--;
			current_opcode += sizeof(unsigned int);
			break;
		}
		case B_VM_OPCODE_CONTROL_JUMP_INT: {
			break;
		}
		case B_VM_OPCODE_CONTROL_RETURN: {
			break;
		}
		case B_VM_OPCODE_DATABASE_OPEN_READ: {
			current_table_stack++;
			struct b_vm_table_t* table = *current_table_stack;
			table->bytes = malloc(10);
			break;
		}
		case B_VM_OPCODE_DATABASE_OPEN_WRITE: {
			current_table_stack++;
			break;
		}
		case B_VM_OPCODE_DATABASE_FETCH: {
			break;
		}
		case B_VM_OPCODE_DATABASE_CLOSE: {
			struct b_vm_table_t* table = *current_table_stack;
			free(table->bytes);
			current_table_stack--;
			break;
		}
		case B_VM_OPCODE_DATABASE_FIND_ID: {
			break;
		}
		case B_VM_OPCODE_HALF: {
			if (current_object_stack != object_stack) {
				*resultObject = *current_object_stack;
			}
			if (current_number_stack != number_stack) {
				*resultNumber = *current_number_stack;
			}
			return 0;
		}
		default: {
			return 1;
		}
		}
	}
	return 1;
}
