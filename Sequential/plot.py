import pandas as pd
import matplotlib.pyplot as plt

# Load data from files
data = pd.read_csv('output_data_points.txt')
centroids = pd.read_csv('centroids.txt')

# Plot the data points before clustering
plt.figure(figsize=(10, 6))
plt.scatter(data['x'], data['y'], c='gray', s=50, alpha=0.8)
plt.xlabel('X Coordinate')
plt.ylabel('Y Coordinate')
plt.title('Data Points Before Clustering')
plt.show()

# Plot the data points after clustering, coloring by cluster
plt.figure(figsize=(10, 6))
scatter = plt.scatter(data['x'], data['y'], c=data['cluster'], cmap='tab20', s=50, alpha=0.8)
plt.colorbar(scatter, label='Cluster')

# Plot centroids with 'X' markers in black
plt.scatter(centroids['x'], centroids['y'], c='black', s=200, marker='X')

# Add labels and title
plt.xlabel('X Coordinate')
plt.ylabel('Y Coordinate')
plt.title('K-Means Clustering Results with Centroids')

# Show the plot
plt.show()