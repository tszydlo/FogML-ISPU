/**
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#include "peripherals.h"
#include "reg_map.h"

#include "fogml_config.h"

#include <stdint.h>
#include <stdbool.h>

#define ACC_SENS 0.000244f

//#define FogML_LOGGER

float tseries[ACC_TIME_TICKS*ACC_AXIS];
float features[FOGML_VECTOR_SIZE];
int tseries_index;
uint16_t iteration;

void __attribute__ ((signal)) algo_00_init(void);
void __attribute__ ((signal)) algo_00(void);

static volatile uint32_t int_status;

void __attribute__ ((signal)) algo_00_init(void)
{
	tseries_index = 0;
	iteration = 0;
}

void __attribute__ ((signal)) algo_00(void)
{
	tseries[tseries_index + 0] = (float)cast_sint16_t(ISPU_ARAW_X) * ACC_SENS;
	tseries[tseries_index + 1] = (float)cast_sint16_t(ISPU_ARAW_Y) * ACC_SENS;
	tseries[tseries_index + 2] = (float)cast_sint16_t(ISPU_ARAW_Z) * ACC_SENS;

	tseries_index += 3;
	if (tseries_index >= ACC_TIME_TICKS*ACC_AXIS) {
		fogml_features_logger(tseries, features);
		tseries_index = 0;

		cast_float(ISPU_DOUT_00) = features[0];
		cast_float(ISPU_DOUT_02) = features[1];
		cast_float(ISPU_DOUT_04) = features[2];
		cast_float(ISPU_DOUT_06) = features[3];
		cast_float(ISPU_DOUT_08) = features[4];
		cast_float(ISPU_DOUT_10) = features[5];
		cast_float(ISPU_DOUT_12) = features[6];
		cast_float(ISPU_DOUT_14) = features[7];
		cast_float(ISPU_DOUT_16) = features[8];
		cast_float(ISPU_DOUT_18) = features[9];
		cast_float(ISPU_DOUT_20) = features[10];
		cast_float(ISPU_DOUT_22) = features[11];

		cast_uint16_t(ISPU_DOUT_24) = iteration;

#ifndef FogML_LOGGER
		cast_uint16_t(ISPU_DOUT_25) = fogml_classification(features);
#endif

		iteration++;
		// interrupt generation (set bit 0 for algo 0, bit 1 for algo 1, etc.)
		int_status = int_status | 0x1u;
	}
}

// For more algorithms implement the corresponding functions: algo_01_init and
// algo_01 for algo 1, algo_02_init and algo_02 for algo 2, etc.

int main(void)
{
	// set boot done flag
	uint8_t status = cast_uint8_t(ISPU_STATUS);
	status = status | 0x04u;
	cast_uint8_t(ISPU_STATUS) = status;

	// enable algorithms interrupt request generation
	cast_uint8_t(ISPU_GLB_CALL_EN) = 0x01u;

	while (true) {
		stop_and_wait_start_pulse;

		// reset status registers and interrupts
		int_status = 0u;
		cast_uint32_t(ISPU_INT_STATUS) = 0u;
		cast_uint8_t(ISPU_INT_PIN) = 0u;

		// get all the algorithms to run in this time slot
		cast_uint32_t(ISPU_CALL_EN) = cast_uint32_t(ISPU_ALGO) << 1;

		// wait for all algorithms execution
		while (cast_uint32_t(ISPU_CALL_EN) != 0u) {
		}

		// get interrupt flags
		uint8_t int_pin = 0u;
		int_pin |= ((int_status & cast_uint32_t(ISPU_INT1_CTRL)) > 0u) ? 0x01u : 0x00u;
		int_pin |= ((int_status & cast_uint32_t(ISPU_INT2_CTRL)) > 0u) ? 0x02u : 0x00u;

		// set status registers and generate interrupts
		cast_uint32_t(ISPU_INT_STATUS) = int_status;
		cast_uint8_t(ISPU_INT_PIN) = int_pin;
	}
}

