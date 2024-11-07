#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#define WORD_SIZE sizeof(unsigned long)
#define MEM_SIZE (920000 * 1000)

int main () {
	//printf(
	//	"Total Memory = 0x%lX\n",
	//	sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGESIZE)		
	//);	
	//printf(
	//	"Available Memory = 0x%lX\n",
	//	sysconf(_SC_AVPHYS_PAGES) * sysconf(_SC_PAGESIZE)		
	//);
	
	size_t sizemem = (size_t) sysconf(_SC_AVPHYS_PAGES) * sysconf(_SC_PAGESIZE);
	unsigned long * ptr;
	ptr = (unsigned long*)malloc(sizemem);
	int size = (int)sizemem/8;
  	printf("unsigned long size: %d\n", sizeof(unsigned long) );	
	if (ptr == NULL) 
	{
		printf("Memory not allocated.\n");
		exit(0);
	}

	for(int i = 0; i < size; i++)
	{
		ptr[i] = 0;
	}
	
	// Get the available RAM
	//printf(
	//	"Total Memory = 0x%lX\n",
	//	sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGESIZE)		
	//);	
	//printf(
	//	"Available Mmeor = 0x%lX\n",
	//	sysconf(_SC_AVPHYS_PAGES) * sysconf(_SC_PAGESIZE)		
	//);

	free(ptr);
}
