#include <sys/types.h>

word
strlen(byte *str) {
	byte *p = str;

	while (*p)
		(void)*p++;

	return p - str;
}

word
strnlen(byte *str, word n) {
	byte *p = str;

	while (*p && p - str < n)
		(void)*p++;

	return p - str;
}


