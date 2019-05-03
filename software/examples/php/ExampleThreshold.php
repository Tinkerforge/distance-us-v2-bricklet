<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletDistanceUSV2.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletDistanceUSV2;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XYZ'; // Change XYZ to the UID of your Distance US Bricklet 2.0

// Callback function for distance callback
function cb_distance($distance)
{
    echo "Distance: " . $distance/10.0 . " cm\n";
}

$ipcon = new IPConnection(); // Create IP connection
$dus = new BrickletDistanceUSV2(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Register distance callback to function cb_distance
$dus->registerCallback(BrickletDistanceUSV2::CALLBACK_DISTANCE, 'cb_distance');

// Configure threshold for distance "greater than 100 cm"
// with a debounce period of 0.1s (100ms)
$dus->setDistanceCallbackConfiguration(100, FALSE, '>', 100*10, 0);

echo "Press ctrl+c to exit\n";
$ipcon->dispatchCallbacks(-1); // Dispatch callbacks forever

?>
