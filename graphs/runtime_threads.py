import matplotlib.pyplot as plt

# Data for different numbers of points
threads = ['1', '2', '4', '8', '10']
runtime_1000_points_ms = [0.014202 * 1000, 0.012861 * 1000, 0.006501 * 1000, 0.005456 * 1000, 0.005045 * 1000]
runtime_10000_points_ms = [0.140502 * 1000, 0.079435 * 1000, 0.077922 * 1000, 0.051266 * 1000, 0.03780 * 1000]
runtime_50000_points_ms = [1.359417 * 1000, 0.506303 * 1000, 0.480346 * 1000, 0.278094 * 1000, 0.130416 * 1000]
runtime_100000_points_ms = [2.332436 * 1000, 1.443393 * 1000, 1.154794 * 1000, 0.841901 * 1000, 0.344152 * 1000]
runtime_500000_points_ms = [12.705845 * 1000, 8.147975 * 1000, 5.655921 * 1000, 3.274208 * 1000, 3.061990 * 1000]

plt.figure(figsize=(10, 6))
plt.plot(threads, runtime_1000_points_ms, 'o-', label='1000 Points')
plt.plot(threads, runtime_10000_points_ms, 'o-', label='10000 Points')
plt.plot(threads, runtime_50000_points_ms, 'o-', label='50000 Points')
plt.plot(threads, runtime_100000_points_ms, 'o-', label='100000 Points')
plt.plot(threads, runtime_500000_points_ms, 'o-', label='500000 Points')

plt.xlabel('Number of Threads')
plt.ylabel('Runtime (ms)')
plt.title('Runtime vs Number of Threads for Different Numbers of Points')

# Set x-axis and y-axis ticks
plt.xticks(threads)
plt.yticks(range(0, 14000, 2000))  # Increase the interval to 2000 ms

plt.legend()
plt.show()