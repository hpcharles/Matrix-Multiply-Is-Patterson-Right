#define TYPEELT 1

#if TYPEELT == 1               /* FLT */
typedef float typeelt;
#elif TYPEELT == 2             /* INT */
typedef int typeelt;
#elif TYPEELT == 3             /* DBL */
typedef double typeelt;
#elif TYPEELT == 4             /* SHT */
typedef short typeelt;
#endif

typedef typeelt **tMatrix;

long long getTime();
void printMatrix(tMatrix a, int nLines, int nColumns);
void randMatrix(tMatrix a, int NLines, int NCols);
tMatrix createMatrix(int NLines, int NCols);
