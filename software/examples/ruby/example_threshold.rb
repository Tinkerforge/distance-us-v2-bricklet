#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/bricklet_distance_us_v2'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = 'XYZ' # Change XYZ to the UID of your Distance US Bricklet 2.0

ipcon = IPConnection.new # Create IP connection
dus = BrickletDistanceUSV2.new UID, ipcon # Create device object

ipcon.connect HOST, PORT # Connect to brickd
# Don't use device before ipcon is connected

# Register distance callback
dus.register_callback(BrickletDistanceUSV2::CALLBACK_DISTANCE) do |distance|
  puts "Distance: #{distance/10.0} cm"
end

# Configure threshold for distance "greater than 100 cm"
# with a debounce period of 0.1s (100ms)
dus.set_distance_callback_configuration 100, false, '>', 100*10, 0

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
