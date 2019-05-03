function matlab_example_simple()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletDistanceUSV2;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XYZ'; % Change XYZ to the UID of your Distance US Bricklet 2.0

    ipcon = IPConnection(); % Create IP connection
    dus = handle(BrickletDistanceUSV2(UID, ipcon), 'CallbackProperties'); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get current distance
    distance = dus.getDistance();
    fprintf('Distance: %g cm\n', distance/10.0);

    input('Press key to exit\n', 's');
    ipcon.disconnect();
end
