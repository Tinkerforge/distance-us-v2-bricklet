/* distance-us-v2-bricklet
 * Copyright (C) 2019 Olaf Lüke <olaf@tinkerforge.com>
 *
 * maxbotix.h: Driver for MaxBotix Distance US sensor
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

#ifndef MAXBOTIX_H
#define MAXBOTIX_H

#include <stdint.h>
#include <stdbool.h>

#include "bricklib2/utility/led_flicker.h"

#define MAXBOTIX_UPDATE_RATE_2HZ  0
#define MAXBOTIX_UPDATE_RATE_10HZ 1

typedef struct {
    bool enable;
    uint8_t state;
    uint16_t value;
    uint16_t distance;

    uint8_t update_rate;
    bool hz10_active;
    uint32_t hz10_time;

	LEDFlickerState led;
} Maxbotix;

extern Maxbotix maxbotix;

void maxbotix_tick(void);
void maxbotix_init(void);

uint16_t maxbotix_get_distance(void);

#endif