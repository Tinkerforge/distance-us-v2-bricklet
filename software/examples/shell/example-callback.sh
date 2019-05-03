#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change XYZ to the UID of your Distance US Bricklet 2.0

# Handle incoming distance callbacks
tinkerforge dispatch distance-us-v2-bricklet $uid distance &

# Set period for distance callback to 0.1s (100ms) without a threshold
tinkerforge call distance-us-v2-bricklet $uid set-distance-callback-configuration 100 false threshold-option-off 0 0

echo "Press key to exit"; read dummy

kill -- -$$ # Stop callback dispatch in background
