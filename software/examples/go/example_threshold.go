package main

import (
	"fmt"
	"github.com/Tinkerforge/go-api-bindings/distance_us_v2_bricklet"
	"github.com/Tinkerforge/go-api-bindings/ipconnection"
)

const ADDR string = "localhost:4223"
const UID string = "XYZ" // Change XYZ to the UID of your Distance US Bricklet 2.0.

func main() {
	ipcon := ipconnection.New()
	defer ipcon.Close()
	dus, _ := distance_us_v2_bricklet.New(UID, &ipcon) // Create device object.

	ipcon.Connect(ADDR) // Connect to brickd.
	defer ipcon.Disconnect()
	// Don't use device before ipcon is connected.

	dus.RegisterDistanceCallback(func(distance uint16) {
		fmt.Printf("Distance: %f cm\n", float64(distance)/10.0)
	})

	// Configure threshold for distance "greater than 100 cm"
	// with a debounce period of 0.1s (100ms).
	dus.SetDistanceCallbackConfiguration(100, false, '>', 100*10, 0)

	fmt.Print("Press enter to exit.")
	fmt.Scanln()
}
