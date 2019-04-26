/* distance-us-v2-bricklet
 * Copyright (C) 2019 Olaf Lüke <olaf@tinkerforge.com>
 *
 * communication.c: TFP protocol message handling
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

#include "communication.h"

#include "bricklib2/utility/communication_callback.h"
#include "bricklib2/protocols/tfp/tfp.h"
#include "bricklib2/utility/callback_value.h"

#include "maxbotix.h"
#include "configs/config_maxbotix.h"

CallbackValue_uint16_t callback_value_distance;


BootloaderHandleMessageResponse handle_message(const void *message, void *response) {
	switch(tfp_get_fid_from_message(message)) {
		case FID_GET_DISTANCE: return get_callback_value_uint16_t(message, response, &callback_value_distance);
		case FID_SET_DISTANCE_CALLBACK_CONFIGURATION: return set_callback_value_callback_configuration_uint16_t(message, &callback_value_distance);
		case FID_GET_DISTANCE_CALLBACK_CONFIGURATION: return get_callback_value_callback_configuration_uint16_t(message, response, &callback_value_distance);
		case FID_SET_UPDATE_RATE: return set_update_rate(message);
		case FID_GET_UPDATE_RATE: return get_update_rate(message, response);
		case FID_SET_DISTANCE_LED_CONFIG: return set_distance_led_config(message);
		case FID_GET_DISTANCE_LED_CONFIG: return get_distance_led_config(message, response);
		default: return HANDLE_MESSAGE_RESPONSE_NOT_SUPPORTED;
	}
}


BootloaderHandleMessageResponse set_update_rate(const SetUpdateRate *data) {
	if(data->update_rate > DISTANCE_US_V2_UPDATE_RATE_10_HZ) {
		return HANDLE_MESSAGE_RESPONSE_INVALID_PARAMETER;
	}

	maxbotix.update_rate = data->update_rate;

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse get_update_rate(const GetUpdateRate *data, GetUpdateRate_Response *response) {
	response->header.length = sizeof(GetUpdateRate_Response);
	response->update_rate   = maxbotix.update_rate;

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}

BootloaderHandleMessageResponse set_distance_led_config(const SetDistanceLEDConfig *data) {
	if(data->config > DISTANCE_US_V2_DISTANCE_LED_CONFIG_SHOW_DISTANCE) {
		return HANDLE_MESSAGE_RESPONSE_INVALID_PARAMETER;
	}

	XMC_GPIO_CONFIG_t config_gpio = {
		.mode         = XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
	};

	XMC_GPIO_CONFIG_t config_pwm = {
		.mode             = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2,
		.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
		.output_level     = XMC_GPIO_OUTPUT_LEVEL_LOW,
	};

	switch(data->config) {
		case DISTANCE_US_V2_DISTANCE_LED_CONFIG_OFF: {
			config_gpio.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH;
			XMC_GPIO_Init(MAXBOTIX_LED_PIN, &config_gpio);
			break;
		}

		case DISTANCE_US_V2_DISTANCE_LED_CONFIG_ON: // fall-through
		case DISTANCE_US_V2_DISTANCE_LED_CONFIG_SHOW_HEARTBEAT: {
			config_gpio.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;
			XMC_GPIO_Init(MAXBOTIX_LED_PIN, &config_gpio);
			break;
		}

		case DISTANCE_US_V2_DISTANCE_LED_CONFIG_SHOW_DISTANCE: {
			XMC_GPIO_Init(MAXBOTIX_LED_PIN, &config_pwm);
			break;
		}
	}

	maxbotix.led.config = data->config;
	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse get_distance_led_config(const GetDistanceLEDConfig *data, GetDistanceLEDConfig_Response *response) {
	response->header.length = sizeof(GetDistanceLEDConfig_Response);
	response->config        = maxbotix.led.config;

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}

bool handle_distance_callback(void) {
	return handle_callback_value_callback_uint16_t(&callback_value_distance, FID_CALLBACK_DISTANCE);
}

void communication_tick(void) {
	communication_callback_tick();
}

void communication_init(void) {
	callback_value_init_uint16_t(&callback_value_distance, maxbotix_get_distance);

	communication_callback_init();
}
