import matplotlib.pyplot as plt
import numpy as np

# Data for plotting (runtime in seconds)
data_points = ['1000', '10000', '50000', '100000', '500000']

# Sequential runtime (in seconds)
sequential = [0.0271789, 0.193354, 1.07808, 2.13707, 11.9473]

# OpenMP runtime (using 10 threads)
openmp_10 = [0.005045, 0.037800, 0.130416, 0.344152, 3.061990]

# MPI runtime (using 6 processes) - converted to seconds
mpi_6 = [0.102296114, 0.121651649, 0.294773817, 0.330806971, 1.030325890]

# CUDA runtime (using 4 threads per block)
cuda_4 = [0.364091, 0.113058, 0.135488, 0.157147, 0.354439]

# Plotting the data
plt.figure(figsize=(10, 6))

# Plot the data for each method
plt.plot(data_points, sequential, label='Sequential', marker='o', color='blue', linestyle='-', linewidth=2)
plt.plot(data_points, openmp_10, label='OpenMP (10 threads)', marker='s', color='green', linestyle='-', linewidth=2)
plt.plot(data_points, mpi_6, label='MPI (6 processes)', marker='^', color='orange', linestyle='-', linewidth=2)
plt.plot(data_points, cuda_4, label='CUDA (4 threads/block)', marker='x', color='red', linestyle='-', linewidth=2)

# Labels and title
plt.xlabel('Number of Data Points')
plt.ylabel('Runtime (seconds)')
plt.title('Performance Comparison: Sequential, OpenMP, MPI, and CUDA')

# Display grid
plt.grid(True)

# Show legend
plt.legend()

# Show the plot
plt.show()