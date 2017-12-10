/*
 * rx_tx_common.c
 *
 *  Created on: Dec 10, 2017
 *      Author: Carlos R. Davila
 */

#include "rx_tx_common.h"
#include "math.h"

char * header_str = "WXYZ";
int * header_idxs;
int header_len;

/**
 * Initialize the header and header related values. This will allocate an array
 * with the locations where the interleaved header characters should go for the
 * given 'payload'.
 */
void init_header(char * payload) {
	//calculate header idx locations with respect to header length and payload length
	int payload_len = strlen(payload);
	printf("Payload Length: %d\n", (int)strlen(payload));
	header_len = strlen(header_str);
	header_idxs = malloc(sizeof(int) * header_len);
	float header_pct = header_len / (float) payload_len;

	// Check if header to payload pct is between 15% and 20%
	if(header_pct < .15 || header_pct > .2) {
		printf("[ERROR] [rx_tx_common] - Header percentage of payload needs to "
				"be between 15%% and 20%% but is at %f%%, please fix header (in rx_tx_common.c) and run again",
				header_pct * 100);
		exit(-1);
	}

	float dist = floor(payload_len / header_len);
	for (int i = 0; i < header_len; i++) {
		header_idxs[i] = (int) (dist * (i + 1));
		printf("header_idx[%d] = %d\n", i, header_idxs[i]);
	}
}

/**
 * Interleaves a payload with the given header and returns the interleaved msg.
 * TODO: Remove all of the debig comments.
 */
char * prep_msg(char * payload, char * header) {
	int payload_len = strlen(payload);
	int header_len = strlen(header);
	int rslt_len = payload_len + header_len;
	char * payload_sbstr;
	char * rslt = (char*) malloc((rslt_len + 1) * sizeof(char));
	int curr_idx, prev_idx, sbstr_size;

	if (header_len >= payload_len) {
		printf("[ERROR] [rx_tx_common] - Header length [%d] needs to "
				"be greater than payload length [%d]", header_len, payload_len);
		return NULL;
	}

	for (int i = 0; i <= header_len; i++) {
		prev_idx = header_idxs[i - 1];

		if (i == header_len) { 	// Done, just append rest of payload
			sbstr_size = payload_len + header_len - prev_idx;
			payload_sbstr = (char *) calloc(sbstr_size, sizeof(char));
			memcpy(payload_sbstr, &payload[prev_idx - header_len + 1], sbstr_size);// Extract part of payload
		} else {
			curr_idx = header_idxs[i];	// Where to place the watermark char i
			printf("Curr idx = %d\n", curr_idx);

			if (i == 0) {
				sbstr_size = curr_idx;
			} else {
				sbstr_size = curr_idx - prev_idx - 1;
			}

			payload_sbstr = (char *) calloc(sbstr_size + 1, sizeof(char));
			memcpy(payload_sbstr, &payload[(prev_idx -i + 1) * (i > 0)], sbstr_size);
			payload_sbstr[sbstr_size] = header_str[i];	 // Extract part of payload
			printf("i = %d [%c]\n", i, header_str[i]);
			printf("Sbstr idx = %d\n", (prev_idx + 1) * (i > 0));
		}	 // end else
		printf("payload_sbstr: %s\n", payload_sbstr);
		strcat(rslt, payload_sbstr);
		printf("result so far: %s\n", rslt);
		free(payload_sbstr);
	} // end for
	return rslt;
}
