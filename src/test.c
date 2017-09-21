#include "test.h"
#include "b_vm.h"
#include "io.h"
#include "iphashmap.h"
#include <stdio.h>
#include <assert.h>

static unsigned char ops[8 * 1024];

//void oonsql_test_iphashmap_memory() {
//	printf("oonsql.test.iphashmap.memory...");
//	int a[1], b[1], c[1], d[1], e[1], f[1], g[1];
//	void* v1, *v2, *v3, *v4, *v5, *v6, *v7;
//	double load[10] = { 0.025, 0.75, 0.1, 0.2, 0.3, 0.4, 0.5, 10, 15, 30 };
//	int n, m;
//	for (n = 1; n < 30; n++) {
//		for (m = 0; m < sizeof(load); m++) {
//			{
//				struct iphashmap_t* h = iphashmap_new_memory(n, load[m], 0);
//				iphashmap_free(h);
//				h = iphashmap_new_memory(n, load[m], 0);
//				iphashmap_set(h, 1, a);
//				if (iphashmap_get(h, 1, &v1) || iphashmap_get(h, 2, &v2) || iphashmap_get(h, 3, &v3) || iphashmap_get(h, 4, &v4) || iphashmap_get(h, 5, &v5) || iphashmap_get(h, 6, &v6)
//						|| iphashmap_get(h, 7, &v7)) {
//					assert(0);
//				}
//				if (v1 != a || v2 || v3 || v4 || v5 || v6 || v7) {
//					assert(0);
//				}
//				iphashmap_set(h, 2, b);
//				if (iphashmap_get(h, 1, &v1) || iphashmap_get(h, 2, &v2) || iphashmap_get(h, 3, &v3) || iphashmap_get(h, 4, &v4) || iphashmap_get(h, 5, &v5) || iphashmap_get(h, 6, &v6)
//						|| iphashmap_get(h, 7, &v7)) {
//					assert(0);
//				}
//				if (v1 != a || v2 != b || v3 || v4 || v5 || v6 || v7) {
//					assert(0);
//				}
//				iphashmap_set(h, 3, c);
//				if (iphashmap_get(h, 1, &v1) || iphashmap_get(h, 2, &v2) || iphashmap_get(h, 3, &v3) || iphashmap_get(h, 4, &v4) || iphashmap_get(h, 5, &v5) || iphashmap_get(h, 6, &v6)
//						|| iphashmap_get(h, 7, &v7)) {
//					assert(0);
//				}
//				if (v1 != a || v2 != b || v3 != c || v4 || v5 || v6 || v7) {
//					assert(0);
//				}
//				iphashmap_set(h, 4, d);
//				if (iphashmap_get(h, 1, &v1) || iphashmap_get(h, 2, &v2) || iphashmap_get(h, 3, &v3) || iphashmap_get(h, 4, &v4) || iphashmap_get(h, 5, &v5) || iphashmap_get(h, 6, &v6)
//						|| iphashmap_get(h, 7, &v7)) {
//					assert(0);
//				}
//				if (v1 != a || v2 != b || v3 != c || v4 != d || v5 || v6 || v7) {
//					assert(0);
//				}
//				iphashmap_set(h, 5, e);
//				if (iphashmap_get(h, 1, &v1) || iphashmap_get(h, 2, &v2) || iphashmap_get(h, 3, &v3) || iphashmap_get(h, 4, &v4) || iphashmap_get(h, 5, &v5) || iphashmap_get(h, 6, &v6)
//						|| iphashmap_get(h, 7, &v7)) {
//					assert(0);
//				}
//				if (v1 != a || v2 != b || v3 != c || v4 != d || v5 != e || v6 || v7) {
//					assert(0);
//				}
//				iphashmap_set(h, 6, f);
//				if (iphashmap_get(h, 1, &v1) || iphashmap_get(h, 2, &v2) || iphashmap_get(h, 3, &v3) || iphashmap_get(h, 4, &v4) || iphashmap_get(h, 5, &v5) || iphashmap_get(h, 6, &v6)
//						|| iphashmap_get(h, 7, &v7)) {
//					assert(0);
//				}
//				if (v1 != a || v2 != b || v3 != c || v4 != d || v5 != e || v6 != f || v7) {
//					assert(0);
//				}
//				iphashmap_set(h, 7, g);
//				if (iphashmap_get(h, 1, &v1) || iphashmap_get(h, 2, &v2) || iphashmap_get(h, 3, &v3) || iphashmap_get(h, 4, &v4) || iphashmap_get(h, 5, &v5) || iphashmap_get(h, 6, &v6)
//						|| iphashmap_get(h, 7, &v7)) {
//					assert(0);
//				}
//				if (v1 != a || v2 != b || v3 != c || v4 != d || v5 != e || v6 != f || v7 != g) {
//					assert(0);
//				}
//				iphashmap_free(h);
//			}
//			{
//				struct iphashmap_t* h = iphashmap_new_memory(n, load[m], 0);
//				iphashmap_set(h, 1, a);
//				iphashmap_set(h, 2, b);
//				iphashmap_set(h, 3, c);
//				iphashmap_set(h, 4, d);
//				iphashmap_set(h, 5, e);
//				iphashmap_set(h, 6, f);
//				iphashmap_set(h, 7, g);
//				iphashmap_del(h, 1);
//				if (iphashmap_get(h, 1, &v1) || iphashmap_get(h, 2, &v2) || iphashmap_get(h, 3, &v3) || iphashmap_get(h, 4, &v4) || iphashmap_get(h, 5, &v5) || iphashmap_get(h, 6, &v6)
//						|| iphashmap_get(h, 7, &v7)) {
//					assert(0);
//				}
//				if (v1 || v2 != b || v3 != c || v4 != d || v5 != e || v6 != f || v7 != g) {
//					assert(0);
//				}
//				iphashmap_del(h, 2);
//				if (iphashmap_get(h, 1, &v1) || iphashmap_get(h, 2, &v2) || iphashmap_get(h, 3, &v3) || iphashmap_get(h, 4, &v4) || iphashmap_get(h, 5, &v5) || iphashmap_get(h, 6, &v6)
//						|| iphashmap_get(h, 7, &v7)) {
//					assert(0);
//				}
//				if (v1 || v2 || v3 != c || v4 != d || v5 != e || v6 != f || v7 != g) {
//					assert(0);
//				}
//				iphashmap_del(h, 3);
//				if (iphashmap_get(h, 1, &v1) || iphashmap_get(h, 2, &v2) || iphashmap_get(h, 3, &v3) || iphashmap_get(h, 4, &v4) || iphashmap_get(h, 5, &v5) || iphashmap_get(h, 6, &v6)
//						|| iphashmap_get(h, 7, &v7)) {
//					assert(0);
//				}
//				if (v1 || v2 || v3 || v4 != d || v5 != e || v6 != f || v7 != g) {
//					assert(0);
//				}
//				iphashmap_del(h, 4);
//				if (iphashmap_get(h, 1, &v1) || iphashmap_get(h, 2, &v2) || iphashmap_get(h, 3, &v3) || iphashmap_get(h, 4, &v4) || iphashmap_get(h, 5, &v5) || iphashmap_get(h, 6, &v6)
//						|| iphashmap_get(h, 7, &v7)) {
//					assert(0);
//				}
//				if (v1 || v2 || v3 || v4 || v5 != e || v6 != f || v7 != g) {
//					assert(0);
//				}
//				iphashmap_del(h, 5);
//				if (iphashmap_get(h, 1, &v1) || iphashmap_get(h, 2, &v2) || iphashmap_get(h, 3, &v3) || iphashmap_get(h, 4, &v4) || iphashmap_get(h, 5, &v5) || iphashmap_get(h, 6, &v6)
//						|| iphashmap_get(h, 7, &v7)) {
//					assert(0);
//				}
//				if (v1 || v2 || v3 || v4 || v5 || v6 != f || v7 != g) {
//					assert(0);
//				}
//				iphashmap_del(h, 6);
//				if (iphashmap_get(h, 1, &v1) || iphashmap_get(h, 2, &v2) || iphashmap_get(h, 3, &v3) || iphashmap_get(h, 4, &v4) || iphashmap_get(h, 5, &v5) || iphashmap_get(h, 6, &v6)
//						|| iphashmap_get(h, 7, &v7)) {
//					assert(0);
//				}
//				if (v1 || v2 || v3 || v4 || v5 || v6 || v7 != g) {
//					assert(0);
//				}
//				iphashmap_del(h, 7);
//				if (iphashmap_get(h, 1, &v1) || iphashmap_get(h, 2, &v2) || iphashmap_get(h, 3, &v3) || iphashmap_get(h, 4, &v4) || iphashmap_get(h, 5, &v5) || iphashmap_get(h, 6, &v6)
//						|| iphashmap_get(h, 7, &v7)) {
//					assert(0);
//				}
//				if (v1 || v2 || v3 || v4 || v5 || v6 || v7) {
//					assert(0);
//				}
//				iphashmap_free(h);
//			}
//		}
//	}
//	printf("ok\n");
//}

void oonsql_test_double() {
	printf("oonsql.test.double...");
	double values[14] = { -0.5, 0.752, -1, 0, 0.5, 1, 2, 4, 8, 10, 1000, 1024, 2048, 4294967294 };
	int size = sizeof(values) / sizeof(double);
	int n;
	for (n = 0; n < size; n++) {
		unsigned char bytes[8];
		b_double_write(bytes, values[n]);
		double value = b_double_read(bytes);
		if (values[n] != value) {
			b_double_write(bytes, values[n]);
			value = b_double_read(bytes);
		}
		double delta = value - values[n];
		if (delta < 0) {
			delta = -delta;
		}
		if (delta < 0.0001) {
			printf("");
		}
		assert(delta <= 0.0001);
	}
	printf("ok\n");
}

void oonsql_test_vm_primitive_true() {
	printf("oonsql.test.vm.primitive.true...");
	unsigned char* cops = ops;
	*cops++ = B_VM_OPCODE_STACK_TRUE;
	*cops++ = B_VM_OPCODE_HALF;
	assert(!b_vm_compile(ops));
	struct b_vm_object_t* ex = 0;
	struct b_vm_object_t* obj = 0;
	b_vm_number_t num = 0.;
	assert(!b_vm_execute(ops, 0, &obj, &num, &ex));
	assert(ex == 0);
	assert(obj == 0);
	assert(num == 1);
	printf("ok\n");
}

void oonsql_test_vm_primitive_false() {
	printf("oonsql.test.vm.primitive.false...");
	unsigned char* cops = ops;
	*cops++ = B_VM_OPCODE_STACK_FALSE;
	*cops++ = B_VM_OPCODE_HALF;
	assert(!b_vm_compile(ops));
	struct b_vm_object_t* ex = 0;
	struct b_vm_object_t* obj = 0;
	b_vm_number_t num = 1.;
	assert(!b_vm_execute(ops, 0, &obj, &num, &ex));
	assert(ex == 0);
	assert(obj == 0);
	assert(num == 0);
	printf("ok\n");
}

void oonsql_test_vm_primitive_int() {
	printf("oonsql.test.vm.primitive.int...");
	unsigned int n, values[10] = { 0, 1, 2, 4, 8, 10, 1000, 1024, 2048, 4294967294 };
	int size = sizeof(values) / sizeof(unsigned int);
	for (n = 0; n < size; n++) {
		unsigned char* cops = ops;
		*cops++ = B_VM_OPCODE_STACK_INTEGER;
		*cops++ = (values[n] >> 24) & 0xff;
		*cops++ = (values[n] >> 16) & 0xff;
		*cops++ = (values[n] >> 8) & 0xff;
		*cops++ = (values[n]) & 0xff;
		*cops++ = B_VM_OPCODE_HALF;
		assert(!b_vm_compile(ops));
		struct b_vm_object_t* ex = 0;
		struct b_vm_object_t* obj = 0;
		b_vm_number_t num = 0.;
		assert(!b_vm_execute(ops, 0, &obj, &num, &ex));
		assert(ex == 0);
		assert(obj == 0);
		assert(num == values[n]);
	}
	printf("ok\n");
}

void oonsql_test_vm_primitive_double() {
	printf("oonsql.test.vm.primitive.double...");
	unsigned int n, values[10] = { 0, 1, 2, 4, 8, 10, 1000, 1024, 2048, 4294967294 };
	int size = sizeof(values) / sizeof(unsigned int);
	for (n = 0; n < size; n++) {
		unsigned char* cops = ops;
		*cops++ = B_VM_OPCODE_STACK_INTEGER;
		*cops++ = (values[n] >> 24) & 0xff;
		*cops++ = (values[n] >> 16) & 0xff;
		*cops++ = (values[n] >> 8) & 0xff;
		*cops++ = (values[n]) & 0xff;
		*cops++ = B_VM_OPCODE_HALF;
		assert(!b_vm_compile(ops));
		struct b_vm_object_t* ex = 0;
		struct b_vm_object_t* obj = 0;
		b_vm_number_t num = 0.;
		assert(!b_vm_execute(ops, 0, &obj, &num, &ex));
		assert(ex == 0);
		assert(obj == 0);
		assert(num == values[n]);
	}
	printf("ok\n");
}

void oonsql_test() {
//	oonsql_test_iphashmap_memory();
	oonsql_test_vm_primitive_true();
	oonsql_test_vm_primitive_false();
	oonsql_test_vm_primitive_int();
//	oonsql_test_double();
	printf("done\n");
}
