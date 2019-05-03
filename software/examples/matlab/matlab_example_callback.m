function matlab_example_callback()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletDistanceUSV2;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XYZ'; % Change XYZ to the UID of your Distance US Bricklet 2.0

    ipcon = IPConnection(); % Create IP connection
    dus = handle(BrickletDistanceUSV2(UID, ipcon), 'CallbackProperties'); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register distance callback to function cb_distance
    set(dus, 'DistanceCallback', @(h, e) cb_distance(e));

    % Set period for distance callback to 0.1s (100ms) without a threshold
    dus.setDistanceCallbackConfiguration(100, false, 'x', 0, 0);

    input('Press key to exit\n', 's');
    ipcon.disconnect();
end

% Callback function for distance callback
function cb_distance(e)
    fprintf('Distance: %g cm\n', e.distance/10.0);
end
