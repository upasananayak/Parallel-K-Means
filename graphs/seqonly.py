import matplotlib.pyplot as plt

# Data
points = ['1000', '10000', '50000', '100000', '500000']
runtime_seconds = [0.0271789, 0.193354, 1.07808, 2.13707, 11.9473]

plt.figure(figsize=(10, 6))
plt.plot(points, runtime_seconds, 'o-', color='blue', label='Runtime')

plt.xlabel('Number of Points')
plt.ylabel('Runtime (in seconds)')
plt.title('Runtime vs Number of Points')
plt.grid(True)  # Add grid for better readability

plt.legend()
plt.show()