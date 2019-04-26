/* distance-us-v2-bricklet
 * Copyright (C) 2019 Olaf Lüke <olaf@tinkerforge.com>
 *
 * maxbotix.c: Driver for MaxBotix Distance US sensor
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "maxbotix.h"

#include "configs/config_maxbotix.h"
#include "bricklib2/hal/system_timer/system_timer.h"
#include "bricklib2/utility/util_definitions.h"
#include "bricklib2/hal/ccu4_pwm/ccu4_pwm.h"

#include "xmc_uart.h"
#include "xmc_gpio.h"

#include "communication.h"


#define maxbotix_rx_irq_handler  IRQ_Hdlr_11

Maxbotix maxbotix;

void maxbotix_parse(const char data) {
	switch(maxbotix.state) {
		case 0: {
			maxbotix.value = 0;

			if(data == 'R') {
				if(maxbotix.update_rate == MAXBOTIX_UPDATE_RATE_10HZ) {
					XMC_GPIO_SetOutputLow(MAXBOTIX_ENABLE_PIN);
				}
				maxbotix.state = 1;
			}

			break;
		}

		case 1: {
			if(data >= '0' && data <= '9') {
				maxbotix.value = maxbotix.value*10 + (data - '0');
			} else {
				if(data == '\r') {
					maxbotix.distance = maxbotix.value;

					if(maxbotix.update_rate == MAXBOTIX_UPDATE_RATE_10HZ) {
						maxbotix.hz10_active = true;
						maxbotix.hz10_time = system_timer_get_ms();
					}
				}
				maxbotix.state = 0;
			}

			break;
		}
	}
}

void __attribute__((optimize("-O3"))) __attribute__ ((section (".ram_code"))) maxbotix_rx_irq_handler(void) {
	while(!XMC_USIC_CH_RXFIFO_IsEmpty(MAXBOTIX_USIC)) {
		const char data = (char)MAXBOTIX_USIC->OUTR;
		maxbotix_parse(data);
	}
}


void maxbotix_tick(void) {
	if(maxbotix.hz10_active) {
		if(system_timer_is_time_elapsed_ms(maxbotix.hz10_time, 2)) {
			maxbotix.hz10_active = false;
			if(maxbotix.enable) {
				XMC_GPIO_SetOutputHigh(MAXBOTIX_ENABLE_PIN);
			}
		}
	}

	if(maxbotix.led.config == DISTANCE_US_V2_DISTANCE_LED_CONFIG_SHOW_DISTANCE) {
		ccu4_pwm_set_duty_cycle(MAXBOTIX_LED_CCU4_SLICE, 1000 - BETWEEN(0, maxbotix.distance-300, 1000));
	} else {
		led_flicker_tick(&maxbotix.led, system_timer_get_ms(), MAXBOTIX_LED_PIN);
	}
	// TODO: Distance LED
}

void maxbotix_init_uart(void) {
	// RX pin configuration
	const XMC_GPIO_CONFIG_t rx_pin_config = {
		.mode             = XMC_GPIO_MODE_INPUT_PULL_UP,
		.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
	};

	// Configure  pins
	XMC_GPIO_Init(MAXBOTIX_RX_PIN, &rx_pin_config);

	// Initialize USIC channel in UART master mode
	// USIC channel configuration
	XMC_UART_CH_CONFIG_t config;
	config.oversampling = 16;
	config.frame_length = 8;
	config.baudrate     = 9600;
	config.stop_bits    = 1;
	config.data_bits    = 8;
	config.parity_mode  = XMC_USIC_CH_PARITY_MODE_NONE;
	XMC_UART_CH_Init(MAXBOTIX_USIC, &config);

	// Set input source path
	XMC_UART_CH_SetInputSource(MAXBOTIX_USIC, MAXBOTIX_RX_INPUT, MAXBOTIX_RX_SOURCE);
	XMC_USIC_CH_EnableInputInversion(MAXBOTIX_USIC, XMC_USIC_CH_INPUT_DX0);

	// Configure receive FIFO
	XMC_USIC_CH_RXFIFO_Configure(MAXBOTIX_USIC, 32, XMC_USIC_CH_FIFO_SIZE_32WORDS, 0);

	// Set service request for rx FIFO receive interrupt
	XMC_USIC_CH_RXFIFO_SetInterruptNodePointer(MAXBOTIX_USIC, XMC_USIC_CH_RXFIFO_INTERRUPT_NODE_POINTER_STANDARD, MAXBOTIX_SERVICE_REQUEST_RX);
	XMC_USIC_CH_RXFIFO_SetInterruptNodePointer(MAXBOTIX_USIC, XMC_USIC_CH_RXFIFO_INTERRUPT_NODE_POINTER_ALTERNATE, MAXBOTIX_SERVICE_REQUEST_RX);

	// Set priority and enable NVIC node for receive interrupt
	NVIC_SetPriority((IRQn_Type)MAXBOTIX_IRQ_RX, MAXBOTIX_IRQ_RX_PRIORITY);
	NVIC_EnableIRQ((IRQn_Type)MAXBOTIX_IRQ_RX);

	// Start UART
	XMC_UART_CH_Start(MAXBOTIX_USIC);

	XMC_USIC_CH_EnableEvent(MAXBOTIX_USIC, XMC_USIC_CH_EVENT_ALTERNATIVE_RECEIVE);
	XMC_USIC_CH_RXFIFO_EnableEvent(MAXBOTIX_USIC, XMC_USIC_CH_RXFIFO_EVENT_CONF_STANDARD | XMC_USIC_CH_RXFIFO_EVENT_CONF_ALTERNATE);
}

void maxbotix_init(void) {
	memset(&maxbotix, 0, sizeof(Maxbotix));

	maxbotix.led.config = DISTANCE_US_V2_DISTANCE_LED_CONFIG_SHOW_DISTANCE;
	maxbotix.enable = true;
	XMC_GPIO_CONFIG_t pin_config = {
		.mode             = XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
		.output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH
	};

	XMC_GPIO_Init(MAXBOTIX_ENABLE_PIN, &pin_config);
	ccu4_pwm_init(MAXBOTIX_LED_PIN, MAXBOTIX_LED_CCU4_SLICE, 1000);
	maxbotix_init_uart();
}

uint16_t maxbotix_get_distance(void) {
	return maxbotix.distance;
}