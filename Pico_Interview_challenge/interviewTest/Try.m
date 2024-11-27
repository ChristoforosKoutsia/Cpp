close all;
clear;
clc;
% Step 1: Import the CSV data
data = csvread('Wave116.csv', 1, 0); % Skip the header row
time = data(:, 1);  % First column: Time (seconds)
volts = data(:, 2); % Second column: Voltage (volts)

% Step 2: Call the frequency analysis function
[freq, peak_times, peak_volts] = analyze_frequency_with_findpeaks_only(time, volts);

% Display the detected frequency
disp(['Detected frequency: ', num2str(freq), ' Hz']);
disp(length(peak_volts));

% Display peak times and voltages
disp('Peak times and corresponding voltages:');
disp(table(peak_times, peak_volts, 'VariableNames', {'Time (s)', 'Voltage (V)'}));

function [freq, peak_times, peak_volts] = analyze_frequency_with_findpeaks_only(time, volts)
    % time: The time vector (seconds)
    % volts: The voltage signal (volts)
    
    % Ensure the signal is a column vector (if it's a row vector)
    volts = volts(:);
    time = time(:);

    % Detect peaks in the time-domain signal
    [peak_volts, peak_indices] = findpeaks(volts, 'MinPeakHeight', max(volts)*0.5, 'MinPeakDistance', 2); % Adjust as needed

    % Extract corresponding times of the peaks
    peak_times = time(peak_indices);

    % Calculate time differences between consecutive peaks
    peak_intervals = diff(peak_times);

    % Calculate the fundamental frequency as the inverse of the average period
    avg_period = mean(peak_intervals); % Average time interval between peaks
    freq = 1 / avg_period; % Fundamental frequency (Hz)
    
    % Optional: Plot the time-domain signal with detected peaks
    figure;
    plot(time, volts);
    hold on;
    plot(peak_times, peak_volts, 'ro'); % Highlight detected peaks
    title('Time-Domain Signal with Detected Peaks');
    xlabel('Time (s)');
    ylabel('Voltage (V)');
    grid on;
    hold off;
end
