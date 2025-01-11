import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

# Load the data from datasetP.txt
df = pd.read_csv("datasetP.txt", sep=" ", header=None)
df = df[[0, 1]]  # Select only the first two columns
df.columns = ["x", "y"]  # Rename the columns for easier handling

# Load the cluster indices from indexP.txt
indices = pd.read_csv("IndexP.txt", header=None)
indices.columns = ["cluster"]

# Combine the data points and cluster indices into a single DataFrame
df["cluster"] = indices["cluster"]

# Before clustering: Scatter plot of the data points
plt.figure(figsize=(10, 8))
sns.scatterplot(x=df["x"], y=df["y"])
plt.title("Scatterplot of y (second column) vs x (first column)")
plt.xlabel("x (first column)")
plt.ylabel("y (second column)")

# After clustering
plt.figure(figsize=(10, 8))
scatter = sns.scatterplot(x=df["x"], y=df["y"], hue=df["cluster"], palette=sns.color_palette("hls", n_colors=len(df["cluster"].unique())))

plt.xlabel("x (first column)")
plt.ylabel("y (second column)")
plt.title("Clustered: y vs x with k-means clusters")

# Move the legend outside the plot
plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left', borderaxespad=0.)

plt.tight_layout()  # Adjust layout to make room for the legend
plt.show()