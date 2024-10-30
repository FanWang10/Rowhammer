#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#define PAGE_SIZE 4096
#define WORD_SIZE sizeof(unsigned long)

int main() {
	int mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
	off_t phys_addr = PAGE_SIZE * 200000;
	void *map_base = mmap(NULL,
			PAGE_SIZE,
			PROT_READ | PROT_WRITE,
			MAP_SHARED,
			mem_fd,
			phys_addr);	// phys_addr should be page-aligned
	
	void *virt_addr = (char *)map_base;

	uint64_t read_result = *(volatile uint64_t*)virt_addr;

	// Access adjacent row
	// uint64_t result_up = *(volatile uint64_t*)virt_addr + WORD_SIZE; 
	printf("The physical address is: %x\n", phys_addr);
	printf("Result read is: %x\n", read_result);


	void *virt_addr_below = virt_addr + WORD_SIZE;
	uint64_t read_result_below = *(volatile uint64_t*)virt_addr_below;
	printf("The lower physical address is: %x\n", phys_addr + WORD_SIZE);
	printf("Result read is: %x\n", read_result_below);

	return 0;
}
