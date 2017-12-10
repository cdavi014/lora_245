/*
 * rx.h
 *
 *  Created on: Dec 10, 2017
 *      Author: Carlos R. Davila
 */

#ifndef RX_H_
#define RX_H_

#include "rx_tx_common.h"

int count_err_bits(unsigned char * input, int input_len);
float check_watermark(unsigned char c);

#endif /* RX_H_ */
