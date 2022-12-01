#include <stdint.h>
#include <stdio.h>

int main()
{
	uint32_t total_no_exits;
	uint32_t total_time_low;
	uint32_t total_time_high;
	uint64_t total_time;

	__asm__("mov $0x4ffffffc, %eax\n\t");
	__asm__("cpuid\n\t");
	__asm__("mov %%eax, %0;" : "=r" (total_no_exits));
	printf("CPUID 0x4ffffffc, Total number of exits = %d\n", total_no_exits);
	
	__asm__("mov $0x4ffffffd, %eax\n\t");
	__asm__("cpuid\n\t");
	__asm__("mov %%ebx, %0;" : "=r" (total_time_high));
	__asm__("mov %%ecx, %0;" : "=r" (total_time_low));
	total_time = total_time_high;
	total_time = total_time << 32;
	total_time |= total_time_low;
	printf("CPUID 0x4ffffffd, Total time spent processing all exits = %ld\n", total_time); 
	
	return 0;
}
