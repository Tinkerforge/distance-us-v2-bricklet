<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletDistanceUSV2.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletDistanceUSV2;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XYZ'; // Change XYZ to the UID of your Distance US Bricklet 2.0

$ipcon = new IPConnection(); // Create IP connection
$dus = new BrickletDistanceUSV2(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Get current distance
$distance = $dus->getDistance();
echo "Distance: " . $distance/10.0 . " cm\n";

echo "Press key to exit\n";
fgetc(fopen('php://stdin', 'r'));
$ipcon->disconnect();

?>
