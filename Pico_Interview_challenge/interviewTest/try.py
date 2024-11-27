import numpy as np
import pandas as pd
import os

# Get the current script location
input_folder = os.path.dirname(os.path.abspath(__file__))
output_file = os.path.join(input_folder, "src/out_python.csv")  # Output file in the same folder

# Initialize a list to store results
results = []

# Process each CSV file in the folder
for filename in os.listdir(input_folder):
    if filename.endswith(".csv"):  # Ensure only CSV files are processed
        file_path = os.path.join(input_folder, filename)

        # Load CSV data
        data = pd.read_csv(file_path)
        time = data['Seconds'].values
        amplitude = data['Volts'].values

        # Ensure uniform sampling (calculate sampling rate)
        fs = 1 / (time[1] - time[0])  # Assuming uniform sampling in time

        # Remove DC component
        amplitude = amplitude - np.mean(amplitude)

        # Apply a Hanning window to the signal
        window = np.hanning(len(amplitude))
        amplitude = amplitude * window

        # Perform FFT
        n = len(amplitude)
        fft_result = np.fft.fft(amplitude)
        frequencies = np.fft.fftfreq(n, d=1 / fs)
        magnitude = np.abs(fft_result[:n // 2])  # Positive frequencies only
        frequencies = frequencies[:n // 2]

        # Find the peak frequency
        peak_idx = np.argmax(magnitude)
        peak_frequency = frequencies[peak_idx]

        # Save result to the list
        results.append({"filename": filename, "frequency": peak_frequency})
        print(f"Processed {filename}: Highest amplitude frequency = {peak_frequency:.2f} Hz")

# Sort results by frequency (ascending order)
results = sorted(results, key=lambda x: x['frequency'])

# Write results to an output CSV
output_df = pd.DataFrame(results)
output_df.to_csv(output_file, index=False)

print(f"Results written to {output_file}")
