
#include <linux/kernel.h>
#include <stdlib.h> 
#include <stdio.h>

void array_to_string(int *array, size_t size, char *str);
void string_to_array(const char *input, int *output, int max_size);