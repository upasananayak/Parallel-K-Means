import matplotlib.pyplot as plt

# Data for sequential and 1 thread
points = [1000, 10000, 50000, 100000, 500000]
runtime_sequential_ms = [x * 1000 for x in [0.0271789, 0.193354, 1.07808, 2.13707, 11.9473]]
runtime_1_thread_ms = [x * 1000 for x in [0.014202, 0.140502, 1.359417, 2.332436, 12.705845]]

plt.figure(figsize=(8, 6))
plt.plot(points, runtime_sequential_ms, 'o-', color='blue', label='Sequential')
plt.plot(points, runtime_1_thread_ms, 'o-', color='red', label='1 Thread')
plt.xlabel('Number of Points')
plt.ylabel('Runtime (ms)')
plt.title('Runtime vs Number of Points (Sequential and 1 Thread)')
plt.legend()
plt.show()
