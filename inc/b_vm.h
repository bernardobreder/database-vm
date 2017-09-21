#ifndef BREDER_VM_H
#define BREDER_VM_H

/**
 * Especifica um tipo para a maquina virtual
 */
typedef double b_vm_number_t;

typedef unsigned char b_vm_error_t;

struct b_vm_object_t {
	unsigned int classId;
};

struct b_vm_table_t {
	unsigned char* bytes;
};

struct b_vm_t {
	int version;
	int maxStack;
};

#define B_VM_OPCODE_STACK_INC 1
#define B_VM_OPCODE_STACK_DEC 2
#define B_VM_OPCODE_STACK_STRING 3
#define B_VM_OPCODE_STACK_DOUBLE 4
#define B_VM_OPCODE_STACK_INTEGER 5
#define B_VM_OPCODE_STACK_TRUE 6
#define B_VM_OPCODE_STACK_FALSE 7
#define B_VM_OPCODE_STACK_NULL 8
#define B_VM_OPCODE_STACK_TERNARY 9

#define B_VM_OPCODE_NUMBER_SUM 20
#define B_VM_OPCODE_NUMBER_SUB 21
#define B_VM_OPCODE_NUMBER_MUL 22
#define B_VM_OPCODE_NUMBER_DIV 23
#define B_VM_OPCODE_NUMBER_EQ 24
#define B_VM_OPCODE_NUMBER_NEQ 25
#define B_VM_OPCODE_NUMBER_COMPARE 26
#define B_VM_OPCODE_NUMBER_GT 27
#define B_VM_OPCODE_NUMBER_GE 28
#define B_VM_OPCODE_NUMBER_LT 29
#define B_VM_OPCODE_NUMBER_LE 30
#define B_VM_OPCODE_NUMBER_MOD 31
#define B_VM_OPCODE_NUMBER_INT_DIV 32
#define B_VM_OPCODE_NUMBER_TO_STRING 33
#define B_VM_OPCODE_NUMBER_IS_NAN 34
#define B_VM_OPCODE_NUMBER_IS_INFINITY 35
#define B_VM_OPCODE_NUMBER_IS_INFINITY_NEGATIVE 40
#define B_VM_OPCODE_NUMBER_HASH 36
#define B_VM_OPCODE_NUMBER_NEG 37
#define B_VM_OPCODE_NUMBER_INC 38
#define B_VM_OPCODE_NUMBER_DEC 39

#define B_VM_OPCODE_INTEGER_SUM 60
#define B_VM_OPCODE_INTEGER_SUB 61
#define B_VM_OPCODE_INTEGER_MUL 62
#define B_VM_OPCODE_INTEGER_DIV 63
#define B_VM_OPCODE_INTEGER_EQ 64
#define B_VM_OPCODE_INTEGER_NEQ 65
#define B_VM_OPCODE_INTEGER_COMPARE 66
#define B_VM_OPCODE_INTEGER_GT 67
#define B_VM_OPCODE_INTEGER_GE 68
#define B_VM_OPCODE_INTEGER_LT 69
#define B_VM_OPCODE_INTEGER_LE 70
#define B_VM_OPCODE_INTEGER_AND 71
#define B_VM_OPCODE_INTEGER_OR 72
#define B_VM_OPCODE_INTEGER_MOD 73
#define B_VM_OPCODE_INTEGER_TO_STRING 74
#define B_VM_OPCODE_INTEGER_HASH 75
#define B_VM_OPCODE_INTEGER_NEG 76
#define B_VM_OPCODE_INTEGER_INC 77
#define B_VM_OPCODE_INTEGER_DEC 78

#define B_VM_OPCODE_BOOLEAN_NOT 90
#define B_VM_OPCODE_BOOLEAN_AND 91
#define B_VM_OPCODE_BOOLEAN_OR 92

#define B_VM_OPCODE_STRING_SUM 100

#define B_VM_OPCODE_CONTROL_JUMP 150
#define B_VM_OPCODE_CONTROL_JUMP_TRUE 151
#define B_VM_OPCODE_CONTROL_JUMP_FALSE 152
#define B_VM_OPCODE_CONTROL_JUMP_INT 153
#define B_VM_OPCODE_CONTROL_RETURN 154

#define B_VM_OPCODE_DATABASE_OPEN_READ 200
#define B_VM_OPCODE_DATABASE_OPEN_WRITE 201
#define B_VM_OPCODE_DATABASE_FETCH 202
#define B_VM_OPCODE_DATABASE_CLOSE 203
#define B_VM_OPCODE_DATABASE_FIND_ID 204

#define B_VM_OPCODE_HALF 255

/**
 * Constroi uma máquina virtual com as configurações padrões
 */
struct b_vm_t* b_vm_new_default();

/**
 * Executa um conjunto de opcodes e retorna um objeto ou nulo caso não tenha que retornar
 */
b_vm_error_t b_vm_execute(unsigned char* opcodes, int length, struct b_vm_object_t** resultObject, double* resultNumber, struct b_vm_object_t** exception);

b_vm_error_t b_vm_compile(unsigned char* opcodes);

#endif
