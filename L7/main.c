#include "cache.h"
#include <stdio.h>
#include <time.h>

#define MAX_SIZE 1024

typedef long array_t[MAX_SIZE * MAX_SIZE];
static simcache_t *cache;

/* Array used for testing. The aligned attribute is used to ensure
 * that test_array[0] is stored at the start of a cache block, for any
 * block size up to 1024.
 */
array_t __attribute__ ((aligned (1024))) test_array;

/*
 * Write data to the array, bypassing the "cache".
 */
void fillArray(array_t a) {
  
    int i, j;
  
    for (i = 0; i < MAX_SIZE; i++)
	for (j = 0; j < MAX_SIZE; j++)
	    a[i * MAX_SIZE + j] = (i + 1) * (j + 1);
}

long sumA(array_t a, int rows, int cols) {
  
    int i, j;
    long sum = 0;

    for (i = 0; i < rows; i++)
	for (j = 0; j < cols; j++)
	    sum += cache_read(cache, (uintptr_t) &a[i * cols + j], rand);
  
    return sum;
}

long sumB(array_t a, int rows, int cols) {
  
    int i, j;
    long sum = 0;

    for (j = 0; j < cols; j++)
	for (i = 0; i < rows; i++)
	    sum += cache_read(cache, (uintptr_t) &a[i * cols + j], rand);
  
    return sum;
}

long sumC(array_t a, int rows, int cols) {
  
    int i, j;
    int sum = 0;
  
    for (j = 0; j < cols; j += 2)
	for (i = 0; i < rows; i += 2)
	    sum += cache_read(cache, (uintptr_t) &a[i * cols + j], rand) +
		cache_read(cache, (uintptr_t) &a[(i+1) * cols + j], rand) +
		cache_read(cache, (uintptr_t) &a[i * cols + j+1], rand) +
		cache_read(cache, (uintptr_t) &a[(i+1) * cols + j+1], rand);
  
    return sum;
}

int64_t sumD(array_t a, size_t rows, size_t cols, size_t count) {

    size_t i, j, k;
    int64_t sum = 0;

    for (k = 0; k < count; k++)
        for (i = 0; i < rows; i++)
            for (j = 0; j < cols; j += 8)
                sum += cache_read(cache, (uintptr_t) &a[i * cols + j + k], rand);

    return sum;
}

int64_t sumE(array_t a, size_t rows, size_t cols) {
    int64_t sum = 0;

    sum += cache_read(cache, (uintptr_t) &a[0], rand);
    sum += cache_read(cache, (uintptr_t) &a[0], rand);
    sum += cache_read(cache, (uintptr_t) &a[0], rand);
    sum += cache_read(cache, (uintptr_t) &a[0], rand);
    sum += cache_read(cache, (uintptr_t) &a[4 * cols], rand);
    sum += cache_read(cache, (uintptr_t) &a[8 * cols], rand);
    sum += cache_read(cache, (uintptr_t) &a[4 * cols], rand);
    sum += cache_read(cache, (uintptr_t) &a[8 * cols], rand);
    sum += cache_read(cache, (uintptr_t) &a[4 * cols], rand);
    return sum;
}
void print_stats() {
  
    int mc = cache_miss_count(cache);
    int ac = cache_access_count(cache);
  
    if (ac == 0) {
	printf("The cache wasn't used.\n");
    }
    else {
	printf("Miss rate = %8.4f\n", (double) mc/ac);
    }
}

int main() {

    srand(time(NULL));
    fillArray(test_array);

    cache = cache_new(16384, 4, 64, CACHE_REPLACEMENTPOLICY_LFU);
    printf("Sum10 = %ld\n", sumA(test_array, 64, 64));
    print_stats();
    cache_free(cache);

    cache = cache_new(4096, 2, 16, CACHE_REPLACEMENTPOLICY_LFU);
    printf("Sum11 = %ld\n", sumE(test_array, 256, 64));
    print_stats();
    cache_free(cache);
    
    cache = cache_new(4096, 2, 16, CACHE_REPLACEMENTPOLICY_LFU);
    printf("Sum12 = %ld\n", sumE(test_array, 1024, 64));
    print_stats();
    cache_free(cache);
    cache = cache_new(16384, 1, 64, CACHE_REPLACEMENTPOLICY_LFU);
    printf("Sum1 = %ld\n", sumA(test_array, 64, 64));
    print_stats();
    cache_free(cache);
  
    cache = cache_new(16384, 1, 64, CACHE_REPLACEMENTPOLICY_LFU);
    printf("Sum2 = %ld\n", sumB(test_array, 64, 64));
    print_stats();
    cache_free(cache);
  
    cache = cache_new(16384, 1, 64, CACHE_REPLACEMENTPOLICY_LFU);
    printf("Sum3 = %ld\n", sumC(test_array, 64, 64));
    print_stats();
    cache_free(cache);

    cache = cache_new(16384, 4, 64, CACHE_REPLACEMENTPOLICY_LFU);
    printf("Sum4 = %ld\n", sumA(test_array, 64, 64));
    print_stats();
    cache_free(cache);
  
    cache = cache_new(16384, 4, 64, CACHE_REPLACEMENTPOLICY_LFU);
    printf("Sum5 = %ld\n", sumB(test_array, 64, 64));
    print_stats();
    cache_free(cache);
  
    cache = cache_new(16384, 4, 64, CACHE_REPLACEMENTPOLICY_LFU);
    printf("Sum6 = %ld\n", sumC(test_array, 64, 64));
    print_stats();
    cache_free(cache);

    cache = cache_new(16384, 8, 64, CACHE_REPLACEMENTPOLICY_RANDOMIZED_MARKING);
    printf("Sum7 = %ld\n", sumD(test_array, 12, 256, 5));
    print_stats();
    cache_free(cache);

    cache = cache_new(16384, 8, 64, CACHE_REPLACEMENTPOLICY_RANDOMIZED_MARKING);
    printf("Sum8 = %ld\n", sumD(test_array, 12, 256, 5));
    print_stats();
    cache_free(cache);

    cache = cache_new(16384, 8, 64, CACHE_REPLACEMENTPOLICY_RANDOMIZED_MARKING);
    printf("Sum9 = %ld\n", sumD(test_array, 12, 256, 5));
    print_stats();
    cache_free(cache);

    return 0;
}
