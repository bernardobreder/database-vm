//#include<sys/stat.h>
//#include <stdlib.h>
//#include <string.h>
//#include <stdio.h>
//#include "iphashmap.h"
//#include "io.h"
//
//struct iphashmap_item_t {
//	unsigned int key;
//	void* value;
//	struct iphashmap_item_t* next;
//};
//
//struct iphashmap_entry_t {
//	unsigned int index;
//	unsigned char changed;
//	struct iphashmap_item_t* item;
//	struct iphashmap_entry_t* next;
//};
//
//struct iphashmap_t {
//	void* (*openForReadFunc)(const char*);
//	void* (*openForWriteFunc)(const char*);
//	void (*closeFunc)(void*);
//	int (*readFunc)(void*, unsigned char*, unsigned int);
//	int (*writeFunc)(void*, unsigned char*, unsigned int);
//	unsigned char (*writeValueFunc)(void*, int (*)(void*, unsigned char*, unsigned int), void* value);
//	void* (*readValueFunc)(void*, int (*)(void*, unsigned char*, unsigned int));
//	void (*freeFunc)(void*);
//	char* tableDir;
//	char* tableFile;
//	// Fator de carga
//	float loadFactor;
//	// Número máximo de elementos para ser feito um resize
//	unsigned int threshold;
//	// Quantidade de entidades
//	unsigned int entryCount;
//	// Primeira entidade
//	struct iphashmap_entry_t* entrys;
//	// Quantidade de elementos
//	unsigned int size;
//};
//
//static struct iphashmap_t* iphashmap_new(void* (*openForReadFunc)(const char*), void* (*openForWriteFunc)(const char*), void (*closeFunc)(void*), int (*readFunc)(void*, unsigned char*, unsigned int),
//		int (*writeFunc)(void*, unsigned char*, unsigned int), void* (*readValueFunc)(void*, int (*)(void*, unsigned char*, unsigned int)),
//		unsigned char (*writeValueFunc)(void*, int (*)(void*, unsigned char*, unsigned int), void* value), void (*freeFunc)(void*), char* tableDir, char* tableFile, unsigned int tableCount,
//		unsigned int size, float loadFactor) {
//	struct iphashmap_t* self = (struct iphashmap_t*) malloc(sizeof(struct iphashmap_t));
//	if (!self) {
//		return 0;
//	}
//	self->openForReadFunc = openForReadFunc;
//	self->openForWriteFunc = openForWriteFunc;
//	self->closeFunc = closeFunc;
//	self->readFunc = readFunc;
//	self->writeFunc = writeFunc;
//	self->freeFunc = freeFunc;
//	self->tableDir = tableDir;
//	self->tableFile = tableFile;
//	self->loadFactor = loadFactor;
//	self->threshold = loadFactor * tableCount;
//	self->entryCount = tableCount;
//	self->size = size;
//	self->entrys = 0;
//	return self;
//}
//
//struct iphashmap_t* iphashmap_new_read(void* (*openForReadFunc)(const char*), void* (*openForWriteFunc)(const char*), void (*closeFunc)(void*), int (*readFunc)(void*, unsigned char*, unsigned int),
//		int (*writeFunc)(void*, unsigned char*, unsigned int), void* (*readValueFunc)(void*, int (*)(void*, unsigned char*, unsigned int)),
//		unsigned char (*writeValueFunc)(void*, int (*)(void*, unsigned char*, unsigned int), void* value), void (*freeFunc)(void*), char* tableDir, char* tableFile) {
//	if (!openForReadFunc || !readFunc) {
//		return 0;
//	}
//	void* file = openForReadFunc(tableFile);
//	if (!file) {
//		return 0;
//	}
//	unsigned char buffer[sizeof(double) + 2 * sizeof(unsigned int)];
//	if (readFunc(file, buffer, sizeof(buffer)) != sizeof(buffer)) {
//		if (closeFunc) {
//			closeFunc(file);
//		}
//		return 0;
//	}
//	unsigned char* aux = buffer;
//	float loadFactor = b_double_read(aux);
//	aux += sizeof(double);
//	unsigned int tableCount = b_int_read(aux);
//	aux += sizeof(unsigned int);
//	unsigned int size = b_int_read(aux);
//	aux += sizeof(unsigned int);
//	if (closeFunc) {
//		closeFunc(file);
//	}
//	return iphashmap_new(openForReadFunc, openForWriteFunc, closeFunc, readFunc, writeFunc, readValueFunc, writeValueFunc, freeFunc, tableDir, tableFile, tableCount, size, loadFactor);
//}
//
//struct iphashmap_t* iphashmap_new_write(void* (*openForReadFunc)(const char*), void* (*openForWriteFunc)(const char*), void (*closeFunc)(void*), int (*readFunc)(void*, unsigned char*, unsigned int),
//		int (*writeFunc)(void*, unsigned char*, unsigned int), void* (*readValueFunc)(void*, int (*)(void*, unsigned char*, unsigned int)),
//		unsigned char (*writeValueFunc)(void*, int (*)(void*, unsigned char*, unsigned int), void* value), void (*freeFunc)(void*), char* tableDir, char* tableFile, int initialCapacity,
//		float loadFactor) {
//	unsigned int size = 0;
//	unsigned int tableCount = 1;
//	while (tableCount < initialCapacity) {
//		tableCount <<= 1;
//	}
//	if (openForWriteFunc) {
//		void* file = openForWriteFunc(tableFile);
//		if (!file) {
//			return 0;
//		}
//		if (writeFunc) {
//			unsigned char buffer[8 + 4 + 4];
//			unsigned char* aux = buffer;
//			b_double_write(aux, loadFactor);
//			aux += sizeof(double);
//			b_int_write(aux, tableCount);
//			aux += sizeof(unsigned int);
//			b_int_write(aux, size);
//			aux += sizeof(unsigned int);
//			if (writeFunc(file, buffer, sizeof(buffer)) != sizeof(buffer)) {
//				if (closeFunc) {
//					closeFunc(file);
//				}
//				return 0;
//			}
//		}
//		if (closeFunc) {
//			closeFunc(file);
//		}
//	}
//	return iphashmap_new(openForReadFunc, openForWriteFunc, closeFunc, readFunc, writeFunc, readValueFunc, writeValueFunc, freeFunc, tableDir, tableFile, tableCount, size, loadFactor);
//}
//
//struct iphashmap_t* iphashmap_new_memory(int initialCapacity, float loadFactor, void (*freeFunc)(void*)) {
//	unsigned int size = 0;
//	unsigned int tableCount = 1;
//	while (tableCount < initialCapacity) {
//		tableCount <<= 1;
//	}
//	return iphashmap_new(0, 0, 0, 0, 0, 0, 0, freeFunc, 0, 0, tableCount, size, loadFactor);
//}
//
//static unsigned char iphashmap_entry_save(struct iphashmap_t* self, struct iphashmap_entry_t* entry) {
//	unsigned int tableDirLen = strlen(self->tableDir);
//	unsigned int tableFileLen = strlen(self->tableFile);
//	char filename[tableDirLen + 1 + tableFileLen + 12 + 1];
//	// Constroi o nome do arquivo
//	{
//		strncpy(filename, self->tableDir, tableDirLen);
//		filename[tableDirLen] = '/';
//		strncpy(filename + tableDirLen + 1, self->tableDir, tableDirLen);
//		memset(filename + tableDirLen + 1 + tableFileLen, 0, 12 + 1);
//		filename[tableDirLen + 1 + tableFileLen] = '.';
//		b_uint_to_string(entry->index, filename + tableDirLen + 1 + tableFileLen + 1, 10);
//	}
//	void* file = self->openForWriteFunc(filename);
//	if (!file) {
//		return 0;
//	}
//	unsigned int size = 0;
//	// Calcula a quantidade de valores da entidade
//	{
//		struct iphashmap_item_t* aux = entry->item;
//		while (aux) {
//			size++;
//			aux = aux->next;
//		}
//	}
//	// Escreva no arquivo a quantidade de valores da entidade
//	{
//		char sizeBuffer[sizeof(unsigned int)];
//		b_uint_to_string(size, sizeBuffer, 10);
//		if (self->writeFunc(file, (unsigned char*) sizeBuffer, sizeof(sizeBuffer)) != sizeof(sizeBuffer)) {
//			if (self->closeFunc) {
//				self->closeFunc(file);
//			}
//			return 0;
//		}
//	}
//	// Escreva cada entidade
//	{
//		struct iphashmap_item_t* aux = entry->item;
//		while (aux) {
//			if (self->writeValueFunc(file, self->writeFunc, aux->value)) {
//				if (self->closeFunc) {
//					self->closeFunc(file);
//				}
//				return 0;
//			}
//			aux = aux->next;
//		}
//	}
//	if (self->closeFunc) {
//		self->closeFunc(file);
//	}
//	return 0;
//}
//
//static void iphashmap_entry_free(struct iphashmap_entry_t* entry, void (*freeFunc)(void*)) {
//	struct iphashmap_item_t* item = entry->item;
//	while (item) {
//		if (freeFunc) {
//			if (item->value) {
//				freeFunc(item->value);
//			}
//		}
//		struct iphashmap_item_t* aux = item;
//		item = item->next;
//		free(aux);
//	}
//}
//
//static struct iphashmap_entry_t* iphashmap_entry_load(struct iphashmap_t* self, unsigned indexFor) {
//	unsigned int tableDirLen = strlen(self->tableDir);
//	unsigned int tableFileLen = strlen(self->tableFile);
//	char filename[tableDirLen + 1 + tableFileLen + 12 + 1];
//	// Constroi o nome do arquivo
//	{
//		strncpy(filename, self->tableDir, tableDirLen);
//		filename[tableDirLen] = '/';
//		strncpy(filename + tableDirLen + 1, self->tableDir, tableDirLen);
//		memset(filename + tableDirLen + 1 + tableFileLen, 0, 12 + 1);
//		filename[tableDirLen + 1 + tableFileLen] = '.';
//		b_uint_to_string(indexFor, filename + tableDirLen + 1 + tableFileLen + 1, 10);
////		sprintf(filename + tableDirLen + 1 + tableFileLen + 1, "%d", indexFor);
//	}
//	void* file = self->openForReadFunc(filename);
//	if (!file) {
//		return 0;
//	}
//	unsigned char sizeBuffer[sizeof(unsigned int) + 1];
//	if (self->readFunc(file, sizeBuffer, sizeof(sizeBuffer)) != sizeof(sizeBuffer)) {
//		if (self->closeFunc) {
//			self->closeFunc(file);
//		}
//		return 0;
//	}
//	sizeBuffer[sizeof(unsigned int)] = 0;
//	unsigned int size = b_string_to_int((char*) sizeBuffer);
//	struct iphashmap_entry_t* entry = (struct iphashmap_entry_t*) malloc(sizeof(struct iphashmap_entry_t));
//	if (!entry) {
//		return 0;
//	}
//	entry->changed = 0;
//	entry->index = indexFor;
//	entry->next = 0;
//	struct iphashmap_item_t* items = (struct iphashmap_item_t*) malloc(size * sizeof(struct iphashmap_item_t));
//	if (!items) {
//		free(entry);
//		return 0;
//	}
//	entry->item = items;
//	int n;
//	for (n = 0; n < size - 1; n++) {
//		struct iphashmap_item_t* aux = items + n;
//		aux->value = 0;
//		aux->next = items + (n + 1);
//	}
//	struct iphashmap_item_t* aux = items;
//	unsigned char keyBuffer[sizeof(unsigned int)];
//	for (n = 0; n < size; n++) {
//		if (self->readFunc(file, keyBuffer, sizeof(unsigned int)) != sizeof(unsigned int)) {
//			if (self->closeFunc) {
//				self->closeFunc(file);
//			}
//			iphashmap_entry_free(entry, self->freeFunc);
//			return 0;
//		}
//		unsigned int key = b_int_read(keyBuffer);
//		aux->key = key;
//		void* value = self->readValueFunc(file, self->readFunc);
//		if (!value) {
//			if (self->closeFunc) {
//				self->closeFunc(file);
//			}
//			iphashmap_entry_free(entry, self->freeFunc);
//			return 0;
//		}
//		aux->value = value;
//		aux = aux->next;
//	}
//	if (self->closeFunc) {
//		self->closeFunc(file);
//	}
//	return entry;
//}
//
//void iphashmap_free(struct iphashmap_t* self) {
//	if (self) {
//		if (self->entrys) {
//			struct iphashmap_entry_t* entry = self->entrys;
//			while (entry) {
//				if (entry->changed) {
//					iphashmap_entry_save(self, entry);
//				}
//				iphashmap_entry_free(entry, self->freeFunc);
//				entry = entry->next;
//			}
//		}
//		free(self);
//	}
//}
//
//unsigned char iphashmap_get(struct iphashmap_t* self, unsigned int key, void** value) {
//	int indexFor = key & (self->entryCount - 1);
//	struct iphashmap_entry_t* entry = self->entrys;
//	while (entry && entry->index != indexFor) {
//		entry = entry->next;
//	}
//	if (!entry) {
//		entry = iphashmap_entry_load(self, indexFor);
//		if (!entry) {
//			return 1;
//		}
//		entry->next = self->entrys;
//		self->entrys = entry;
//	}
//	struct iphashmap_item_t* item = entry->item;
//	while (item) {
//		if (item->key == key) {
//			*value = item->value;
//			return 0;
//		}
//		item = item->next;
//	}
//	*value = 0;
//	return 0;
//}
//
//static unsigned char iphashmap_resize(struct iphashmap_t* self, unsigned int tableCount) {
////	struct iphashmap_item_t** newTable = (struct iphashmap_item_t**) calloc(tableCount, sizeof(struct iphashmap_item_t*));
////	if (!newTable) {
////		return 1;
////	}
//	struct iphashmap_entry_t* dstEntry;
//	int indexFor;
//	for (indexFor = 0; indexFor < self->entryCount; indexFor++) {
//		struct iphashmap_entry_t* entry = self->entrys;
//		while (entry && entry->index != indexFor) {
//			entry = entry->next;
//		}
//		if (!entry) {
//			entry = iphashmap_entry_load(self, indexFor);
//		}
//		struct iphashmap_item_t* item = entry->item;
//		while (entry) {
//			struct iphashmap_item_t* next = entry->next;
//			int i = entry->key & (tableCount - 1);
//			entry->next = newTable[i];
//			newTable[i] = entry;
//			if (entryExist) {
//				entryExist[i] = 1;
//			}
//			entry = next;
//		}
//	}
//	free(self->tableChanged);
//	free(self->entryExist);
//	free(self->table);
//	self->table = newTable;
//	self->entryCount = tableCount;
//	self->threshold = tableCount * self->loadFactor;
//	self->tableChanged = tableChanged;
//	self->entryExist = entryExist;
//	if (self->tableChanged) {
//		memset(self->tableChanged, 1, tableCount);
//	}
//	return 0;
//}
//
//unsigned char iphashmap_set(struct iphashmap_t* self, unsigned int key, void* value) {
//	int indexFor = key & (self->entryCount - 1);
//	struct iphashmap_item_t* entry = self->table[indexFor];
//	if (!entry && self->entryExist && self->entryExist[indexFor]) {
//		entry = self->table[indexFor];
//		if (!entry) {
//			self->table[indexFor] = entry = iphashmap_entry_load(self, indexFor);
//			if (!entry) {
//				return 1;
//			}
//		}
//	}
//	while (entry) {
//		if (entry->key == key) {
//			entry->value = value;
//			if (self->tableChanged) {
//				self->tableChanged[indexFor] = 1;
//			}
//			return 0;
//		}
//		entry = entry->next;
//	}
//	entry = (struct iphashmap_item_t*) malloc(sizeof(struct iphashmap_item_t));
//	if (!entry) {
//		return 1;
//	}
//	if (self->tableChanged) {
//		self->tableChanged[indexFor] = 1;
//	}
//	entry->key = key;
//	entry->value = value;
//	entry->next = self->table[indexFor];
//	self->table[indexFor] = entry;
//	if (self->size++ >= self->threshold) {
//		if (iphashmap_resize(self, 2 * self->entryCount)) {
//			self->size--;
//			self->table[indexFor] = entry->next;
//			free(entry);
//			return 1;
//		}
//	}
//	return 0;
//}
//
//unsigned char iphashmap_del(struct iphashmap_t* self, unsigned int key) {
//	int indexFor = key & (self->entryCount - 1);
//	struct iphashmap_item_t* entry = self->table[indexFor];
//	if (!entry && self->entryExist && self->entryExist[indexFor]) {
//		entry = self->table[indexFor];
//		if (!entry) {
//			self->table[indexFor] = entry = iphashmap_entry_load(self, indexFor);
//			if (!entry) {
//				return 1;
//			}
//		}
//	}
//	struct iphashmap_item_t* last = 0;
//	while (entry) {
//		if (entry->key == key) {
//			if (last) {
//				last->next = entry->next;
//			} else {
//				self->table[indexFor] = entry->next;
//			}
//			if (self->freeFunc) {
//				self->freeFunc(entry->value);
//			}
//			if (self->tableChanged) {
//				self->tableChanged[indexFor] = 1;
//			}
//			free(entry);
//			if (self->size-- >= self->threshold) {
//				if (iphashmap_resize(self, self->entryCount / 2)) {
//					if (last) {
//						last->next = entry;
//					} else {
//						self->table[indexFor] = entry;
//					}
//					self->size++;
//					return 1;
//				}
//			}
//			return 0;
//		}
//		last = entry;
//		entry = entry->next;
//	}
//
//	return 0;
//}
