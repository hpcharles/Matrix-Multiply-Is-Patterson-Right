#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main (void)
{
	long l1_cache_line_size = sysconf(_SC_LEVEL1_DCACHE_LINESIZE);
	long l2_cache_line_size = sysconf(_SC_LEVEL2_CACHE_LINESIZE);
	long l3_cache_line_size = sysconf(_SC_LEVEL3_CACHE_LINESIZE);

	long l1_cache_size		= sysconf(_SC_LEVEL1_DCACHE_SIZE);
	long l2_cache_size		= sysconf(_SC_LEVEL2_CACHE_SIZE);
	long l3_cache_size		= sysconf(_SC_LEVEL3_CACHE_SIZE);

	printf("L1 Cache Line Size is %ld bytes.\n", l1_cache_line_size);
	printf("L2 Cache Line Size is %ld bytes.\n", l2_cache_line_size);
	printf("L3 Cache Line Size is %ld bytes.\n", l3_cache_line_size);

	printf("----------------------------------------------------\n");
	printf("L1 Cache Size is %ld bytes.\n", l1_cache_size);
	printf("L2 Cache Size is %ld bytes.\n", l2_cache_size);
	printf("L3 Cache Size is %ld bytes.\n", l3_cache_size);

	return (0);
}
