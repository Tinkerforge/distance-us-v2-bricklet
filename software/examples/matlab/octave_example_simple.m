function octave_example_simple()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "XYZ"; % Change XYZ to the UID of your Distance US Bricklet 2.0

    ipcon = javaObject("com.tinkerforge.IPConnection"); % Create IP connection
    dus = javaObject("com.tinkerforge.BrickletDistanceUSV2", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get current distance
    distance = dus.getDistance();
    fprintf("Distance: %g cm\n", distance/10.0);

    input("Press key to exit\n", "s");
    ipcon.disconnect();
end
