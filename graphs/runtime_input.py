import matplotlib.pyplot as plt

# Data for different numbers of threads
points = ['1000', '10000', '50000', '100000', '500000']
runtime_1_thread_ms = [x * 1000 for x in [0.014202, 0.140502, 1.359417, 2.332436, 12.705845]]
runtime_2_threads_ms = [x * 1000 for x in [0.012861, 0.079435, 0.506303, 1.443393, 8.147975]]
runtime_4_threads_ms = [x * 1000 for x in [0.006501, 0.077922, 0.480346, 1.154794, 5.655921]]
runtime_8_threads_ms = [x * 1000 for x in [0.005456, 0.051266, 0.278094, 0.841901, 3.274208]]
runtime_10_threads_ms = [x * 1000 for x in [0.005045, 0.03780, 0.130416, 0.344152, 3.061990]]

plt.figure(figsize=(10, 6))
plt.plot(points, runtime_1_thread_ms, 'o-', label='1 Thread')
plt.plot(points, runtime_2_threads_ms, 'o-', label='2 Threads')
plt.plot(points, runtime_4_threads_ms, 'o-', label='4 Threads')
plt.plot(points, runtime_8_threads_ms, 'o-', label='8 Threads')
plt.plot(points, runtime_10_threads_ms, 'o-', label='10 Threads')
plt.xlabel('Number of Points')
plt.ylabel('Runtime (ms)')
plt.title('Runtime vs Number of Points for Different Numbers of Threads')
plt.legend()
plt.show()