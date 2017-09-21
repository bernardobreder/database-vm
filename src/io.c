#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "io.h"

void b_int_write(unsigned char* bytes, unsigned int value) {
	*bytes++ = (value >> 24) & 0xFF;
	*bytes++ = (value >> 18) & 0xFF;
	*bytes++ = (value >> 8) & 0xFF;
	*bytes++ = (value) & 0xFF;
}

unsigned int b_int_read(unsigned char* bytes) {
	return ((*bytes++) << 24) + ((*bytes++) << 16) + ((*bytes++) << 8) + (*bytes++);
}

void b_long_write(unsigned char* bytes, unsigned long value) {
	*bytes++ = (value >> 56) & 0xFF;
	*bytes++ = (value >> 48) & 0xFF;
	*bytes++ = (value >> 40) & 0xFF;
	*bytes++ = (value >> 32) & 0xFF;
	*bytes++ = (value >> 24) & 0xFF;
	*bytes++ = (value >> 18) & 0xFF;
	*bytes++ = (value >> 8) & 0xFF;
	*bytes++ = (value) & 0xFF;
}

unsigned long b_long_read(unsigned char* bytes) {
	return ((long) (*bytes++) << 56) + ((long) (*bytes++) << 48) + ((long) (*bytes++) << 40) + ((long) (*bytes++) << 32) + ((*bytes++) << 24) + ((*bytes++) << 16) + ((*bytes++) << 8) + (*bytes++);
}

void b_double_write(unsigned char* bytes, double v) {
	int ebits = 11, fbits = 52;
	int bias = (1 << (ebits - 1)) - 1;
	unsigned char s;
	double f;
	int e;
	if (isnan(v)) {
		e = (1 << bias) - 1;
		f = 1;
		s = 0;
	} else if (isinf(v)) {
		e = (1 << bias) - 1;
		f = 0;
		s = (v < 0) ? 1 : 0;
	} else if (v == 0) {
		e = 0;
		f = 0;
		s = (isinf(1 / v) == -1) ? 1 : 0;
	} else {
		s = v < 0;
		v = v < 0 ? -v : v;
		if (v >= pow(2, 1 - bias)) {
			double ln2 = 0.6931471805599453;
			double aux = floor(log(v) / ln2);
			double ln = aux > bias ? bias : aux;
			e = (int) (ln + bias);
			f = v * pow(2, fbits - ln) - pow(2, fbits);
		} else {
			e = 0;
			f = v / pow(2, 1 - bias - fbits);
		}
	}
	unsigned char bits[64];
	int i, n, m, index = 0;
	for (i = 0; i < fbits; i++) {
		bits[index++] = ((int) f) % 2 == 1 ? 1 : 0;
		f = floor(f / 2);
	}
	for (i = 0; i < ebits; i++) {
		bits[index++] = e % 2 == 1 ? 1 : 0;
		e = (int) floor(e / 2);
	}
	bits[index] = s;
	for (n = 0; n < 8; n++) {
		int value = 0;
		for (m = 0; m < 8; m++) {
			if (bits[n * 8 + m]) {
				value += pow(2, m);
			}
		}
		*bytes++ = (unsigned char) (value & 0xff);
	}
}

double b_double_read(unsigned char* bytes) {
	int ebits = 11, fbits = 52;
	unsigned char bits[64];
	int n, i, j, index = 0;
	for (i = 0; i < 8; i++) {
		unsigned char b = *bytes++;
		for (j = 0; j < 8; j++) {
			bits[index++] = b % 2 == 1 ? 1 : 0;
			b = b >> 1;
		}
	}
	int bias = (1 << (ebits - 1)) - 1;
	int s = bits[63] ? -1 : 1;
	int e = 0;
	for (n = 62; n >= 64 - ebits - 1; n--) {
		if (bits[n]) {
			e += pow(2, ebits - 1 - 62 + n);
		}
	}
	long f = 0;
	int imax = 64 - ebits - 2;
	for (n = imax; n >= 0; n--) {
		if (bits[n]) {
			f += pow(2, n);
		}
	}
	if (e == (1 << ebits) - 1) {
		return f != 0 ? NAN : s * 1. / 0.;
	} else if (e > 0) {
		return s * pow(2, e - bias) * (1 + f / pow(2, fbits));
	} else if (f != 0) {
		return s * pow(2, -(bias - 1)) * (f / pow(2, fbits));
	} else {
		return s * 0;
	}
}

int b_string_to_int(char *s) {
	int sign = (*s == '+' || *s == '-') ? ((*s++ == '+') ? 1 : -1) : 1;
	int n;
	for (n = 0; *s; s++) {
		n = (n * 10) + (*s - '0');
	}
	return sign * n;
}

char *b_uint_to_string(unsigned int value, char *digits, int base) {
	char *s, *p;
	s = "0123456789abcdefghijklmnopqrstuvwxyz";
	if (base == 0)
		base = 10;
	if (digits == NULL || base < 2 || base > 36)
		return NULL;
	if (value < (unsigned int) base) {
		digits[0] = s[value];
		digits[1] = '\0';
	} else {
		for (p = b_uint_to_string(value / ((unsigned int) base), digits, base); *p; p++)
			;
		b_uint_to_string(value % ((unsigned int) base), p, base);
	}
	return digits;
}

char *b_int_to_string(int value, char *digits, int base) {
	char *d;
	unsigned int u;
	d = digits;
	if (base == 0)
		base = 10;
	if (digits == NULL || base < 2 || base > 36)
		return NULL;
	if (value < 0) {
		*d++ = '-';
		u = -((unsigned) value);
	} else
		u = value;
	b_uint_to_string(u, d, base);
	return digits;
}

//static void swap(char *a, char *b, size_t n) {
//	while (n--) {
//		*a ^= *b;
//		*b ^= *a;
//		*a ^= *b;
//		a++;
//		b++;
//	}
//}
//
//void my_memrev(char *s, size_t n) {
//	switch (n) {
//	case 0:
//	case 1:
//		break;
//	case 2:
//	case 3:
//		swap(s, s + n - 1, 1);
//		break;
//	default:
//		my_memrev(s, n / 2);
//		my_memrev(s + ((n + 1) / 2), n / 2);
//		swap(s, s + ((n + 1) / 2), n / 2);
//		break;
//	}
//}
//
//void reverse(char *s) {
//	char *p;
//	for (p = s; *p; p++)
//		;
//	my_memrev(s, (size_t) (p - s));
//}
//
//static char *strchr(char *s, int c) {
//	char ch = c;
//
//	for (; *s != ch; ++s)
//		if (*s == '\0')
//			return NULL;
//	return s;
//}
//
//int strindex(char *s, char *t) {
//	char *u, *v, *w;
//
//	if (*t == '\0')
//		return 0;
//	for (u = s; (u = strchr(u, *t)) != NULL; ++u) {
//		for (v = u, w = t;;)
//			if (*++w == '\0')
//				return (int) (u - s);
//			else if (*++v != *w)
//				break;
//	}
//	return -1;
//}
//
//#define NUMBER '0'      /* from Chapter 4 */
//
//int getop(char *s) {
//	int c;
//	while ((*s = c = getch()) == ' ' || c == '\t')
//		;
//	*(s + 1) = '\0';
//	if (!isdigit(c) && c != '.')
//		return c; /* not a number */
//	if (isdigit(c)) /* collect integer part */
//		while (isdigit(*++s = c = getch()))
//			;
//	if (c == '.') /* collect fraction part */
//		while (isdigit(*++s = c = getch()))
//			;
//	*++s = '\0';
//	if (c != EOF)
//		ungetch(c);
//	return NUMBER;
//}
