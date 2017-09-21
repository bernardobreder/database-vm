#ifndef BREDER_IPHASHMAP_H
#define BREDER_IPHASHMAP_H

struct iphashmap_t* iphashmap_new_read(void* (*openForReadFunc)(const char*), void* (*openForWriteFunc)(const char*), void (*closeFunc)(void*), int (*readFunc)(void*, unsigned char*, unsigned int),
		int (*writeFunc)(void*, unsigned char*, unsigned int), void* (*readValueFunc)(void*, int (*)(void*, unsigned char*, unsigned int)),
		unsigned char (*writeValueFunc)(void*, int (*)(void*, unsigned char*, unsigned int), void* value), void (*freeFunc)(void*), char* tableDir, char* tableFile);

struct iphashmap_t* iphashmap_new_write(void* (*openForReadFunc)(const char*), void* (*openForWriteFunc)(const char*), void (*closeFunc)(void*), int (*readFunc)(void*, unsigned char*, unsigned int),
		int (*writeFunc)(void*, unsigned char*, unsigned int), void* (*readValueFunc)(void*, int (*)(void*, unsigned char*, unsigned int)),
		unsigned char (*writeValueFunc)(void*, int (*)(void*, unsigned char*, unsigned int), void* value), void (*freeFunc)(void*), char* tableDir, char* tableFile, int initialCapacity,
		float loadFactor);

struct iphashmap_t* iphashmap_new_memory(int initialCapacity, float loadFactor, void (*freeFunc)(void*));

void iphashmap_free(struct iphashmap_t* self);

unsigned char iphashmap_get(struct iphashmap_t* self, unsigned int key, void** value);

unsigned char iphashmap_set(struct iphashmap_t* self, unsigned int key, void* value);

unsigned char iphashmap_del(struct iphashmap_t* self, unsigned int key);

#endif
