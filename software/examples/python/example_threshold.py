#!/usr/bin/env python
# -*- coding: utf-8 -*-

HOST = "localhost"
PORT = 4223
UID = "XYZ" # Change XYZ to the UID of your Distance US Bricklet 2.0

from tinkerforge.ip_connection import IPConnection
from tinkerforge.bricklet_distance_us_v2 import BrickletDistanceUSV2

# Callback function for distance callback
def cb_distance(distance):
    print("Distance: " + str(distance/10.0) + " cm")

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    dus = BrickletDistanceUSV2(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    # Register distance callback to function cb_distance
    dus.register_callback(dus.CALLBACK_DISTANCE, cb_distance)

    # Configure threshold for distance "greater than 100 cm"
    # with a debounce period of 0.1s (100ms)
    dus.set_distance_callback_configuration(100, False, ">", 100*10, 0)

    raw_input("Press key to exit\n") # Use input() in Python 3
    ipcon.disconnect()
