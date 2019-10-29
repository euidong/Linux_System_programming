#include <stdio.h>


//this function return a length of string by using pointer.
int strlen_p(char* str) {
	int len = 0;
	while (str[len] != '\0')
		len++;
	return len;
}

//this function return a length of string by using array.
int strlen_a(char str[]) {
	int i;

	for (i = 0 ; str[i] != '\0'; i++)
		;
	return i;
}

//this function copy src to dst by using pointer.
void strcpy_p(char* dst, char *src) {
	while (*src) {
		*dst++ = *src++;
	}
	*dst = *src;
}

//this function copy src to dst by using array.
void strcpy_a(char dst[], char src[]) {
	int i;

	for (i = 0 ; src[i] != '\0'; i++)
		dst[i] = src[i];

	dst[i] = src[i];
}

// this function add all src to dst by using pointer
void strcat_p(char *dst, char *src) {
	while(*dst++)
		;
	dst--;
	while(*src)
		*dst++ = *src++;
	*dst = '\0';	
}
// this function add all src to dst by using array
void strcat_a(char dst[], char src[]) {
	int i,j;

	for (i = 0 ; dst[i] != '\0'; i++)
		;
	for (j = 0 ; src[j] != '\0'; j++)
		dst[i+j] = src[j];
	dst[i+j] = '\0';
}

//this function compare two word(dst, src). when dst > src, return 1 and when dst == src, return 0,  and when dst < src, return 1. by using pointer
int strcmp_p(char *dst, char *src) {
	int cmp =0;
	while(*dst && *src) {
		if(*dst > *src) {
			cmp= 1;
			break;
		}
		else if(*dst < *src) {
			cmp = -1;
			break;
		}
		*dst++;
		*src++;
	}
	if (!cmp) {
		if (*dst)
			cmp = 1;
		else if (*src)
			cmp = -1;
	}
	return cmp;
}

//this function compare two word(dst, src). when dst > src, return 1 and when dst == src, return 0,  and when dst < src, return 1. by using array
int strcmp_a(char dst[], char src[]) {
	int cmp = 0;
	int i;
	for (i=0; dst[i] && src[i]; i++) {
		if(dst[i] > src[i])
		{
			cmp = 1;
			break;
		}
		else if (dst[i] < src[i])
		{	
			cmp = -1;
			break;
		}
	}
	if (!cmp) {
		if (dst[i])
			cmp = 1;
		else if (src[i])
			cmp = -1;
	}
	return cmp;
}

void main() {
	int len1, len2;
	char str1[20], str2[20];

	len1 = strlen_p("Hello");
	len2 = strlen_a("Hello");
	printf("strlen: p=%d, a=%d\n", len1, len2);

	strcpy_p(str1, "Hello");
	strcpy_a(str2, "Hello");
	printf("strcpy: p=%s, a=%s\n", str1, str2);

	strcat_p(str1, ", World");
	strcat_a(str2, ", World");
	printf("strcat: p=%s, a=%s\n", str1, str2);
	
	printf("strcmp: %d\n",strcmp_p(str1, str2));
	printf("strcmp: %d\n",strcmp_a("good", "gold"));
}

/*
This program will show all string function by two way.
first is array based implementation.
Second is point based implementation.
*/
