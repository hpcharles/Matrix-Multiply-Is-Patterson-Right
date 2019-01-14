#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>






typedef unsigned long long ticks;




					long long	start	();
					long long 	stop	(long long timeusec);
//static __inline__	ticks		getticks(void);
ticks		getticks(void);
