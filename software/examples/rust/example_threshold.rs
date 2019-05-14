use std::{error::Error, io, thread};
use tinkerforge::{distance_us_v2_bricklet::*, ip_connection::IpConnection};

const HOST: &str = "localhost";
const PORT: u16 = 4223;
const UID: &str = "XYZ"; // Change XYZ to the UID of your Distance US Bricklet 2.0.

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection.
    let dus = DistanceUsV2Bricklet::new(UID, &ipcon); // Create device object.

    ipcon.connect((HOST, PORT)).recv()??; // Connect to brickd.
                                          // Don't use device before ipcon is connected.

    let distance_receiver = dus.get_distance_callback_receiver();

    // Spawn thread to handle received callback messages.
    // This thread ends when the `dus` object
    // is dropped, so there is no need for manual cleanup.
    thread::spawn(move || {
        for distance in distance_receiver {
            println!("Distance: {} cm", distance as f32 / 10.0);
        }
    });

    // Configure threshold for distance "greater than 100 cm"
    // with a debounce period of 0.1s (100ms).
    dus.set_distance_callback_configuration(100, false, '>', 100 * 10, 0);

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    ipcon.disconnect();
    Ok(())
}
