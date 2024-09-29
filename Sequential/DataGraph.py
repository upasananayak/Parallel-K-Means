import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

# Load the data from data_20k.csv (assumed first two columns are x and y)
df = pd.read_csv("data_20k.csv", header=None)
df.columns = ["x", "y"]  # Rename the columns for easier handling

# Before clustering: Scatter plot of the data points
sns.scatterplot(x=df["x"], y=df["y"])
plt.title("Scatterplot of y (second column) vs x (first column)")
plt.xlabel("x (first column)")
plt.ylabel("y (second column)")
plt.show()

# After clustering
plt.figure()
df_clustered = pd.read_csv("output2.csv")  # Read the clustered output
scatter = sns.scatterplot(x=df_clustered.x, y=df_clustered.y, 
                          hue=df_clustered.c, 
                          palette=sns.color_palette("hls", n_colors=20))

plt.xlabel("x (first column)")
plt.ylabel("y (second column)")
plt.title("Clustered: y vs x with k-means clusters")

# Move the legend outside the plot
plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left', borderaxespad=0.)

plt.tight_layout()  # Adjust layout to make room for the legend
plt.show()
