/*
 * rx_tx_common.h
 *
 *  Created on: Dec 10, 2017
 *      Author: Carlos R. Davila
 */

#ifndef RX_TX_COMMON_H_
#define RX_TX_COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Global Variables **/
char * header_str;						// Header used for communication, should be adjusted if payload changes length
extern int header_len;				// Length of the header being used
extern int * header_idxs;			// Location of where to interlace header chars in payload. Calculated at runtime in init_header()
struct RF_Settings {					// Contains all the variables to store RF register settings
	int crc;
	int spreading_factor[3];
	int signal_power[3];
	int bitrate[3];
	int scrambling[3];
	int frequency[3];
};

void init_header();
char * prep_msg(char * payload, char * header);

#endif /* RX_TX_COMMON_H_ */
