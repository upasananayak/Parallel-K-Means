import matplotlib.pyplot as plt

# Data for input sizes and thread counts
input_sizes = [1000, 10000, 50000, 100000, 500000]
threads = [2, 4, 8, 10]
execution_times = {
    1000: [0.014202, 0.012861, 0.006501, 0.005456, 0.005045],
    10000: [0.140502, 0.079435, 0.077922, 0.051266, 0.037800],
    50000: [1.359417, 0.506303, 0.480346, 0.278094, 0.130416],
    100000: [2.332436, 1.443393, 1.154794, 0.841901, 0.344152],
    500000: [12.705845, 8.147975, 5.655921, 3.274208, 3.061990]
}

# Calculate Speedup and Efficiency
speedups = {}
efficiencies = {}

for input_size in input_sizes:
    time_1 = execution_times[input_size][0]  # Time with 1 thread
    speedups[input_size] = [time_1 / time_n for time_n in execution_times[input_size]]
    efficiencies[input_size] = [speedup / threads[i] for i, speedup in enumerate(speedups[input_size][1:])]

# Plot Speedup
plt.figure(figsize=(10, 6))
for input_size in input_sizes:
    plt.plot(threads, speedups[input_size][1:], label=f'Input Size {input_size}')
plt.xlabel('Number of Threads')
plt.ylabel('Speedup')
plt.title('Speedup vs Number of Threads for Different Input Sizes')
plt.legend()
plt.grid(True)
plt.show()

# Plot Efficiency
plt.figure(figsize=(10, 6))
for input_size in input_sizes:
    plt.plot(threads, efficiencies[input_size], label=f'Input Size {input_size}')
plt.xlabel('Number of Threads')
plt.ylabel('Efficiency')
plt.title('Efficiency vs Number of Threads for Different Input Sizes')
plt.legend()
plt.grid(True)
plt.show()