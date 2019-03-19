/* distance-us-v2-bricklet
 * Copyright (C) 2019 Olaf Lüke <olaf@tinkerforge.com>
 *
 * config.h: All configurations for Distance US Bricklet 2.0
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

#ifndef CONFIG_GENERAL_H
#define CONFIG_GENERAL_H

#include "xmc_device.h"

#define STARTUP_SYSTEM_INIT_ALREADY_DONE
#define SYSTEM_TIMER_FREQUENCY 1000 // Use 1 kHz system timer

#define UARTBB_TX_PIN P0_0

#define FIRMWARE_VERSION_MAJOR 2
#define FIRMWARE_VERSION_MINOR 0
#define FIRMWARE_VERSION_REVISION 0

#define CALLBACK_VALUE_TYPE CALLBACK_VALUE_TYPE_UINT16

#include "config_custom_bootloader.h"

#endif
