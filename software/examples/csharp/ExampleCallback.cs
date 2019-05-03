using System;
using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change XYZ to the UID of your Distance US Bricklet 2.0

	// Callback function for distance callback
	static void DistanceCB(BrickletDistanceUSV2 sender, int distance)
	{
		Console.WriteLine("Distance: " + distance/10.0 + " cm");
	}

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletDistanceUSV2 dus = new BrickletDistanceUSV2(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Register distance callback to function DistanceCB
		dus.DistanceCallback += DistanceCB;

		// Set period for distance callback to 0.1s (100ms) without a threshold
		dus.SetDistanceCallbackConfiguration(100, false, 'x', 0, 0);

		Console.WriteLine("Press enter to exit");
		Console.ReadLine();
		ipcon.Disconnect();
	}
}
