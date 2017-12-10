/*
 * main.c
 *
 * This file is purely for testing at the moment.
 *
 *  Created on: Dec 10, 2017
 *      Author: Carlos R. Davila
 */
#include "rx.h"

// TODO: Remove this, just for testing
char * payload = "Hey_CMPE_245_SJSU_9067";

void main() {
	printf("\n*** INIT HEADER ***\n");
	init_header(payload);
	printf("Payload - %s\n", payload);
	char * interleaved_payload = prep_msg(payload, header_str);
	printf("Interleaved payload - %s", interleaved_payload);

	printf("\n\n*** INIT ERROR TESTS ***\n");
	float error = check_watermark('W');
	printf("Returned error: %f\n\n", error);
	error = check_watermark('X');
	printf("Returned error: %f\n\n", error);
	error = check_watermark('Y');
	printf("Returned error: %f\n\n", error);
	error = check_watermark('Z');
	printf("Returned error: %f\n\n", error);
	error = check_watermark('Y');
	printf("Returned error: %f\n\n", error);
	error = check_watermark('Z');
	printf("Returned error: %f\n\n", error);
	error = check_watermark('X');
	printf("Returned error: %f\n\n", error);
	printf("Done!");
}
