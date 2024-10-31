#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#define PAGE_SIZE 4096
#define WORD_SIZE sizeof(unsigned long)
#define HAMMER_SIZE 25000000

int main() {
	int mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
	int i = 3;
	for(i; i < 70000; i++){
		off_t phys_addr = PAGE_SIZE * i;
		void *map_base = mmap(NULL,
			PAGE_SIZE,
			PROT_READ | PROT_WRITE,
			MAP_SHARED,
			mem_fd,
			phys_addr);	// phys_addr should be page-aligned
	
		void *virt_addr = (char *)map_base + WORD_SIZE;
		uint64_t pa = (uint64_t) phys_addr + WORD_SIZE;
		uint64_t read_result = *(volatile uint64_t*)virt_addr;
		// Access adjacent row
		uint64_t result_up = *(volatile uint64_t*)virt_addr + WORD_SIZE; 
		printf("The physical address is: %x\n", phys_addr + WORD_SIZE);
		printf("Result read is: %x\n", read_result);

	
		void *virt_addr_below = virt_addr + WORD_SIZE;
		uint64_t pa_below = pa + WORD_SIZE;
		uint64_t read_result_below = *(volatile uint64_t*)virt_addr_below;
		//printf("The below physical address is: %x\n", phys_addr + 2 * WORD_SIZE);
		//printf("Result read is: %x\n", read_result_below);

		void *virt_addr_above = virt_addr - WORD_SIZE;
		uint64_t pa_above = pa - WORD_SIZE;
		uint64_t read_result_above = *(volatile uint64_t*)virt_addr_above;
		//printf("The above physical address is: %x\n", phys_addr);
		//printf("Result read is: %x\n", read_result_above);

		int cycle = 0;
		for (cycle; cycle < HAMMER_SIZE; cycle++) 
		{
			asm volatile("dc zva, %0\n\t"
				     "dc zva, %1\n\t"
				     ::"r"(virt_addr_above),"r"(virt_addr_below));
		}
		//printf("Hammer End\n");
		printf("After hammering the physical row %x has data %x\n", pa, *(volatile uint64_t*)virt_addr);
		uint64_t final_result = *(volatile uint64_t*)virt_addr;
		if(final_result != read_result) {
			printf("Rowhammer triggered\n");
		}
	}
	return 0;
}
