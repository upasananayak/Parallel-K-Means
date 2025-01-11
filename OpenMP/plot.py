import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

# Load the data from the file
df = pd.read_csv("cluster_output_threads10_points10000.txt", sep=" ", header=None)
df.columns = ["x", "y", "cluster"]  # Rename the columns for easier handling

# Load the centroids from the file
centroids_df = pd.read_csv("centroid_output_threads10_points10000.txt", sep=" ", header=None)
centroids_df.columns = ["x", "y"]

# Before clustering: Scatter plot of the data points
plt.figure(figsize=(10, 8))
sns.scatterplot(x=df["x"], y=df["y"])
plt.title("Scatterplot of y (second column) vs x (first column)")
plt.xlabel("x (first column)")
plt.ylabel("y (second column)")

# After clustering
plt.figure(figsize=(10, 8))
scatter = sns.scatterplot(x=df["x"], y=df["y"], hue=df["cluster"], palette=sns.color_palette("hls", n_colors=len(df["cluster"].unique())))

# Plot centroids
plt.scatter(centroids_df["x"], centroids_df["y"], marker='x', s=100, c='black', label='Centroids')

plt.xlabel("x (first column)")
plt.ylabel("y (second column)")
plt.title("Clustered: y vs x with k-means clusters")

# Move the legend outside the plot
plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left', borderaxespad=0.)

plt.tight_layout()  # Adjust layout to make room for the legend
plt.show()