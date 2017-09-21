#ifndef BREDER_IO_H
#define BREDER_IO_H

void b_int_write(unsigned char* bytes, unsigned int value);

unsigned int b_int_read(unsigned char* bytes);

void b_long_write(unsigned char* bytes, unsigned long value);

unsigned long b_long_read(unsigned char* bytes);

void b_double_write(unsigned char* bytes, double v);

double b_double_read(unsigned char* bytes);

int b_string_to_int(char *s);

char *b_uint_to_string(unsigned int value, char *digits, int base);

char *b_int_to_string(int value, char *digits, int base);

#endif
