function octave_example_callback()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "XYZ"; % Change XYZ to the UID of your Distance US Bricklet 2.0

    ipcon = javaObject("com.tinkerforge.IPConnection"); % Create IP connection
    dus = javaObject("com.tinkerforge.BrickletDistanceUSV2", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register distance callback to function cb_distance
    dus.addDistanceCallback(@cb_distance);

    % Set period for distance callback to 0.1s (100ms) without a threshold
    dus.setDistanceCallbackConfiguration(100, false, "x", 0, 0);

    input("Press key to exit\n", "s");
    ipcon.disconnect();
end

% Callback function for distance callback
function cb_distance(e)
    fprintf("Distance: %g cm\n", e.distance/10.0);
end
