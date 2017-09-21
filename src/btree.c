#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define HALF_MAX 10

struct btree_t {
	int rootId;
};

struct btree_node_t {
	unsigned int id;
	unsigned int keys[HALF_MAX * 2 - 1];
	void* values[HALF_MAX * 2 - 1];
	unsigned int children[HALF_MAX * 2];
	unsigned char leaf;
	unsigned char childrenSize;
	unsigned char keySize;
};

unsigned char btree_node_is_full(struct btree_node_t* self) {
	return self->childrenSize + 1 == 2 * HALF_MAX;
}

unsigned char btree_node_is_minimal(struct btree_node_t* self) {
	return self->childrenSize + 1 == HALF_MAX;
}

static struct btree_node_t* btree_node_new(unsigned char leaf) {
	struct btree_node_t* self = (struct btree_node_t*) calloc(1, sizeof(struct btree_node_t));
	if (!self) {
		return 0;
	}
	self->leaf = leaf;
	self->childrenSize = 0;
	self->keySize = 0;
	return self;
}

static double btree_node_indexOf(struct btree_node_t* self, unsigned int key) {
	int i;
	for (i = 0; i < self->keySize; i++) {
		if (self->keys[i] == key) {
			return i;
		}
		if (self->keys[i] > key) {
			return i + 0.5;
		}
	}
	return self->keySize + 0.5;
}

static double btree_node_merge_children(struct btree_node_t* self, unsigned int childrenIndex, struct btree_node_t* child, struct btree_node_t* sibling) {
	child->keys[child->keySize] = self->keys[childrenIndex];
	child->values[child->keySize] = self->values[childrenIndex];
	child->childrenSize++;
	memcpy(self->keys + childrenIndex, self->keys + childrenIndex + 1, (self->keySize - childrenIndex - 1) * sizeof(unsigned int));
	memcpy(self->values + childrenIndex, self->values + childrenIndex + 1, (self->keySize - childrenIndex - 1) * sizeof(void*));
	self->keySize--;
	memcpy(self->children + childrenIndex + 1, self->children + childrenIndex + 2, (self->childrenSize - childrenIndex - 2) * sizeof(unsigned int));
	self->childrenSize--;
	if (!child->leaf) {
		int firstChildIdOfSibling = sibling->children[0];
		memcpy(sibling->children, sibling->children + 1, (sibling->childrenSize - 1) * sizeof(unsigned int));
		sibling->childrenSize--;
		child->children[child->childrenSize++] = firstChildIdOfSibling;
	} else {

	}
}

static void btree_node_add_locally(struct btree_node_t* self, int key) {
	double d = btree_node_indexOf(self, key);
	int i = (int) d;
	if (i != d) {
		memcpy(self->keys + i + 1, self->keys + i, (self->keySize - i) * sizeof(unsigned int));
		self->keys[i] = key;
		self->values[i] = 0;
		self->keySize++;
		if (!self->leaf) {
			memcpy(self->children + i + 2, self->children + i + 1, (self->keySize - i - 1) * sizeof(void*));
			self->children[i + 1] = 0;
			self->childrenSize++;
		}
	}
}

static unsigned char btree_node_add(struct btree_node_t* self, struct btree_t* btree, unsigned int key) {
	struct btree_node_t* node = self;
	while (!node->leaf) {
		double d = btree_node_indexOf(node, key);
		int i = (int) d;
		if (i == d) {
			return 0;
		} else {
			unsigned int childId = node->children[i];
			struct btree_node_t* child = btree_load_node(btree, childId);
			if (!child) {
				return 1;
			}
			if (btree_node_is_full(child)) {
				btree_node_split(i, child);
			} else {
				btree_write_node(btree, node);
				node = child;
			}
		}
	}
	btree_node_add_locally(node, key);
	btree_write_node(btree, node);
}

static struct btree_node_t* btree_node_add_create_right_sibling(struct btree_node_t* self, struct btree_t* btree) {
	struct btree_node_t* sibling = btree_node_new(self->leaf);
	if (!sibling) {
		return 0;
	}
	memcpy(sibling->keys, self->keys + HALF_MAX, (HALF_MAX - 1) * sizeof(unsigned int));
	memcpy(sibling->values, self->values + HALF_MAX, (HALF_MAX - 1) * sizeof(void*));
	sibling->keySize = HALF_MAX - 1;
	if (!self->leaf) {
		memcpy(sibling->children, self->children + HALF_MAX, HALF_MAX * sizeof(unsigned int));
		sibling->childrenSize = HALF_MAX;
	}
	btree_write_node(btree, sibling);
	return 0;
}

struct btree_t* btree_new() {
	struct btree_t* self = (struct btree_t*) malloc(sizeof(struct btree_t));
	if (!self) {
		return 0;
	}
	return self;
}

void btree_free(struct btree_t* self) {
	free(self);
}
