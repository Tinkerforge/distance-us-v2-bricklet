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

CallbackValue_uint16_t callback_value_distance;


BootloaderHandleMessageResponse handle_message(const void *message, void *response) {
	switch(tfp_get_fid_from_message(message)) {
		case FID_GET_DISTANCE: return get_callback_value_uint16_t(message, response, &callback_value_distance);
		case FID_SET_DISTANCE_CALLBACK_CONFIGURATION: return set_callback_value_callback_configuration_uint16_t(message, &callback_value_distance);
		case FID_GET_DISTANCE_CALLBACK_CONFIGURATION: return get_callback_value_callback_configuration_uint16_t(message, response, &callback_value_distance);
		default: return HANDLE_MESSAGE_RESPONSE_NOT_SUPPORTED;
	}
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
