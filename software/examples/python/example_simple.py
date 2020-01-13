#!/usr/bin/env python
# -*- coding: utf-8 -*-

HOST = "localhost"
PORT = 4223
UID = "XYZ" # Change XYZ to the UID of your Distance US Bricklet 2.0

from tinkerforge.ip_connection import IPConnection
from tinkerforge.bricklet_distance_us_v2 import BrickletDistanceUSV2

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    dus = BrickletDistanceUSV2(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    # Get current distance
    distance = dus.get_distance()
    print("Distance: " + str(distance/10.0) + " cm")

    input("Press key to exit\n") # Use raw_input() in Python 2
    ipcon.disconnect()
