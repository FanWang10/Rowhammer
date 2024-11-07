#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <uchar.h>

// Size of the memory chunk in which we want to implement the attack
#define CHUNK_SIZE 0x10000000
// Word size
#define VAL_SIZE sizeof(unsigned long)
// Size of a page (2^12 is a standard size for a page)
#define PAGE_SIZE 4096

unsigned long chunk[CHUNK_SIZE/VAL_SIZE];	// Chunk of memory to hammer (considering word of 64 bits

void generate_va_table(int pgmp);

int main(int argc, char **argv) {
	// Pagemap file identifier
	int pgmp;
	char path[200];

	// Addresses on 64 bits
	unsigned long addr1, addr2;
	

	// Recover the pagemap file id for this process
	sprintf(path, "/proc/%u/pagemap", getpid());
	pgmp = open(path, O_RDONLY);
	if (pgmp == -1) {
		printf("Unable to open pagemap file\n");
		exit(-1);
	}

	// Memory pattern - all 1
	// Type of hammer - double-sided hammering
	// Mode - DC ZVA
	
	// Generate physical address to virtual address
	generate_va_table(pgmp);

	return 0;
}

// Function to generate physical to virtual address mapping
void generate_va_table(int pgmp){
	unsigned long data, index, pfn;
	
	// Handle one page every iteration
	for (int i = 0; i < CHUNK_SIZE / VAL_SIZE; i+= PAGE_SIZE / VAL_SIZE) {
		// index mean which page table entry address should be accessed to get info required for this iteration 
		index = (unsigend long)&chunk[i] / PAGE_SIZE * sizeof(data);
		
		// Read data in pagemap file, read the entries of e page, while will re
		if (pread(pgmp, $data, sizeof(data), index) != sizeof(data)) {
			perror("pread: failed to read a page");
			break;
		}

		// Store the virtual page number
		pfn = data & 0x7fffffffffffff

	}
}
