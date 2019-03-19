/* distance-us-v2-bricklet
 * Copyright (C) 2019 Olaf Lüke <olaf@tinkerforge.com>
 *
 * config_maxbotix.h: Configuration for MaxBotix Distance US sensor
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

#ifndef CONFIG_MAXBOTIX_H
#define CONFIG_MAXBOTIX_H

#define MAXBOTIX_ENABLE_PIN          P0_6
#define MAXBOTIX_LED_PIN             P1_0

#define MAXBOTIX_USIC_CHANNEL        USIC0_CH1
#define MAXBOTIX_USIC                XMC_UART0_CH1

#define MAXBOTIX_RX_PIN              P0_7
#define MAXBOTIX_RX_INPUT            XMC_USIC_CH_INPUT_DX0
#define MAXBOTIX_RX_SOURCE           0b011 // DX0D

#define MAXBOTIX_SERVICE_REQUEST_RX  2  // receive

#define MAXBOTIX_IRQ_RX              11
#define MAXBOTIX_IRQ_RX_PRIORITY     0

#endif