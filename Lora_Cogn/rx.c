/*
 * rx.c
 *
 *  Created on: Dec 9, 2017
 *      Author: Carlos R. Davila
 */
#include "rx.h"

/**
 * Counts how many bits of 1 there are in a given array of characters.
 */
int count_err_bits(unsigned char * input, int input_len) {
	unsigned char curr_byte;
	int num_errors = 0;

	for (int i = 0; i < input_len; i++) {
		curr_byte = input[i];
		for (int j = 0; j < 8; j++) {
			if(((curr_byte >> (7 - j)) & 1) == 1) num_errors++;
		}
	}
	return num_errors;
}

/**
 * Checks the watermark with the next character 'c' provided. This function
 * internally keeps track of how many characters it has checked. If it has already
 * checked all the header bits, it begins from header character at 0 again.
 */

float check_watermark(unsigned char c) {
	static int num_errors = 0;
	static int header_idx = 0;
	unsigned char char_diff = 0;

	printf("Checking char[%c] against [%c].\n", c, header_str[header_idx]);
	if(c != header_str[header_idx]) {
		//compare characters with XOR
		printf("ERROR! %c[%d] != %c[%d]\n", c, (int) c,
				header_str[header_idx], (int) header_str[header_idx]);

		char_diff = (unsigned char) (c ^ header_str[header_idx]);
		num_errors += count_err_bits(&char_diff, 1);
	}
	header_idx++;
	if(header_idx == header_len - 1) {
		header_idx = 0;  //Reset idx to keep checking messages
	}

	float result = num_errors / (8.0f * strlen(header_str));
	printf("Result of watermark is: %f\n", result);
	return result;
}
