#include <stdio.h>


//this function compare two word(dst, src). when dst > src, return 1 and when dst == src, return 0,  and when dst < src, return 1. by using pointer
int strncmp_p(char *dst, char *src, int n) {
    int cmp =0;
	int counter = 0;
    while(counter < n&& *dst && *src) {
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
		counter++;
    }
    if (!cmp && !(counter == n) ) {
        if (*dst)
            cmp = 1;
        else if (*src)
            cmp = -1;
    }
    return cmp;
}

//this function compare two word(dst, src). when dst > src, return 1 and when dst == src, return 0,  and when dst < src, return 1. by using array
int strncmp_a(char dst[], char src[], int n) {
    int cmp = 0;
    int i;
    for (i=0; i < n && dst[i] && src[i] ; i++) {
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
    if (!cmp && !(i == n)) {
        if (dst[i])
            cmp = 1;
        else if (src[i])
            cmp = -1;
    }
    return cmp;
}

void main() {
	int len1, len2;
	char *str1 = "hello";
	char *str2 = "hello, world";
	
	printf("%d\n", strncmp_a(str1, str2, 5));
	printf("%d\n", strncmp_p(str1, str2, 6));

}
