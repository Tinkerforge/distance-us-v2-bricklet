var Tinkerforge = require('tinkerforge');

var HOST = 'localhost';
var PORT = 4223;
var UID = 'XYZ'; // Change XYZ to the UID of your Distance US Bricklet 2.0

var ipcon = new Tinkerforge.IPConnection(); // Create IP connection
var dus = new Tinkerforge.BrickletDistanceUSV2(UID, ipcon); // Create device object

ipcon.connect(HOST, PORT,
    function (error) {
        console.log('Error: ' + error);
    }
); // Connect to brickd
// Don't use device before ipcon is connected

ipcon.on(Tinkerforge.IPConnection.CALLBACK_CONNECTED,
    function (connectReason) {
        // Configure threshold for distance "greater than 100 cm"
        // with a debounce period of 0.1s (100ms)
        dus.setDistanceCallbackConfiguration(100, false, '>', 100*10, 0);
    }
);

// Register distance callback
dus.on(Tinkerforge.BrickletDistanceUSV2.CALLBACK_DISTANCE,
    // Callback function for distance callback
    function (distance) {
        console.log('Distance: ' + distance/10.0 + ' cm');
    }
);

console.log('Press key to exit');
process.stdin.on('data',
    function (data) {
        ipcon.disconnect();
        process.exit(0);
    }
);
