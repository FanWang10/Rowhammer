#include <stdlib.h>
#include <stdio.h>
#define WORD_SIZE sizeof(unsigned long)
#define MEM_SIZE (920000 * 1000)

int main () {
	unsigned long * ptr;
	ptr = (unsigned long*)malloc(MEM_SIZE);
	if (ptr == NULL) 
	{
		printf("Memory not allocated.\n");
		exit(0);
	}	
}
