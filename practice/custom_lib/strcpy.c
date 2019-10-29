void mystrcpy(char* dst, char* src)
{
	while(*src) {
		*dst++ = *src++;
	}
	*dst = *src;
}
