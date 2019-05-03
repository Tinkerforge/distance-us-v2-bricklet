#!/usr/bin/perl

use strict;
use Tinkerforge::IPConnection;
use Tinkerforge::BrickletDistanceUSV2;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change XYZ to the UID of your Distance US Bricklet 2.0

# Callback subroutine for distance callback
sub cb_distance
{
    my ($distance) = @_;

    print "Distance: " . $distance/10.0 . " cm\n";
}

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $dus = Tinkerforge::BrickletDistanceUSV2->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Register distance callback to subroutine cb_distance
$dus->register_callback($dus->CALLBACK_DISTANCE, 'cb_distance');

# Configure threshold for distance "greater than 100 cm"
# with a debounce period of 0.1s (100ms)
$dus->set_distance_callback_configuration(100, 0, '>', 100*10, 0);

print "Press key to exit\n";
<STDIN>;
$ipcon->disconnect();
