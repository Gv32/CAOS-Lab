#include "shared.h"

void array_to_string(int *array, size_t size, char *str){
	size_t offset = 0;
	int bytes_written;
	for(int i=0; i < size; i++){
		bytes_written = sprintf(str + offset, "%d", array[i]);
		offset += bytes_written;
        if (i < size - 1) {
            *(str + offset) = ',';
        }
		else{
            *(str + offset) = '\0';
		}
		offset += 1;
	}
}

void string_to_array(const char *input, int *output, int max_size) {
    int i = 0;
	int num = 0;
	int count = 0;
    int is_negative = 0;
	int is_number = 1;
    while (input[i] != '\0' && count < max_size) {
        if (input[i] == ' ' || input[i] == ',') {
            i++;
			is_number = 0;
        }
		if(is_number){
			if (input[i] == '-') {
				is_negative = 1;
				i++;
			}
			while (input[i] >= '0' && input[i] <= '9') {
				num = num * 10 + (input[i] - '0');
				i++;
			}
			if (is_negative) {
				num = -num;
				is_negative = 0;
			}
			output[count++] = num;
			num = 0;
		}

		is_number = 1;

    }

}
